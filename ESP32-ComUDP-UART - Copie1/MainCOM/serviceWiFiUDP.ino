// serviceWiFiUDP.c
// Service UDP simple avec machines à états RX/TX

#include "main.h"
#include "piloteWiFiUDP.h"
#include "serviceBaseDeTemps.h"
#include "serviceWiFiUDP.h"

// OBJET GLOBAL
SERVICEWIFIUDP serviceWiFiUDP;

// -------------------------
// MACHINE À ÉTATS RÉCEPTION
// -------------------------
void serviceWiFiUDP_attendUnPacket(void)
{
  if(serviceWiFiUDP.information == SERVICEWIFIUDP_INFORMATION_DISPONIBLE)
  {
    return; 
  }

  if (serviceWiFiUDP.information == SERVICEWIFIUDP_INFORMATION_TRAITEE)
  {
   // Lire tout paquet UDP s'il y en a un
    char *message = piloteWiFiUDP_litRecu();
    
    // 0 = pas de paquet → rien à faire
    if (message[0] == '\0')
    {
        return;
    }

 
    // Copier le message reçu dans le service
    strncpy(serviceWiFiUDP.messageRecu, message, SERVICEWIFIUDP_TAILLE_MESSAGE - 1);
    serviceWiFiUDP.messageRecu[SERVICEWIFIUDP_TAILLE_MESSAGE - 1] = '\0';

     // Indiquer au processus qu'un message est disponible
    serviceWiFiUDP.information = SERVICEWIFIUDP_INFORMATION_DISPONIBLE;
    
   
  }
    
}


// -------------------------
// MACHINE À ÉTATS TRANSMISSION
// -------------------------
void serviceWiFiUDP_attendUneRequete(void)
{
    // Aucune requête → retourner immédiatement
    if (serviceWiFiUDP.requete == SERVICEWIFIUDP_REQUETE_TRAITEE)
    {
        return;
    }

    // Transmettre le message texte (char[])
  piloteWiFiUDP_Transmet(serviceWiFiUDP.messageATransmettre);

    // Marquer la requête comme traitée
    serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_TRAITEE;
}



// -------------------------
// INITIALISATION DU SERVICE
// -------------------------
void serviceWiFiUDP_initialise(void)
{
    // Aucune info reçue
    serviceWiFiUDP.information = SERVICEWIFIUDP_INFORMATION_TRAITEE;

    // Aucune requête 
    serviceWiFiUDP.requete = SERVICEWIFIUDP_REQUETE_TRAITEE;

    // État rx et tx :
    serviceBaseDeTemps_execute[SERVICEWIFIUDP_PHASE_RECEPTION] = serviceWiFiUDP_attendUnPacket;
    serviceBaseDeTemps_execute[SERVICEWIFIUDP_PHASE_TRANSMISSION] = serviceWiFiUDP_attendUneRequete;
}
