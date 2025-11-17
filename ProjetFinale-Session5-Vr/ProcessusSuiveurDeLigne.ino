#include "main.h"
#include "InterfaceDetecteurDeLigne.h"
#include "ProcessusSuiveurDeLigne.h"
#include "ProcessusConduite.h"
// ===============================
// Fonctions privées
// ===============================
void processusSuiveurDeLigne_Suit (void);
// ===============================
// Fonctions publiques
// ===============================

void processusSuiveurDeLigne_Suit (void)
{
 unsigned int ValeurSuiveur = vLireSuiveurPCF(0x22);

 if (ValeurSuiveur == 0b0001000 )
 {
  serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_avance;
 }
}



void processusSuiveurDeLigne_initialise(void) 
{
  
  vEcrireSuiveurPCF();
  serviceBaseDeTemps_execute[PROCESSUSSUIVEURDELIGNEPHASE] = processusSuiveurDeLigne_Suit;
}