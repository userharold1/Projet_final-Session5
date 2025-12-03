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
void processusCAN_UART_gere(void);
void processusTestCAN_gere(void);
//Definitions de variables privees:
//pas de variables privees

// ---------------------------------------------------------------------
//  (OPTION) VERSION TEST ÉMISSION : UART -> CAN (pour l'autre STM)
// ---------------------------------------------------------------------
// Si tu veux utiliser cette STM comme "émetteur CAN de test",
// tu peux commenter la fonction au-dessus et décommenter celle-ci :
void processusTestCAN_gere(void)
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
    serviceProtocole637.octetsATransmettre[0] = 'T';
    serviceProtocole637.octetsATransmettre[1] = 'E';
    serviceProtocole637.octetsATransmettre[2] = 'S';
    serviceProtocole637.octetsATransmettre[3] = 'T';
    serviceProtocole637.octetsATransmettre[4] = 'C';
    serviceProtocole637.octetsATransmettre[5] = 'A';
    serviceProtocole637.octetsATransmettre[6] = 'N';
    // ici ton action
// 5) Demander l’envoi UART via serviceProtocole637
    serviceProtocole637.requete = REQUETE_ACTIVE;

}

    // 6) Marquer le message CAN comme traité pour ne pas renvoyer en boucle
    serviceCan637.information = INFORMATION_TRAITEE;
  
}


void processusCAN_UART_gere(void)
{
    unsigned char i;
    static unsigned int compteur = 0 ;

    // Petit diviseur de fréquence : on envoie une trame tous les 100 ticks
    if (++compteur < 100)
    {
        return;
    }
    compteur = 0;

    // Si une trame CAN est déjà en attente de transmission, on attend
    if (serviceCan637.requete == REQUETE_ACTIVE)
    {
        return;
    }

    // Préparer les 8 octets à transmettre : 0x31 ('1') × 8
    for (i = 0; i < 8; i++)
    {
        serviceCan637.octetsATransmettre[i] = 0x31;   // '1'
    }

    // Zero du reste du buffer serviceCan637 (optionnel)
    for (; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
    {
        serviceCan637.octetsATransmettre[i] = 0x00;
    }

    // Longueur : 8 octets
    serviceCan637.nombreATransmettre = 8;

    // Demander la transmission CAN au service
    serviceCan637.requete = REQUETE_ACTIVE;
}


//Definitions de fonctions publiques:
void processusCAN_UART_initialise(void)
{
  // Inscription du processus dans le service de base de temps
  serviceBaseDeTemps_execute[PROCESSUSCAN_UART_PHASE] =
      processusCAN_UART_gere;
}
