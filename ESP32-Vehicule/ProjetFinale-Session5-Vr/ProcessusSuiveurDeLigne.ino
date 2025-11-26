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


if(processusVehicule.retoune != ACTIF)
{
   
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


if(processusVehicule.retoune == ACTIF)
    {
        // ✅ NOUVELLE LOGIQUE : On ne corrige PAS vers le centre
        // On MAINTIENT la ligne là où elle est détectée
        
        // ===== LIGNE AU CENTRE → Reculer droit =====
        if (ValeurSuiveur == 0x08)
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_AVANCE;
        }
        
        // ===== LIGNE À DROITE → MAINTENIR à droite (tourner à droite aussi!) =====
        // Au lieu de corriger à gauche, on SUIT la courbe à droite
        else if (ValeurSuiveur == 0x10)  // Légèrement à droite
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_TOURNEADROITE;  // ← MÊME DIRECTION!
        }
        else if (ValeurSuiveur == 0x18 || ValeurSuiveur == 0x20)  // Moyennement à droite
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_TOURNEADROITE;
        }
        else if (ValeurSuiveur == 0x30 || ValeurSuiveur == 0x40 || ValeurSuiveur == 0x60)  // Très à droite
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_TOURNEADROITE;
        }
        
        // ===== LIGNE À GAUCHE → MAINTENIR à gauche (tourner à gauche aussi!) =====
        else if (ValeurSuiveur == 0x04)  // Légèrement à gauche
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_TOURNEAGAUCHE;  // ← MÊME DIRECTION!
        }
        else if (ValeurSuiveur == 0x06 || ValeurSuiveur == 0x02)  // Moyennement à gauche
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_TOURNEAGAUCHE;
        }
        else if (ValeurSuiveur == 0x01 || ValeurSuiveur == 0x03)  // Très à gauche
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_TOURNEAGAUCHE;
        }
        
        // Ligne pleine
        else if (ValeurSuiveur == 0x7F)
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_ARRET;
        }
        // Ligne perdue
        else if(ValeurSuiveur == 0x00)
        {
            processusSuiveurDeLigne.Direction = PROCESSUSSUIVEURLIGNE_PERDU;
        }
    }


}

}



void processusSuiveurDeLigne_initialise(void) 
{
  
  vEcrireSuiveurPCF();
  serviceBaseDeTemps_execute[PROCESSUSSUIVEURDELIGNEPHASE] = processusSuiveurDeLigne_Suit;
}