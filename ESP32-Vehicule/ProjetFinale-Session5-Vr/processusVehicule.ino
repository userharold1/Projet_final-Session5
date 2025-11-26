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
#define DELAIROTATION180 1900
#define DELAIROTATION90  1000

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
      
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;

      if(processusVehicule.blocActif == BLOCMETAL)
      {
       strcpy(serviceWiFiUDP.messageATransmettre, "MilieuR");
       serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_A_TRAITER;
       processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
       serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
      }
      else if(processusVehicule.blocActif == BLOCROUGE)
      {
        processusVehicule.retoune = ACTIF;
        processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
        serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
      }
      
      
      break;

    case POSITION_LIGNE_DEBUT:
      strcpy(serviceWiFiUDP.messageATransmettre, "Pese");
      serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_A_TRAITER;
      // Arrivé à la ligne début → rotation 180° puis réinitialiser
      processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;
      processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_AttenteInstruction;
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
  if(millis() - compteurRotation >= DELAIROTATION180) 
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
    if(processusVehicule.retoune == NON_ACTIF)
    {
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_Suit;
    }
    else if(processusVehicule.retoune == ACTIF)
    {
      serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_SuitEnRecul;
    }
    
  }
}

void processusVehicule_SuitEnRecul(void)
{
    if(processusVehicule.controleSuiveur == SUIVEUR_ACTIF)
    {
        // --- LOGIQUE DE SUIVI EN RECUL ---
        // PAS D'INVERSION car rotation sur place fonctionne dans les 2 sens
        
        if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_AVANCE)
        {
            // Ligne centrée : reculer droit
          serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_recul_lent;
        }
        else if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_TOURNEADROITE)
        {
            // Garder tourneADroite (rotation sur place)
            serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite_vitesseFaible;
        }
        else if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_TOURNEAGAUCHE)
        {
            // Garder tourneAGauche (rotation sur place)
            serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneAGauche_vitesseFaible;
        }
        else if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_PERDU)
        {
            // Ligne perdue → arrêt
            serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
        }

        // --- DÉTECTION DE LIGNE PLEINE ---
        if(processusSuiveurDeLigne.Direction == PROCESSUSSUIVEURLIGNE_ARRET)
        {
            // Incrémenter uniquement à la première détection
            if(processusVehicule.derniereLignePleine == 0)
            {
                processusVehicule.CompteurPosi++;
            }
            processusVehicule.derniereLignePleine = 1;

            // --- ARRIVÉE À LA LIGNE DE DÉBUT ---
            if(processusVehicule.CompteurPosi == POSITION_LIGNE_DEBUT)
            {
                // ARRÊT COMPLET
                serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;

                // Envoyer confirmation de pesée
                strcpy(serviceWiFiUDP.messageATransmettre, "Pese");
                serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_A_TRAITER;

                // RESET COMPLET pour nouveau cycle
                processusVehicule.CompteurPosi = POSITION_DEPART;
                processusVehicule.derniereLignePleine = 0;
                processusVehicule.retoune = NON_ACTIF;
                processusVehicule.controleSuiveur = SUIVEUR_NON_ACTIF;

                // Retour à l'état d'attente d'instruction
                serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_gere;
                return;
            }

            // --- SI CE N'EST PAS LA LIGNE DE DÉBUT ---
            // Continuer à reculer en ignorant les lignes intermédiaires
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
        }
        else
        {
            // La ligne n'est plus pleine → reset du flag
            processusVehicule.derniereLignePleine = 0;
        }
    }
}





void processusVehicule_AttenteInstruction(void)
{
    // Toujours arrêter les moteurs ici
    serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;

    // Vérifier si un message UDP est disponible
    if(serviceWiFiUDP.information == SERVICEWIFIUDP_INFORMATION_DISPONIBLE)
    {
        if((strcmp(serviceWiFiUDP.messageRecu, "Part") == 0))
        {
          if(processusVehicule.CompteurPosi == POSITION_LIGNE_FIN )
          {
             serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_rotation180;
          }   
         /* else if(processusVehicule.CompteurPosi == POSITION_LIGNE_DEBUT)
          {
           
          }*/
        }

        // Toujours vider le buffer UDP
        serviceWiFiUDP.information = SERVICEWIFIUDP_INFORMATION_TRAITEE;
    }
}


void processusVehicule_initialise(void)
{
  processusVehicule.retoune = NON_ACTIF;
  processusVehicule.controleSuiveur = SUIVEUR_ACTIF;
  processusVehicule.CompteurPosi = POSITION_DEPART;
  processusVehicule.derniereLignePleine = 0;
  serviceBaseDeTemps_execute[PROCESSUSVEHICULEPHASE] = processusVehicule_gere;
}