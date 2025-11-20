#include "main.h"
#include "InterfaceDetecteurDeLigne.h"
#include "ProcessusSuiveurDeLigne.h"
#include "ProcessusConduite.h"
#include "processusVehicule.h"

//**********************************
//Variables Glogales
//***********************************
PROCESSUSSUIVEURDELIGNE processusSuiveurDeLigne;

// ===============================
// Fonctions privées
// ===============================
void processusSuiveurDeLigne_Suit (void);
// ===============================
// Fonctions publiques
// ===============================

void processusSuiveurDeLigne_Suit (void)
{
     if (processusVehicule.controleSuiveur != SUIVEUR_ACTIF)
    {
      return;
    }

if(processusVehicule.controleSuiveur == SUIVEUR_ACTIF)
{

 unsigned int ValeurSuiveur = vLireSuiveurPCF();

if (ValeurSuiveur == 0x08)
{
    processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
   // serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_avance;
}

else if (ValeurSuiveur == 0x10 || ValeurSuiveur == 0x18 || ValeurSuiveur == 0x20 || ValeurSuiveur == 0x30 || ValeurSuiveur == 0x40 || ValeurSuiveur == 0x60)
{
    processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_TOURNEADROITE;
   // serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite;
}

else if (ValeurSuiveur == 0x04 || ValeurSuiveur == 0x06 || ValeurSuiveur == 0x02 || ValeurSuiveur == 0x01 || ValeurSuiveur == 0x03)
{
    processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_TOURNEAGAUCHE;
   // serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneAGauche;
}

if (ValeurSuiveur == 0x7F ) //|| ValeurSuiveur == 0x00)
{
    processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_ARRET;
   // serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
}

if(ValeurSuiveur == 0x00)
{
   processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_PERDU;
}

}

}



void processusSuiveurDeLigne_initialise(void) 
{
  
  vEcrireSuiveurPCF();
  serviceBaseDeTemps_execute[PROCESSUSSUIVEURDELIGNEPHASE] = processusSuiveurDeLigne_Suit;
}