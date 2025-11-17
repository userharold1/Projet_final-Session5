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
 unsigned int ValeurSuiveur = vLireSuiveurPCF();

 if (ValeurSuiveur == 0b0001000 )
 {
  serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_avance;
 }

 if (ValeurSuiveur == 0b0010000 || ValeurSuiveur == 0b0011000 || ValeurSuiveur == 0b0100000 || ValeurSuiveur == 0b0110000 || ValeurSuiveur == 0b1000000)
{
  serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneAGauche;
}

if (ValeurSuiveur == 0b0000100 || ValeurSuiveur == 0b0000110 || ValeurSuiveur == 0b0000010 || ValeurSuiveur == 0b0000001 || ValeurSuiveur == 0b0000011)
{
    serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_tourneADroite;
}


 if (ValeurSuiveur == 0b0111111 ||  ValeurSuiveur == 0b0000000)     // ligne pleine (tout noir) ou Ligne perdu (tout blanc)
{
    serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
}

}



void processusSuiveurDeLigne_initialise(void) 
{
  
  vEcrireSuiveurPCF();
  serviceBaseDeTemps_execute[PROCESSUSSUIVEURDELIGNEPHASE] = processusSuiveurDeLigne_Suit;
}