#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: 247-616-ESP32
//DESCRIPTION: Programme qui gÃ¨re des fonctionnalitÃ©s de base Ã  l'aide d'une base de temps

//HISTORIQUE:
// 2025-11-18, Harold Kouadio: crÃ©ation

//inclusions globales

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles:
#define PILOTETIMER0_FREQUENCE_DES_PERIPHERIQUES_EN_HZ 80000000
#define PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
#define PILOTEENTREE1_BROCHE 21


#define piloteMoteur1_EN_BROCHE 14
#define piloteMoteur1_IN1_BROCHE 15
#define piloteMoteur1_IN2_BROCHE 32
#define piloteMoteur1_ETAT_INITIAL_A_ZERO

#define piloteMoteur2_EN_BROCHE 12
#define piloteMoteur2_IN1_BROCHE 27
#define piloteMoteur2_IN2_BROCHE 33
#define piloteMoteur2_ETAT_INITIAL_A_ZERO

#define piloteMoteur3_EN_BROCHE 17
#define piloteMoteur3_IN1_BROCHE 19
#define piloteMoteur3_IN2_BROCHE 16
#define piloteMoteur3_ETAT_INITIAL_A_ZERO

#define piloteMoteur4_EN_BROCHE 4
#define piloteMoteur4_IN1_BROCHE 5
#define piloteMoteur4_IN2_BROCHE 18
#define piloteMoteur4_ETAT_INITIAL_A_ZERO

// Moteur 
#define MOTEURAVG 1
#define MOTEURAVD 2
#define MOTEURARG 3
#define MOTEURARD 4
#define ADDRESSPCF 0x22

// WIFIUDP
#define WIFI_SSID "Harold-ESP32-COM" 
#define WIFI_PASSWORD "12345678" 
#define LOCALIPAP "192.168.20.1"
#define GETAWAYAP "192.168.20"
#define SUBNETAP "255.255.255.0"
#define IPDEST "192.168.20.1"
#define PORTDEST 56315


#define PILOTEANALOGUE1_BROCHE A4
#define INTERFACEENTREE1_VALEUR_LUE_SI_ACTIVE  1   
#define INTERFACEENTREE1_VALEUR_LUE_SI_INACTIVE 0
#define INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ  125
#define INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles:
#define SERVICETASKSERVER_PERIODE_EN_US (4000L)
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ ((1000000L)/SERVICETASKSERVER_PERIODE_EN_US)

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 5

#define SERVICEWIFIUDP_PHASE_RECEPTION  0
#define SERVICEWIFIUDP_PHASE_TRANSMISSION 1
#define PROCESSUSVEHICULEPHASE  2
#define PROCESSUSSUIVEURDELIGNEPHASE 3
#define PROCESSUSCONDUITEPHASE 4

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1
//#define PROCESSUSTACHELENTEDANSLOOP_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Variables publiques:
//pas de variables publiques

//Fonctions publiques:
//pas de fonctions publiques

#endif
