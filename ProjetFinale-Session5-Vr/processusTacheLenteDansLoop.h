#ifndef PROCESSUSTACHELENTEDANSLOOP_H
#define PROCESSUSTACHELENTEDANSLOOP_H

//MODULE: PROCESSUSTACHELENTEDANSLOOP
//DESCRIPTION: processus qui realise une tache lente sur demande alors qu'il fait parvenir
//au pc des messages a l'aide de l'instruction printf lorsqu'un requete lui est formule

//HISTORIQUE:
// 2021-06-29, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSTACHELENTEDANSLOOP_PHASE 1

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSTACHELENTEDANSLOOP_MODULE_EN_FONCTION 1
#define PROCESSUSTACHELENTEDANSLOOP_MODULE_PAS_EN_FONCTION 0
#define PROCESSUSTACHELENTEDANSLOOP_REQUETE_ACTIVE 1
#define PROCESSUSTACHELENTEDANSLOOP_REQUETE_TRAITEE 0

typedef struct
{
  unsigned char etatDuModule;
  unsigned char message;
  unsigned char requete; 
} PROCESSUSTACHELENTEDANSLOOP;

//Fonctions publiques:
void PROCESSUSTACHELENTEDANSLOOP_initialise(void);

//Variables publiques:
extern PROCESSUSTACHELENTEDANSLOOP processusTacheLenteDansLoop;

#endif
