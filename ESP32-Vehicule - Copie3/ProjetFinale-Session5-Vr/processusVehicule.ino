// serviceVehicule.c
// Processus Véhicule

#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceWiFiUDP.h"
#include "processusConduite.h"
#include "ProcessusSuiveurDeLigne.h"
#include "processusVehicule.h"
//================================
// Define
//================================
#define DELAIROTATION180 900
#define DELAIROTATION90  500
#define DELAI_RECUL_AVANT_ROTATION 500
#define DELAI_ATTENTE_AVANT_ROTATION 2000
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
void processusVehicule_AttenteInstruction(void);
void processusVehicule_SuitEnRecul(void);

// ===============================
// Fonctions publiques
// ===============================
void processusVehicule_gere (void)
{
  if(serviceWiFiUDP.information == SERVICEWIFIUDP_INFORMATION_DISPONIBLE)
  {
    if(strcmp(serviceWiFiUDP.messageRecu, "Rouge") == 0)
    {
      processusVehicule.blocActif = BLOCROUGE;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
    }

    else if(strcmp(serviceWiFiUDP.messageRecu, "Metal") == 0)
    {
      processusVehicule.blocActif = BLOCMETAL;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
    }

    else
    {
      processusVehicule.blocActif = AUCUNBLOC;
      return;
      
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
     strcpy(serviceWiFiUDP.messageATransmettre, "MilieuA");
     serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_A_TRAITER;
      // Reprendre le suivi vers la ligne de fin
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
      break;

    case POSITION_LIGNE_FIN:
      strcpy(serviceWiFiUDP.messageATransmettre, "Tri");
      serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_A_TRAITER;
      // Ligne de fin → faire un 180°
      processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_AttenteInstruction;
      break;

    case POSITION_LIGNE_MILIEU_RETOUR:
      // Retour en passant la ligne du milieu
      
      //processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;

      
       strcpy(serviceWiFiUDP.messageATransmettre, "MilieuR");
       serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_A_TRAITER;
       processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
       serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
      
   
      
      
      break;

    case POSITION_LIGNE_DEBUT:
      strcpy(serviceWiFiUDP.messageATransmettre, "Pese");
      serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_A_TRAITER;
      
      processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;

      if(processusVehicule.blocActif == BLOCMETAL)
      {
        serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_AttenteInstruction;
      }
      else if(processusVehicule.blocActif == BLOCROUGE)
      {
        serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
      }
      
      break;

    default:
      break;
  }
}



void processusVehicule_rotation180(void)
{
    static unsigned long compteurRotation = 0;
    static bool rotationEnCours = false;

    if(!rotationEnCours)
    {
        rotationEnCours = true;
        compteurRotation = millis();

        unsigned long Trecul = millis();
        while (millis() - Trecul < DELAI_RECUL_AVANT_ROTATION)
        {
            serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_recul;
        }

        processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
    }

    serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite;

    if(millis() - compteurRotation >= DELAIROTATION180)
    {
        unsigned long TArrêt = millis();
         while (millis() - TArrêt < DELAI_ATTENTE_AVANT_ROTATION)
        {
           serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
        }

        serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;

        // ==========================================
        //         CAS 1 : 180 depuis LIGNE FIN
        // ==========================================
        if(processusVehicule.CompteurPosi == POSITION_LIGNE_FIN)
        {
            // On repart immédiatement
            processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;

            rotationEnCours = false;
            compteurRotation = 0;
            return;
        }

        // ==========================================
        //         CAS 2 : 180 depuis LIGNE DEBUT
        // ==========================================
        if(processusVehicule.CompteurPosi == POSITION_LIGNE_DEBUT)
        {
            // IMPORTANT : on remet la position au départ
            processusVehicule.CompteurPosi = POSITION_DEPART;

            if(processusVehicule.blocActif == BLOCROUGE)
            {
                // ROUGE => attendre instruction
                serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_AttenteInstruction;
            }
            else  // METAL
            {
                // METAL => repartir en suivi
                processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
                processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
                serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
            }

            rotationEnCours = false;
            compteurRotation = 0;
            return;
        }

        // Autre cas improbable → sécurité
        processusVehicule.CompteurPosi = POSITION_DEPART;
        processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
        serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;

        rotationEnCours = false;
        compteurRotation = 0;
    }
}









void processusVehicule_AttenteInstruction(void)
{
    serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;

    if(serviceWiFiUDP.information == SERVICEWIFIUDP_INFORMATION_DISPONIBLE)
    {
        // === CAS LIGNE FIN ===
        if(processusVehicule.CompteurPosi == POSITION_LIGNE_FIN)
        {
            if(strcmp(serviceWiFiUDP.messageRecu, "Part") == 0)
            {
                serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
            }
        }

        // === CAS LIGNE DEBUT ===
        if(processusVehicule.CompteurPosi == POSITION_DEPART)
        {
            processusVehicule.ancienBloc = processusVehicule.blocActif;

            // NOUVEAU = ROUGE
            if(strcmp(serviceWiFiUDP.messageRecu, "Rouge") == 0)
            {
                processusVehicule.blocActif = BLOCROUGE;

                if(processusVehicule.ancienBloc == BLOCMETAL)    // metal -> rouge = 180
                {
                    serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
                }
                else  // rouge -> rouge = pas 180
                {
                    processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
                    processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
                    serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
                }
            }

            // NOUVEAU = METAL
            if(strcmp(serviceWiFiUDP.messageRecu, "Metal") == 0)
            {
                processusVehicule.blocActif = BLOCMETAL;

                if(processusVehicule.ancienBloc == BLOCMETAL)  // metal -> metal = 180
                {
                    serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
                }
                else  // rouge -> metal = pas 180
                {
                    processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
                    processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
                    serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
                }
            }
        }

        serviceWiFiUDP.information = SERVICEWIFIUDP_INFORMATION_TRAITEE;
    }
}



void processusVehicule_initialise(void)
{
   processusVehicule.blocActif = AUCUNBLOC;
  processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
  processusVehicule.CompteurPosi = POSITION_DEPART;
  processusVehicule.derniereLignePleine = 0;
  serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_gere;
}