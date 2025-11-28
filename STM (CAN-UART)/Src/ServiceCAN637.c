//serviceCan637:
//Historique: 
// 2025-11-28, creation à partir de serviceProtocole637 pour utilisation via CAN1

//INCLUSIONS
#include "main.h"
#include "piloteCAN1.h"
#include "serviceBaseDeTemps.h"
#include "serviceCan637.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
static void serviceCan637_gereLaTransmission(void);
static void serviceCan637_gereLaReception(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de variables publiques:
SERVICECAN637 serviceCan637;

//Definitions de fonctions privees:

//--------------------- TRANSMISSION --------------------------
static void serviceCan637_gereLaTransmission(void)
{
  // Si aucune requête à traiter, on sort
  if (serviceCan637.requete == REQUETE_TRAITEE)
  {
    return;
  }

  // Validation de la longueur demandée (1 à N, N = 8)
  if ((serviceCan637.nombreATransmettre == 0) ||
      (serviceCan637.nombreATransmettre > SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM))
  {
    serviceCan637.statut = SERVICECAN637_ERREUR_LONGUEUR_INVALIDE;
    serviceCan637.requete = REQUETE_TRAITEE;
    return;
  }

  // S'il n'y a pas de mailbox CAN libre, on réessaiera au prochain tick
  if (piloteCAN1_messageTransmis() == 0)
  {
    return;
  }

  // Transmission CAN proprement dite
  if (piloteCAN1_transmetDesDonnes(PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION,
                                   serviceCan637.octetsATransmettre,
                                   serviceCan637.nombreATransmettre)
      != PILOTECAN1_TRANSMIS)
  {
    serviceCan637.statut = SERVICECAN637_ERREUR_TRANSMISSION;
    serviceCan637.requete = REQUETE_TRAITEE;
    return;
  }

  // Tout est OK
  serviceCan637.statut = SERVICECAN637_PAS_D_ERREURS;
  serviceCan637.requete = REQUETE_TRAITEE;
}

//--------------------- RECEPTION -----------------------------
static void serviceCan637_gereLaReception(void)
{
  unsigned char tampon[SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char i;

  // Tant que l'information n'a pas été traitée par l'interface,
  // on ne remplace pas le buffer.
  if (serviceCan637.information == INFORMATION_DISPONIBLE)
  {
    return;
  }

  // Aucun message disponible dans le FIFO CAN
  if (piloteCAN1_messageDisponible() == 0)
  {
    return;
  }

  // On lit un message du FIFO
  if (piloteCAN1_litUnMessageRecu(tampon) != PILOTECAN1_DISPONIBLE)
  {
    // Erreur de lecture: on signale l'erreur et on indique qu'une info est dispo
    serviceCan637.nombreARecevoir = 0;
    serviceCan637.statut = SERVICECAN637_ERREUR_RECEPTION;
    serviceCan637.information = INFORMATION_DISPONIBLE;
    return;
  }

  // À ce niveau, on a reçu un message CAN.
  // On copie toujours N octets (taille maximale définie pour le protocole 637).
  for (i = 0; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
  {
    serviceCan637.octetsRecus[i] = tampon[i];
  }

  // Pas de DLC accessible ici, donc on considère que le protocole envoie
  // toujours exactement SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM octets.
  serviceCan637.nombreARecevoir = SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM;

  serviceCan637.statut = SERVICECAN637_PAS_D_ERREURS;
  serviceCan637.information = INFORMATION_DISPONIBLE;
}

//--------------------- INITIALISATION ------------------------
void serviceCan637_initialise(void)
{
  unsigned char i;

  serviceCan637.etatDuModuleDeReception = MODULE_PAS_EN_FONCTION;
  serviceCan637.information = INFORMATION_TRAITEE;
  serviceCan637.requete = REQUETE_TRAITEE;
  serviceCan637.nombreATransmettre = 0;
  serviceCan637.nombreARecevoir = 0;
  serviceCan637.statut = SERVICECAN637_PAS_D_ERREURS;

  for (i = 0; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
  {
    serviceCan637.octetsATransmettre[i] = 0;
    serviceCan637.octetsRecus[i] = 0;
  }

  // Initialisation du pilote CAN1 (filtre + CAN_Start)
  if (piloteCAN1_initialise() != PILOTECAN1_PAS_D_ERREUR)
  {
    serviceCan637.statut = SERVICECAN637_ERREUR_RECEPTION;
  }

  // Enregistrement des fonctions de gestion dans le service de base de temps
  serviceBaseDeTemps_execute[SERVICECAN637_PHASE_TRANSMISSION] =
      serviceCan637_gereLaTransmission;
  serviceBaseDeTemps_execute[SERVICECAN637_PHASE_RECEPTION] =
      serviceCan637_gereLaReception;

  serviceCan637.etatDuModuleDeReception = MODULE_EN_FONCTION;
}
