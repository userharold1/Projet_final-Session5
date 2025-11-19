// serviceVehicule.c
// Processus Véhicule

#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceWiFiUDP.h"
#include "processusConduite.h"
#include "ProcessusSuiveurDeLigne.h"

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
  if( processusVehicule.controleSuiveur == SUIVEUR_ACTIF)
  {
   if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_AVANCE)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_avance;
    }
    else if (processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_TOURNEADROITE)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite;
    }
    else if (processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_TOURNEAGAUCHE)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneAGauche;
    }
    /*else if (processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_PERDU)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
    }*/



    if (processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_ARRET)
    {
        if (processusVehicule.derniereLignePleine == 0)
        {
            processusVehicule.CompteurPosi++;
           // serviceWiFiUDP.messageATransmettre[1] = "a";
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
    switch (processusVehicule.CompteurPosi)
    {
        case POSITION_LIGNE_MILIEU_AVANT:
            // Reprendre le suivi vers la ligne de fin
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
            break;


        case POSITION_LIGNE_FIN:
            // Ligne de fin → faire un 180°
            processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
            break;


        case POSITION_LIGNE_MILIEU_RETOUR:
            // Retour en passant la ligne du milieu
            //processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
            break;


        case POSITION_LIGNE_DEBUT:
            // Arrivé à la ligne début → stop ou 180° selon message UDP
            
          // serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
           processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
           serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
           //serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
            break;

        default:
            break;
    }
}



void processusVehicule_rotation180(void)
{
    static unsigned long compteurRotation = 0;

    // Début de la rotation : initialiser le temps de départ
    if (compteurRotation == 0)
    {
        compteurRotation = millis();  
        // Désactiver le suiveur pendant la rotation
        serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
        processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
    }

    // Action de rotation
    serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite;

    // Durée de rotation à ajuster (ms)
    if (millis() - compteurRotation >= 1000) 
    {
        // Arrêter les moteurs
        serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;

        // Réactiver le suiveur après rotation
        processusVehicule.controleSuiveur = SUIVEUR_ACTIF;

        // Réinitialiser pour la prochaine rotation
        compteurRotation = 0;

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
