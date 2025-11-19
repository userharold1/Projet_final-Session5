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



    if (processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_ARRET)
    {
        if (processusVehicule.derniereLignePleine == 0)
        {
            processusVehicule.CompteurPosi++;
            serviceWiFiUDP.messageATransmettre[1] = "a";
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
            serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_rotation180;

            // Après rotation → repartir vers le début (même direction de suivi)
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
            break;


        case POSITION_LIGNE_MILIEU_RETOUR:
            // Retour en passant la ligne du milieu
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
            break;


        case POSITION_LIGNE_DEBUT:
            // Arrivé à la ligne début → stop ou 180° selon message UDP
            serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
            break;

        default:
            break;
    }
}



void processusConduite_rotation180(void)
{
    static unsigned int compteurRotation = 0;

    if (compteurRotation == 0)
    {
        Serial.println("Rotation 180° démarrée");
    }

    // Tourner sur place : un moteur avance, l'autre recule
    moteur_IN1_driver1(MOTEUR1, HIGH);
    moteur_IN2_driver1(MOTEUR1, LOW);

    moteur_IN1_driver1(MOTEUR2, LOW);
    moteur_IN2_driver1(MOTEUR2, HIGH);

    // PWM à 205 si tu en as un
    // moteur_EN_driver1(MOTEUR1, 205);
    // moteur_EN_driver1(MOTEUR2, 205);

    compteurRotation++;

    // *** À ajuster selon ton robot ***
    if (compteurRotation >= 18)  // ← calibré pour vitesse 205
    {
        compteurRotation = 0;

        // Stop
        processusConduite_arret();

        Serial.println("Rotation 180° terminée");

        // Repartir vers le suivi
        serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
    }
}



void processusVehicule_initialise(void)
{
 processusVehicule.CompteurPosi = POSITION_DEPART;
 processusVehicule.derniereLignePleine = 0;
 serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_gere;
}
