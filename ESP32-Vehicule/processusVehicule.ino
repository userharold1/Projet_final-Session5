// serviceVehicule.c
// Processus Véhicule

#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceWiFiUDP.h"
#include "processusConduite.h"
#include "ProcessusSuiveurDeLigne.h"

//================================
// Define
//================================
DELAIROTATION180 1900
DELAIROTATION90  800

//================================
// Variables Globales
//================================

PROCESSUSVEHICULE processusVehicule;

// ===============================
// Fonctions privées
// ===============================
void processusVehicule_gere (void);
void processusVehicule_Suit(void);
void processusVehicule_Positionnement(void);
void processusVehicule_rotation180(void);
// ===============================
// Fonctions publiques
// ===============================
void processusVehicule_gere (void)
{
  if(serviceWiFiUDP.information == SERVICEWIFIUDP_INFORMATION_DISPONIBLE)
  {
    if(strcmp(serviceWiFiUDP.messageRecu, "Suit") == 0)
    {
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
    }

    serviceWiFiUDP.information = SERVICEWIFIUDP_INFORMATION_TRAITEE;
  }
}

void processusVehicule_Suit(void)
{
  if(processusVehicule.controleSuiveur == SUIVEUR_ACTIF)
  {
    // Gestion des directions de suivi
    if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_AVANCE)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_avance;
    }
    else if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_TOURNEADROITE)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite;
    }
    else if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_TOURNEAGAUCHE)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneAGauche;
    }
    else if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_PERDU)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
    }

    // Détection d'une ligne pleine (positionnement)
    if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_ARRET)
    {
      // Incrémenter seulement si c'était pas déjà une ligne pleine
      if(processusVehicule.derniereLignePleine == 0)
      {
        processusVehicule.CompteurPosi++;
      }
      processusVehicule.derniereLignePleine = 1;

      // Passer à la phase de positionnement
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Positionnement;
    }
    else
    {
      processusVehicule.derniereLignePleine = 0;
    }
  }
}

void processusVehicule_Positionnement(void)
{
  switch(processusVehicule.CompteurPosi)
  {
    case POSITION_LIGNE_MILIEU_AVANT:
      // Reprendre le suivi vers la ligne de fin
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
      break;

    case POSITION_LIGNE_FIN:
      // Ligne de fin → faire un 180°
      processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
      break;

    case POSITION_LIGNE_MILIEU_RETOUR:
      // Retour en passant la ligne du milieu
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
      break;

    case POSITION_LIGNE_DEBUT:
      // Arrivé à la ligne début → rotation 180° puis réinitialiser
      processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
      break;

    default:
      break;
  }
}

void processusVehicule_rotation180(void)
{
  static unsigned long compteurRotation = 0;
  static bool rotationEnCours = false;

  // Début de la rotation : initialiser
  if(!rotationEnCours)
  {
    compteurRotation = millis();
    rotationEnCours = true;
    
    // IMPORTANT : Désactiver le suiveur AVANT de commencer la rotation
    processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
  }

  // Action de rotation
  serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite;

  // Durée de rotation à ajuster selon ton robot (1050ms)
  if(millis() - compteurRotation >= 1900) 
  {
    // Arrêter les moteurs brièvement
    serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
    
    // Petit délai pour stabiliser (optionnel, peut aider)
   // delay(50);

    // Remettre le compteur à 0 seulement APRÈS la rotation complète
    if(processusVehicule.CompteurPosi == POSITION_LIGNE_DEBUT)
    {
      processusVehicule.CompteurPosi = 0;
    }

    // Réactiver le suiveur
    processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
    
    // Forcer la sortie de la détection de ligne pleine
    // Le robot est encore sur la ligne, on ignore jusqu'à ce qu'il la quitte
    processusVehicule.derniereLignePleine = 1;

    // Réinitialiser les variables statiques
    compteurRotation = 0;
    rotationEnCours = false;

    // Revenir au suivi de ligne
    serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
  }
}

void processusVehicule_initialise(void)
{
  processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
  processusVehicule.CompteurPosi = POSITION_DEPART;
  processusVehicule.derniereLignePleine = 0;
  serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_gere;
}