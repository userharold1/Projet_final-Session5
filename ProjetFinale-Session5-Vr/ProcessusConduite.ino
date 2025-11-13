#include "main.h"
#include "InterfaceDriver1.h"
#include "InterfaceDriver2.h"

// ===============================
// Fonctions privées
// ===============================
 

// ===============================
// Fonctions publiques
// ===============================


void roues_arret(void) 
{
  // Driver 1
  moteur_IN1_driver1(MOTEUR1, LOW);
  moteur_IN2_driver1(MOTEUR1, LOW);

  moteur_IN1_driver1(MOTEUR2, LOW);
  moteur_IN2_driver1(MOTEUR2, LOW);

  // Driver 2
  moteur_IN1_driver2(MOTEUR3, LOW);
  moteur_IN2_driver2(MOTEUR3, LOW);

  moteur_IN1_driver2(MOTEUR4, LOW);
  moteur_IN2_driver2(MOTEUR4, LOW);
}

// Avancer
void processusRoues_avance(void)
 {
  moteur_IN1_driver1(MOTEUR1, HIGH);
  moteur_IN2_driver1(MOTEUR1, LOW);

  moteur_IN1_driver1(MOTEUR2, HIGH);
  moteur_IN2_driver1(MOTEUR2, LOW);

  moteur_IN1_driver2(MOTEUR3, HIGH);
  moteur_IN2_driver2(MOTEUR3, LOW);

  moteur_IN1_driver2(MOTEUR4, HIGH);
  moteur_IN2_driver2(MOTEUR4, LOW);
}


void processusRoues_initialise(void) 
{
  serviceBaseDeTemps_executeDansLoop[PROCESSUSTACHELENTEDANSLOOP_PHASE] = processusRoues_avance;
}
