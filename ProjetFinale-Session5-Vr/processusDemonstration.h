#ifndef PROCESSUSDEMONSTRATION_H
#define PROCESSUSDEMONSTRATION_H

//MODULE: PROCESSUSDEMONSTRATION
//DESCRIPTION: processus qui montre comment synchroniser des operations gerer par le serviceBaseDeTemps avec celles de la boucle "main"
//i.e synchroniser les taches ordinaires et les taches lentes

//HISTORIQUE:
// 2021-06-29, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSDEMONSTRATION_PHASE 1


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSDEMONSTRATION_MODULE_EN_FONCTION 1
#define PROCESSUSDEMONSTRATION_MODULE_PAS_EN_FONCTION 0

typedef struct
{
  unsigned char etatDuModule;  
} PROCESSUSDEMONSTRATION;

//Fonctions publiques:
void PROCESSUSDEMONSTRATION_initialise(void);

//Variables publiques:
extern PROCESSUSDEMONSTRATION processusDemonstration;

#endif
