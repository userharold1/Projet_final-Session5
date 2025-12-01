//serviceCan637:
//Historique: 
// 2025-12-01, création à partir de serviceProtocole637 pour utilisation via CAN1

//INCLUSIONS
#include "main.h"
#include "piloteCAN1.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCAN637.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
static void serviceCan637_gereLaTransmission(void);
static void serviceCan637_gereLaReception(void);

//Definitions de variables privees:


//Definitions de variables publiques:
SERVICECAN637 serviceCan637;

//--------------------------------------------------
//            TRANSMISSION
//--------------------------------------------------
static void serviceCan637_gereLaTransmission(void)
{
  // Aucune requête en attente
  if (serviceCan637.requete == REQUETE_TRAITEE)
  {
    return;
  }

  // Validation de la longueur
  if (serviceCan637.nombreATransmettre == 0)
  {
    serviceCan637.statut = SERVICECAN637_ERREUR_LONGUEUR_NULLE;
    serviceCan637.requete = REQUETE_TRAITEE;
    return;
  }

  if (serviceCan637.nombreATransmettre > SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM)
  {
    serviceCan637.statut = SERVICECAN637_ERREUR_LONGUEUR_TROP_GRANDE;
    serviceCan637.requete = REQUETE_TRAITEE;
    return;
  }

  // Si aucune mailbox CAN n'est libre, on réessaiera au prochain tick
  if (piloteCAN1_messageTransmis() == 0)
  {
    return;
  }

  // Transmission CAN via le pilote
  // L'ID utilisé vient de main.h: PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION
  if (piloteCAN1_transmetDesDonnes(PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION,
                                   serviceCan637.octetsATransmettre,
                                   serviceCan637.nombreATransmettre)
      != PILOTECAN1_TRANSMIS)
  {
    serviceCan637.statut = SERVICECAN637_ERREUR_TRANSMISSION;
    serviceCan637.requete = REQUETE_TRAITEE;
    return;
  }

  // Tout s'est bien passé
  serviceCan637.statut = SERVICECAN637_PAS_D_ERREURS;
  serviceCan637.requete = REQUETE_TRAITEE;
}

//--------------------------------------------------
//            RECEPTION
//--------------------------------------------------
static void serviceCan637_gereLaReception(void)
{
  unsigned char tampon[8]; // tampon brut, 8 max en CAN
  unsigned char i;

  // Si l'information précédente n'a pas encore été lue par l'interface,
  // on ne remplace pas le buffer.
  if (serviceCan637.information == INFORMATION_DISPONIBLE)
  {
    return;
  }

  // Est-ce qu'il y a au moins une trame dans le FIFO CAN ?
  if (piloteCAN1_messageDisponible() == 0)
  {
    return;
  }

  // On lit UNE trame via le pilote de base
  if (piloteCAN1_litUnMessageRecu(tampon) != PILOTECAN1_DISPONIBLE)
  {
    serviceCan637.nombreARecevoir = 0;
    serviceCan637.statut = SERVICECAN637_ERREUR_RECEPTION;
    serviceCan637.information = INFORMATION_DISPONIBLE; // signale une erreur
    return;
  }

    serviceCan637.nombreARecevoir = SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM;
 

  // Copie dans le buffer public
  for (i = 0; i < serviceCan637.nombreARecevoir; i++)
  {
    serviceCan637.octetsRecus[i] = tampon[i];
  }

  // Si jamais on reçoit moins d'octets que prévu, on peut zéroter le reste
  for (; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
  {
    serviceCan637.octetsRecus[i] = 0;
  }

  serviceCan637.statut = SERVICECAN637_PAS_D_ERREURS;
  serviceCan637.information = INFORMATION_DISPONIBLE;
}

//--------------------------------------------------
//            INITIALISATION
//--------------------------------------------------
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

 
  serviceBaseDeTemps_execute[SERVICECAN637_PHASE_TRANSMISSION] =
      serviceCan637_gereLaTransmission;
  serviceBaseDeTemps_execute[SERVICECAN637_PHASE_RECEPTION] =
      serviceCan637_gereLaReception;

  serviceCan637.etatDuModuleDeReception = MODULE_EN_FONCTION;
}
