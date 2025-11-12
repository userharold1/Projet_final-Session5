//processusTacheLenteDansLoop:
//Historique: 
// 2021-11-02, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "processusTacheLenteDansLoop.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void processusTacheLenteDansLoop_attendUneRequete(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void processusTacheLenteDansLoop_attendUneRequete(void)
{
  if (processusTacheLenteDansLoop.requete == PROCESSUSTACHELENTEDANSLOOP_REQUETE_TRAITEE)
  {
    return;
  }
  delay(500); //on s'assure que la tache est lente pour que la demonstration soit concluante
  printf("Voici le message: %c\n", processusTacheLenteDansLoop.message);
  delay(500);
  processusTacheLenteDansLoop.requete = PROCESSUSTACHELENTEDANSLOOP_REQUETE_TRAITEE;
}

//Definitions de variables publiques:
PROCESSUSTACHELENTEDANSLOOP processusTacheLenteDansLoop;

//Definitions de fonctions publiques:
void processusTacheLenteDansLoop_initialise(void)
{
  processusTacheLenteDansLoop.requete = PROCESSUSTACHELENTEDANSLOOP_REQUETE_TRAITEE;
  processusTacheLenteDansLoop.etatDuModule = PROCESSUSTACHELENTEDANSLOOP_MODULE_EN_FONCTION;
  serviceBaseDeTemps_executeDansLoop[PROCESSUSTACHELENTEDANSLOOP_PHASE] = processusTacheLenteDansLoop_attendUneRequete;
}
