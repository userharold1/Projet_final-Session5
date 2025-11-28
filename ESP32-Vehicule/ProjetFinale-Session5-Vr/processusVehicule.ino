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
#define DELAIROTATION180 2100
#define DELAIROTATION90  500
#define DELAI_RECUL_AVANT_ROTATION 200
//#define DELAI_ATTENTE_AVANT_ROTATION 2000
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
    /*else if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_PERDU)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
    }*/

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
    static unsigned long debutAction = 0;
    static uint8_t etape = 0;

    // Étape 0 : RECUL non bloquant
    if(etape == 0)
    {
        if(debutAction == 0)
        {
            debutAction = millis();
            processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
        }

        serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_recul;

        if(millis() - debutAction >= DELAI_RECUL_AVANT_ROTATION)
        {
            etape = 1;
            debutAction = millis();
        }
       return;
    }

    // Étape 1 : ROTATION non bloquante
    if(etape == 1)
    {
        serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite;

        if(millis() - debutAction >= DELAIROTATION180)
        {
            etape = 2;
            debutAction = 0;
        }
        return;
    }


    // Étape 2 : FIN DE ROTATION
    if(etape == 2)
    {
        serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;

        // On revient entre DEBUT et MILIEU
        
        processusVehicule.derniereLignePleine = 1;

       if(processusVehicule.CompteurPosi == POSITION_LIGNE_FIN)
       {
        processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
        processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
        serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
       }
      else if(processusVehicule.CompteurPosi == POSITION_LIGNE_DEBUT)
      {
          if(processusVehicule.blocActif == BLOCROUGE)
        {
            processusVehicule.CompteurPosi = POSITION_DEPART;
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_AttenteInstruction;
            
        }
        else
        {
            processusVehicule.CompteurPosi = POSITION_DEPART;
            processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
            serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
        }

      }
    else if(processusVehicule.CompteurPosi == POSITION_DEPART)
    {
        // 180 lancé depuis AttenteInstruction (cas metal -> rouge ou metal -> metal)
        // → après rotation, on veut SUIVRE la ligne
        processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
        processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
        serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
    }
        
        // RESET pour la prochaine fois
        etape = 0;
        return;
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
        if ((processusVehicule.CompteurPosi == POSITION_DEPART) || (processusVehicule.CompteurPosi == POSITION_LIGNE_DEBUT))
        {
            processusVehicule.ancienBloc = processusVehicule.blocActif;

            // NOUVEAU = ROUGE
            if(strcmp(serviceWiFiUDP.messageRecu, "Rouge") == 0)
            {
                processusVehicule.blocActif = BLOCROUGE;

                if(processusVehicule.ancienBloc == BLOCMETAL)    // metal -> rouge = 180
                {
                  processusVehicule.CompteurPosi = POSITION_DEPART;
                    serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
                }
                else if(processusVehicule.ancienBloc == BLOCROUGE)  // rouge -> rouge = pas 180
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