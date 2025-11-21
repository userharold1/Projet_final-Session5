#ifndef PILOTEUART_H
#define PILOTEUART_H

//MODULE: piloteUART
//DESCRIPTION: pour utiliser le USART2
//HISTORIQUE:
// 2025-11-21, Harold Kouadio, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielle
//pas de d�pendances mat�rielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de d�pendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PILOTEUART_DISPONIBLE  1
#define PILOTEUART_PAS_DISPONIBLE 0
#define PILOTEUART_TRANSMIS 0
#define PILOTEUART_PAS_TRANSMIS 1

//Fonctions publiques:
void piloteUART_initialise(void);
unsigned char piloteUART_octetDisponible(void);
unsigned char piloteUART_octetTransmis(void);
unsigned char piloteUART_litUnOctetRecu(void);
void piloteUART_transmet(unsigned char Octet);

//Variables publiques:
//pas de variables publiques

#endif
