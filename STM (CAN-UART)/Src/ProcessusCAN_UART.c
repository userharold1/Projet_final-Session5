//processusCAN_UART:
//Historique:
// 2025-12-01, création

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceCan637.h"
#include "piloteCAN1.h"
#include "serviceProtocole637.h"
#include "processusCAN_UART.h"

//Déclarations de fonctions privées:
void processusCAN_UART_uartVersCan(void);
void processusCAN_UART_canVersUart(void);
//Definitions de variables privees:
//pas de variables privees

// ---------------------------------------------------------------------
//  (OPTION) VERSION TEST ÉMISSION : UART -> CAN (pour l'autre STM)
// ---------------------------------------------------------------------
// Si tu veux utiliser cette STM comme "émetteur CAN de test",
// tu peux commenter la fonction au-dessus et décommenter celle-ci :
/*void processusTestCAN_gere(void)
{
  unsigned char i;
  
  // 1) Attendre un nouveau message CAN (serviceCan637 a rempli octetsRecus[])
  if (serviceCan637.information != INFORMATION_DISPONIBLE)
  {
    return;
  }
  
  // 2) Si une trame UART 637 est déjà en transmission, on attend
  if (serviceProtocole637.requete == REQUETE_ACTIVE)
  {
    return;
  }
  
  // (Option : ici tu peux lire serviceCan637.octetsRecus[]
  //  pour choisir un message différent selon ce qui vient du CAN)
  
  // 3) Vider le buffer d'envoi du protocole 637
  for (i = 0; i < SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
  {
    serviceProtocole637.octetsATransmettre[i] = 0;
  }
  
  if ( (serviceCan637.octetsRecus[0] == 0x31) &&
      (serviceCan637.octetsRecus[1] == 0x31) &&
        (serviceCan637.octetsRecus[2] == 0x31) &&
          (serviceCan637.octetsRecus[3] == 0x31) &&
            (serviceCan637.octetsRecus[4] == 0x31) &&
              (serviceCan637.octetsRecus[5] == 0x31) &&
                (serviceCan637.octetsRecus[6] == 0x31) &&
                  (serviceCan637.octetsRecus[7] == 0x31))
  { 
    // 4) Mettre "TESTCAN"
    serviceProtocole637.octetsATransmettre[0] = 'M';
    serviceProtocole637.octetsATransmettre[1] = 'e';
    serviceProtocole637.octetsATransmettre[2] = 't';
    serviceProtocole637.octetsATransmettre[3] = 'a';
    serviceProtocole637.octetsATransmettre[4] = 'l';
    // ici ton action
    // 5) Demander l’envoi UART via serviceProtocole637
    serviceProtocole637.requete = REQUETE_ACTIVE;
    
  }
  



    // 6) Marquer le message CAN comme traité pour ne pas renvoyer en boucle
    serviceCan637.information = INFORMATION_TRAITEE;
  
}*/

// =======================
// UART -> CAN
// =======================

