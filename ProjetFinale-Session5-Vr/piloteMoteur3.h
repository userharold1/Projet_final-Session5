#ifndef piloteMoteur3_H
#define piloteMoteur3_H

//MODULE: piloteMoteur1
//DESCRIPTION: pour permettre la commande d'une sortie
// 2025-11-12, Harold Kouadio, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define piloteMoteur1_BROCHE 13
//#define piloteMoteur1_ETAT_INITIAL_A_UN
//#define piloteMoteur1_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteMoteur3_EN_metA(unsigned char Niveau);
void piloteMoteur3_IN1_metA(unsigned char Niveau);
void piloteMoteur3_IN2_metA(unsigned char Niveau);
void piloteMoteur3_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
