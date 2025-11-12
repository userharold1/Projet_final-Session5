#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: 247-616-ESP32
//DESCRIPTION: Programme qui gÃ¨re des fonctionnalitÃ©s de base Ã  l'aide d'une base de temps

//HISTORIQUE:
// 2021-10-31, Yves Roy: crÃ©ation

//inclusions globales

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles:
#define PILOTETIMER0_FREQUENCE_DES_PERIPHERIQUES_EN_HZ 80000000
#define PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
#define PILOTEENTREE1_BROCHE 21


#define piloteMoteur1_EN_BROCHE 13
#define piloteMoteur1_IN1_BROCHE 12
#define piloteMoteur1_IN2_BROCHE 27
#define piloteMoteur1_ETAT_INITIAL_A_ZERO

#define piloteMoteur2_EN_BROCHE 33
#define piloteMoteur2_IN1_BROCHE 15
#define piloteMoteur2_IN2_BROCHE 32
#define piloteMoteur2_ETAT_INITIAL_A_ZERO

#define piloteMoteur3_EN_BROCHE 14
#define piloteMoteur3_IN1_BROCHE 34
#define piloteMoteur3_IN2_BROCHE 39
#define piloteMoteur3_ETAT_INITIAL_A_ZERO

#define piloteMoteur4_EN_BROCHE 39
#define piloteMoteur4_IN1_BROCHE 36
#define piloteMoteur4_IN2_BROCHE 4
#define piloteMoteur4_ETAT_INITIAL_A_ZERO

#define PILOTEANALOGUE1_BROCHE A4
#define INTERFACEENTREE1_VALEUR_LUE_SI_ACTIVE  1   
#define INTERFACEENTREE1_VALEUR_LUE_SI_INACTIVE 0
#define INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ  125
#define INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles:
#define SERVICETASKSERVER_PERIODE_EN_US (4000L)
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ ((1000000L)/SERVICETASKSERVER_PERIODE_EN_US)

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 2
#define INTERFACEENTREE1_PHASE 0
#define PROCESSUSDEMONSTRATION_PHASE 1

#define PROCESSUSWIFITRANSMISION_PHASE 2
#define PROCESSUSWIFIRECEPTION_PHASE 3

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1
#define PROCESSUSTACHELENTEDANSLOOP_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Variables publiques:
//pas de variables publiques

//Fonctions publiques:
//pas de fonctions publiques

#endif