void processusCAN_UART_uartVersCan(void)
{
    unsigned char i;

    // Nouveau message UART 637 ?
    if (serviceProtocole637.information != INFORMATION_DISPONIBLE)
    {
        return;
    }

    // CAN déjà occupé ?
    if (serviceCan637.requete == REQUETE_ACTIVE)
    {
        return;
    }

    // Erreur dans la trame UART ?
    if (serviceProtocole637.statut != SERVICEPROTOCOLE637_PAS_D_ERREURS)
    {
        serviceProtocole637.information = INFORMATION_TRAITEE;
        return;
    }

    // ============================
    //  CAS 1 : Millieu
    // ============================
    if ( (serviceProtocole637.octetsRecus[0] == 'M') &&
         (serviceProtocole637.octetsRecus[1] == 'i') &&
         (serviceProtocole637.octetsRecus[2] == 'l') &&
         (serviceProtocole637.octetsRecus[3] == 'i') &&
         (serviceProtocole637.octetsRecus[4] == 'e') &&
         (serviceProtocole637.octetsRecus[5] == 'u'))
    {
        // 1) Choisir l'ID CAN
        serviceCan637.idATransmettre = CAN_ID_POSITIONNEMENT;   // 0x100

        // 2) Remplir le buffer CAN avec la lettre à envoyer ('C')
        for (i = 0; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
        {
          serviceCan637.octetsATransmettre[i] = 'C';
        }

       
        serviceCan637.nombreATransmettre = SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM;

        // 4) On lance la transmission CAN
        serviceCan637.requete = REQUETE_ACTIVE;

        // 5) On a consommé le message UART
        serviceProtocole637.information = INFORMATION_TRAITEE;
        return;
    }

    // ============================
    //  CAS 2 : Pesee
    // ============================
     if ((serviceProtocole637.octetsRecus[0] == 'P') &&
         (serviceProtocole637.octetsRecus[1] == 'e') &&
         (serviceProtocole637.octetsRecus[2] == 's') &&
         (serviceProtocole637.octetsRecus[3] == 'e') &&
         (serviceProtocole637.octetsRecus[4] == 'e') )
    {
     

        // 1) Choisir l'ID CAN
        serviceCan637.idATransmettre = CAN_ID_POSITIONNEMENT;   // 0x100

        // 2) Remplir le buffer CAN avec la lettre à envoyer ('B')
        for (i = 0; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
        {
          serviceCan637.octetsATransmettre[i] = 'B';
        }

     
        serviceCan637.nombreATransmettre = SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM;

        // 4) On lance la transmission CAN
        serviceCan637.requete = REQUETE_ACTIVE;

        // 5) On a consommé le message UART
        serviceProtocole637.information = INFORMATION_TRAITEE;
        return;
    }

    // ============================
    //  CAS 3 : TRI
    // ============================
     if ((serviceProtocole637.octetsRecus[0] == 'T') &&
         (serviceProtocole637.octetsRecus[1] == 'r') &&
         (serviceProtocole637.octetsRecus[2] == 'i') )
    {
        // 1) Choisir l'ID CAN
        serviceCan637.idATransmettre = CAN_ID_POSITIONNEMENT;   // 0x100

        // 2) Remplir le buffer CAN avec la lettre à envoyer ('U')
        for (i = 0; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
        {
          serviceCan637.octetsATransmettre[i] = 'U';
        }

     
        serviceCan637.nombreATransmettre = SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM;

        // 4) On lance la transmission CAN
        serviceCan637.requete = REQUETE_ACTIVE;

        // 5) On a consommé le message UART
        serviceProtocole637.information = INFORMATION_TRAITEE;
        return;
    }
    
    
    // ============================
    //  CAS 4 : ERREUR 
    // ============================
     if((serviceProtocole637.octetsRecus[0] == 'E') &&
        (serviceProtocole637.octetsRecus[1] == 'r') &&
        (serviceProtocole637.octetsRecus[2] == 'r') &&
        (serviceProtocole637.octetsRecus[3] == 'e') &&
        (serviceProtocole637.octetsRecus[4] == 'u') &&
        (serviceProtocole637.octetsRecus[5] == 'r'))
    {
        // ID CAN = Erreur (0x106)
        serviceCan637.idATransmettre = CAN_ID_ERREUR;

        // On remplit tout le buffer avec 'E'
        for (i = 0; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
        {
            serviceCan637.octetsATransmettre[i] = 'E';
        }

        serviceCan637.nombreATransmettre = SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM;
        serviceCan637.requete            = REQUETE_ACTIVE;
        serviceProtocole637.information  = INFORMATION_TRAITEE;
        return;
    }
    
   serviceProtocole637.information = INFORMATION_TRAITEE;  
}



// =======================
// CAN -> UART
// =======================
void processusCAN_UART_canVersUart(void)
{
    unsigned char i;

    // Nouveau message CAN dispo ?
    if (serviceCan637.information != INFORMATION_DISPONIBLE)
    {
        return;
    }

    // UART déjà en émission ?
    if (serviceProtocole637.requete == REQUETE_ACTIVE)
    {
        return;
    }

    // Erreur CAN ?
    if (serviceCan637.statut != SERVICECAN637_PAS_D_ERREURS)
    {
        serviceCan637.information = INFORMATION_TRAITEE;
        return;
    }
    
    

    if (serviceCan637.octetsRecus[0] == 'O' &&
        serviceCan637.octetsRecus[1] == 'O' &&
        serviceCan637.octetsRecus[2] == 'O' &&
        serviceCan637.octetsRecus[3] == 'O' &&
        serviceCan637.octetsRecus[4] == 'O' &&
        serviceCan637.octetsRecus[5] == 'O' &&
        serviceCan637.octetsRecus[6] == 'O' &&
        serviceCan637.octetsRecus[7] == 'O')
    {
        // On veut envoyer "Rouge" en UART via serviceProtocole637

        // Nettoyer le buffer TX UART
        for (i = 0; i < SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
        {
            serviceProtocole637.octetsATransmettre[i] = 0;
        }

        serviceProtocole637.octetsATransmettre[0] = 'R';
        serviceProtocole637.octetsATransmettre[1] = 'o';
        serviceProtocole637.octetsATransmettre[2] = 'u';
        serviceProtocole637.octetsATransmettre[3] = 'g';
        serviceProtocole637.octetsATransmettre[4] = 'e';

     

        serviceProtocole637.requete    = REQUETE_ACTIVE;
        serviceCan637.information      = INFORMATION_TRAITEE;
        return;
    }
    
    
    

    if (serviceCan637.octetsRecus[0] == 'M' &&
        serviceCan637.octetsRecus[1] == 'M' &&
        serviceCan637.octetsRecus[2] == 'M' &&
        serviceCan637.octetsRecus[3] == 'M' &&
        serviceCan637.octetsRecus[4] == 'M' &&
        serviceCan637.octetsRecus[5] == 'M' &&
        serviceCan637.octetsRecus[6] == 'M' &&
        serviceCan637.octetsRecus[7] == 'M')
    {
        // On veut envoyer "Rouge" en UART via serviceProtocole637

        // Nettoyer le buffer TX UART
        for (i = 0; i < SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
        {
            serviceProtocole637.octetsATransmettre[i] = 0;
        }

        serviceProtocole637.octetsATransmettre[0] = 'M';
        serviceProtocole637.octetsATransmettre[1] = 'e';
        serviceProtocole637.octetsATransmettre[2] = 't';
        serviceProtocole637.octetsATransmettre[3] = 'a';
        serviceProtocole637.octetsATransmettre[4] = 'l';

 

        serviceProtocole637.requete    = REQUETE_ACTIVE;
        serviceCan637.information      = INFORMATION_TRAITEE;
        return;
    }
    

    // Si rien ne matche, on marque tout de même comme traité
    serviceCan637.information = INFORMATION_TRAITEE;
}




//Definitions de fonctions publiques:
void processusCAN_UART_initialise(void)
{
  // Inscription du processus dans le service de base de temps
  serviceBaseDeTemps_execute[PROCESSUSCAN_UART_PHASE_UARTCAN] =
      processusCAN_UART_uartVersCan;
  
  serviceBaseDeTemps_execute[PROCESSUSCAN_UART_PHASE_CANUART] =
      processusCAN_UART_canVersUart;
}
