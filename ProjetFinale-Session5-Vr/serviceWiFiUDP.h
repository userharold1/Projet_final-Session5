// serviceWiFiUDP.h
// Auteur : Harold pour ProjetFinDeSession
// Service UDP avec machines à états (réception + transmission)

#ifndef SERVICEWIFIUDP_H
#define SERVICEWIFIUDP_H

// INCLUSIONS
#include "main.h"

// CONSTANTES
#define SERVICEWIFIUDP_TAILLE_MESSAGE   255


#define SERVICEWIFIUDP_INFORMATION_DISPONIBLE 1
#define SERVICEWIFIUDP_INFORMATION_TRAITEE    0

#define SERVICEWIFIUDP_REQUETE_TRAITEE 1
#define SERVICEWIFIUDP_REQUETE_A_TRAITER 0


// STRUCTURE DU SERVICE
typedef struct
{
    // --- Réception ---
    char messageRecu[SERVICEWIFIUDP_TAILLE_MESSAGE];
    unsigned char information;

    // --- Transmission ---
    char messageATransmettre[SERVICEWIFIUDP_TAILLE_MESSAGE];
    unsigned char requete;

} SERVICEWIFIUDP;

// OBJET GLOBAL
extern SERVICEWIFIUDP serviceWiFiUDP;

// FONCTIONS PUBLIQUES
void serviceWiFiUDP_initialise(void);

// machines à états
void serviceWiFiUDP_attendUnPacket(void);
void serviceWiFiUDP_attendUneRequete(void);

#endif
