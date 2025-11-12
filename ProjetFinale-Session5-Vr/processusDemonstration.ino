//processusDemonstration:
//Historique: 
// 2021-11-02, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceEntree1.h"
#include "processusTacheLenteDansLoop.h"
#include "processusDemonstration.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void processusDemonstration_attendApresInterfaceEntree1(void);
void processusDemonstration_attendApresProcessusTacheLenteDansLoop(void);
void processusDemonstration_attendUneDemandeDeRequetePourLesTachesLentes(void);
void processusDemonstration_attendApresLaFinDUneTacheLente(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void processusDemonstration_attendApresInterfaceEntree1(void)
{
  if (interfaceEntree1.etatDuModule == INTERFACEENTREE1_MODULE_PAS_EN_FONCTION)
  {
    return;
  }
  serviceBaseDeTemps_execute[PROCESSUSDEMONSTRATION_PHASE] = processusDemonstration_attendApresProcessusTacheLenteDansLoop;  
}

void processusDemonstration_attendApresProcessusTacheLenteDansLoop(void)
{
  if (processusTacheLenteDansLoop.etatDuModule == PROCESSUSTACHELENTEDANSLOOP_MODULE_PAS_EN_FONCTION)
  {
    return;
  }
  if (processusTacheLenteDansLoop.requete == PROCESSUSTACHELENTEDANSLOOP_REQUETE_ACTIVE)
  {
    return;
  }  
  processusDemonstration.etatDuModule = PROCESSUSDEMONSTRATION_MODULE_EN_FONCTION;
  serviceBaseDeTemps_execute[PROCESSUSDEMONSTRATION_PHASE] = processusDemonstration_attendUneDemandeDeRequetePourLesTachesLentes;
}

void processusDemonstration_attendUneDemandeDeRequetePourLesTachesLentes(void)
{
unsigned char valeurLue;
  if (interfaceEntree1.information == INTERFACEENTREE1_INFORMATION_TRAITEE)
  {
    return;
  }
  interfaceEntree1.information = INTERFACEENTREE1_INFORMATION_TRAITEE;
  if (interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_ACTIVE)
  {
    processusTacheLenteDansLoop.message = 'A'; //A comme dans Active
  }
  else
  {
    processusTacheLenteDansLoop.message = 'I'; //I comme dans Inactive
  }
  processusTacheLenteDansLoop.requete = PROCESSUSTACHELENTEDANSLOOP_REQUETE_ACTIVE;
  serviceBaseDeTemps_execute[PROCESSUSDEMONSTRATION_PHASE] = processusDemonstration_attendLaFinDUneTacheLente;   
}

void processusDemonstration_attendLaFinDUneTacheLente(void)
{
  if (processusTacheLenteDansLoop.requete == PROCESSUSTACHELENTEDANSLOOP_REQUETE_ACTIVE)
  {
    return;
  }
  serviceBaseDeTemps_execute[PROCESSUSDEMONSTRATION_PHASE] = processusDemonstration_attendUneDemandeDeRequetePourLesTachesLentes;       
}

//Definitions de variables publiques:
PROCESSUSDEMONSTRATION processusDemonstration;

//Definitions de fonctions publiques:
void processusDemonstration_initialise(void)
{
  processusDemonstration.etatDuModule = PROCESSUSDEMONSTRATION_MODULE_PAS_EN_FONCTION;
  serviceBaseDeTemps_execute[PROCESSUSDEMONSTRATION_PHASE] = processusDemonstration_attendApresInterfaceEntree1;
}
