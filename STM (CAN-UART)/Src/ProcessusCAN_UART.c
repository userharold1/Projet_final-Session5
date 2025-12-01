//processusCanVersUart637:
//Historique:
// 2025-12-01, création

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceCan637.h"
#include "serviceProtocole637.h"
#include "processusCAN_UART.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
static void processusCanVersUart637_gere(void);

//Definitions de variables privees:
//pas de variables privees
static unsigned int compteur = 0;
//Definitions de fonctions privees:

// Fonction appelée périodiquement par serviceBaseDeTemps
static void processusCanVersUart637_gere(void)
{
    unsigned char i;

    // TEST: si jamais un message CAN arrive, on envoie "TESTCAN" en UART
    /*if (serviceCan637.information == INFORMATION_DISPONIBLE)
    {
        if (serviceProtocole637.requete == REQUETE_ACTIVE)
        {
            return;
        }

//        // on vide le buffer UART
//        for (i = 0; i < SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
//        {
//            serviceProtocole637.octetsATransmettre[i] = 0;
//        }

        serviceProtocole637.octetsATransmettre[0] = 'T';
        serviceProtocole637.octetsATransmettre[1] = 'E';
        serviceProtocole637.octetsATransmettre[2] = 'S';
        serviceProtocole637.octetsATransmettre[3] = 'T';
        serviceProtocole637.octetsATransmettre[4] = 'C';
        serviceProtocole637.octetsATransmettre[5] = 'A';
        serviceProtocole637.octetsATransmettre[6] = 'N';

        serviceProtocole637.requete = REQUETE_ACTIVE;
        serviceCan637.information = INFORMATION_TRAITEE;
        return;
    }*/


    // Petit diviseur de fréquence : on envoie une trame tous les 100 ticks
    if (++compteur < 100)
    {
        return;
    }
    compteur = 0;

    // Si une trame est déjà en attente de transmission, on attend
    if (serviceCan637.requete == REQUETE_ACTIVE)
    {
        return;
    }

    // Préparer les 8 octets à transmettre : 0x31 ('1') × 8
    for (i = 0; i < 8; i++)
    {
        serviceCan637.octetsATransmettre[i] = 0x31;   // ou '1'
    }

    // Les autres octets au-delà de 8, on les met à 0 par sécurité
    for (; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
    {
        serviceCan637.octetsATransmettre[i] = 0x00;
    }

    // Longueur : 8 octets
    serviceCan637.nombreATransmettre = 8;

    // Demander la transmission CAN au service
    serviceCan637.requete = REQUETE_ACTIVE;

    // (le reste de ta logique plus intelligente après)
}

//Definitions de fonctions publiques:

void processusCAN_UART_initialise(void)
{
  // Inscription du processus dans le service de base de temps
  serviceBaseDeTemps_execute[PROCESSUSCAN_UART_PHASE] =
      processusCanVersUart637_gere;
}
