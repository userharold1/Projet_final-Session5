#ifndef SERVICECAN637_H
#define SERVICECAN637_H

//MODULE: serviceCan637
//DESCRIPTION: implemente un service de communication 247-637 via le CAN1
//             en utilisant le pilote piloteCAN1 et le service de base de temps.

//HISTORIQUE:
// 2025-11-28, adaptation à partir de serviceProtocole637

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
// (copiez et adaptez ce qui suit dans "main.h")
// pas de dependances materielles

//Dependances logicielles
// (copiez et adaptez ce qui suit dans "main.h")
// #define SERVICECAN637_PHASE_RECEPTION      0
// #define SERVICECAN637_PHASE_TRANSMISSION   1
// #define SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM  8  // max CAN = 8

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define SERVICECAN637_PAS_D_ERREURS            0
#define SERVICECAN637_ERREUR_TRANSMISSION      1
#define SERVICECAN637_ERREUR_RECEPTION         2
#define SERVICECAN637_ERREUR_LONGUEUR_INVALIDE 3

typedef struct
{
  unsigned char etatDuModuleDeReception;  
  unsigned char information;
  unsigned char octetsRecus[SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char requete;
  unsigned char nombreATransmettre;
  unsigned char octetsATransmettre[SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char nombreARecevoir;
  unsigned char statut;
} SERVICECAN637;

//Fonctions publiques:
void serviceCan637_initialise(void);

//Variables publiques:
extern SERVICECAN637 serviceCan637;

#endif
