#ifndef PROCESSUSCANVERSUART637_H
#define PROCESSUSCANVERSUART637_H

//MODULE: processusCanVersUart637
//DESCRIPTION: transfère les données reçues par serviceCan637
//             vers serviceProtocole637 (CAN -> UART 637)

//HISTORIQUE:
// 2025-12-01, création

//DEFINITIONS REQUISES PAR LE MODULE:
// (à mettre dans main.h)
//
// #define PROCESSUSCANVERSUART637_PHASE   X
//   X = indice libre dans serviceBaseDeTemps_execute[]

//INFORMATION PUBLIQUE:
// pas de variables publiques, seulement une fonction d'init

//Fonctions publiques:
void processusCAN_UART_initialise(void);

#endif
