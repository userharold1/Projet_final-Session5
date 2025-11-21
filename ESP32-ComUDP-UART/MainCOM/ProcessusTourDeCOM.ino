#include "main.h"
#include "serviceBaseDeTemps.h"
#include "ProcessusTourDeCOM.h"
#include "serviceProtocole637.h"
#include "serviceWiFiUDP.h"

// ===============================
// Fonctions privées
// ===============================


// ===============================
// Fonctions publiques
// ===============================

// ---------------- MACHINE A ETATS ------------------

// --------------------------------------------------------
// PHASE 1 : ATTENDRE UN MESSAGE UDP
// --------------------------------------------------------

void processusTourDeCOM_attendUneRequete(void)
{
    // On attend un paquet UDP disponible
    if (serviceWiFiUDP.information != INFORMATION_DISPONIBLE)
    {
        return;
    }

    // Passe à la prochaine étape : copie
    serviceBaseDeTemps_execute[PROCESSUSTOURDECOM_TRANSMISSION_PHASE] = processusTourDeCOM_TransmissionUART;
}

// --------------------------------------------------------
// PHASE 2 : COPIER MESSAGE UDP → protocole637
// --------------------------------------------------------

void processusTourDeCOM_TransmissionUART(void)
{
    // Copier le message texte UDP dans les octets du protocole
    int i;
      // Copier jusqu'à la fin de la chaîne ou jusqu'à la limite 637
    for (i = 0; i < SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM && serviceWiFiUDP.messageRecu[i] != '\0'; i++)
    {
      serviceProtocole637.octetsATransmettre[i] = (unsigned char)serviceWiFiUDP.messageRecu[i];
    }
      // Remplir le reste avec 0 pour effacer l’ancien contenu
    for (; i < SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
    {
        serviceProtocole637.octetsATransmettre[i] = 0;
    }

    // Indiquer au protocole qu’une transmission est demandée
    serviceProtocole637.requete = REQUETE_ACTIVE;

    // Le paquet UDP est consommé → on l’efface
    serviceWiFiUDP.information = INFORMATION_TRAITEE;

    // Retourner en attente
    serviceBaseDeTemps_execute[PROCESSUSTOURDECOM_TRANSMISSION_PHASE] = processusTourDeCOM_attendUneRequete;
}


void processusTourDeCOM_AttendReceptionUART(void)
{
    if (serviceProtocole637.information != INFORMATION_DISPONIBLE)
    {
        return;
    }
    
    // Une trame UART complète a été reçue !
    serviceBaseDeTemps_execute[PROCESSUSTOURDECOM_RECEPTION_PHASE] = processusTourDeCOM_ReceptionUART;
}


void processusTourDeCOM_ReceptionUART(void)
{
    // Copier la trame reçue vers messageATransmettre
    int i;
    for (i = 0; i < serviceProtocole637.nombreARecevoir && i < SERVICEWIFIUDP_TAILLE_MESSAGE - 1; i++)
    {
        serviceWiFiUDP.messageATransmettre[i] = (char)serviceProtocole637.octetsRecus[i];
    }

     // Effacer le reste (évite les résidus si trame plus courte)
    for (int j = i; j < SERVICEWIFIUDP_TAILLE_MESSAGE; j++)
    {
        serviceWiFiUDP.messageATransmettre[j] = '\0';
    }


    // Déclencher la transmission UDP
    serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_A_TRAITER;

    // Marquer la trame UART comme traitée
    serviceProtocole637.information = INFORMATION_TRAITEE;

    // Retour à l'attente
    serviceBaseDeTemps_execute[PROCESSUSTOURDECOM_RECEPTION_PHASE] =
        processusTourDeCOM_AttendReceptionUART;
}



// --------------------------------------------------------
// INITIALISATION DU PROCESSUS
// --------------------------------------------------------

void processusTourDeCOM_initialise(void) 
{
   serviceBaseDeTemps_execute[PROCESSUSTOURDECOM_TRANSMISSION_PHASE] = processusTourDeCOM_attendUneRequete;
   serviceBaseDeTemps_execute[PROCESSUSTOURDECOM_RECEPTION_PHASE] = processusTourDeCOM_AttendReceptionUART;

}