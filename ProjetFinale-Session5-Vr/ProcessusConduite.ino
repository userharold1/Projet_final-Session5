#include "main.h"
#include "InterfaceDriver1.h"
#include "InterfaceDriver2.h"

// ===============================
// Fonctions privées
// ===============================
/*void processusRoues_avance(void);
void processusRoues_recul(void);
void roues_arret(void) ;*/
// ===============================
// Fonctions publiques
// ===============================


void processusConduite_arret(void) 
{
  // Driver 1
  InterfaceDriver1_IN1(MOTEUR1, LOW);
  InterfaceDriver1_IN2(MOTEUR1, LOW);

  InterfaceDriver1_IN1(MOTEUR2, LOW);
  InterfaceDriver1_IN2(MOTEUR2, LOW);

  // Driver 2
  InterfaceDriver2_IN1(MOTEUR3, LOW);
  InterfaceDriver2_IN2(MOTEUR3, LOW);

  InterfaceDriver2_IN1(MOTEUR4, LOW);
  InterfaceDriver2_IN2(MOTEUR4, LOW);

  InterfaceDriver1_Vitesse(MOTEUR1, 0);
  InterfaceDriver1_Vitesse(MOTEUR2, 0);

  InterfaceDriver2_Vitesse(MOTEUR3, 0);
  InterfaceDriver2_Vitesse(MOTEUR4, 0);
}

// Avancer
void processusConduite_avance(void)
 {
  InterfaceDriver1_IN1(MOTEUR1, HIGH);
  InterfaceDriver1_IN2(MOTEUR1, LOW);

  InterfaceDriver1_IN1(MOTEUR2, HIGH);
  InterfaceDriver1_IN2(MOTEUR2, LOW);

  InterfaceDriver2_IN1(MOTEUR3, HIGH);
  InterfaceDriver2_IN2(MOTEUR3, LOW);

  InterfaceDriver2_IN1(MOTEUR4, HIGH);
  InterfaceDriver2_IN2(MOTEUR4, LOW);

  InterfaceDriver1_Vitesse(MOTEUR1, 200);
  InterfaceDriver1_Vitesse(MOTEUR2, 200);

  InterfaceDriver2_Vitesse(MOTEUR3, 200);
  InterfaceDriver2_Vitesse(MOTEUR4, 200);
}

void processusConduite_recul(void)
{
  // Moteurs sur InterfaceDriver1 (MOTEUR1 et MOTEUR2)
  InterfaceDriver1_IN1(MOTEUR1, LOW);
  InterfaceDriver1_IN2(MOTEUR1, HIGH);

  InterfaceDriver1_IN1(MOTEUR2, LOW);
  InterfaceDriver1_IN2(MOTEUR2, HIGH);

  // Moteurs sur InterfaceDriver2 (MOTEUR3 et MOTEUR4)
  InterfaceDriver2_IN1(MOTEUR3, LOW);
  InterfaceDriver2_IN2(MOTEUR3, HIGH);

  InterfaceDriver2_IN1(MOTEUR4, LOW);
  InterfaceDriver2_IN2(MOTEUR4, HIGH);

  // Vitesse 
  InterfaceDriver1_Vitesse(MOTEUR1, 205);
  InterfaceDriver1_Vitesse(MOTEUR2, 205);

  InterfaceDriver2_Vitesse(MOTEUR3, 205);
  InterfaceDriver2_Vitesse(MOTEUR4, 205);
}


void processusConduite_tourneAGauche(void)
{

  InterfaceDriver1_IN1(MOTEUR1, LOW);
  InterfaceDriver1_IN2(MOTEUR1, HIGH);

  InterfaceDriver1_IN1(MOTEUR2, HIGH);
  InterfaceDriver1_IN2(MOTEUR2, LOW);

  InterfaceDriver2_IN1(MOTEUR3, LOW);
  InterfaceDriver2_IN2(MOTEUR3, HIGH);

  InterfaceDriver2_IN1(MOTEUR4, HIGH);
  InterfaceDriver2_IN2(MOTEUR4, LOW);

  // Côté gauche très lent
  InterfaceDriver1_Vitesse(MOTEUR1, 205);
  InterfaceDriver2_Vitesse(MOTEUR3, 205);

  // Côté droit normal
  InterfaceDriver1_Vitesse(MOTEUR2, 205);
  InterfaceDriver2_Vitesse(MOTEUR4, 205);
}


void processusConduite_tourneADroite(void)
{
  // Tous avancent
  InterfaceDriver1_IN1(MOTEUR1, HIGH);
  InterfaceDriver1_IN2(MOTEUR1, LOW);

  InterfaceDriver1_IN1(MOTEUR2, LOW);
  InterfaceDriver1_IN2(MOTEUR2, HIGH);

  InterfaceDriver2_IN1(MOTEUR3, HIGH);
  InterfaceDriver2_IN2(MOTEUR3, LOW);

  InterfaceDriver2_IN1(MOTEUR4, LOW);
  InterfaceDriver2_IN2(MOTEUR4, HIGH);

  // Côté droit très lent
  InterfaceDriver1_Vitesse(MOTEUR2, 205);
  InterfaceDriver2_Vitesse(MOTEUR4, 205);

  // Côté gauche normal
  InterfaceDriver1_Vitesse(MOTEUR1, 205);
  InterfaceDriver2_Vitesse(MOTEUR3, 205);
}





void processusConduite_initialise(void) 
{
  serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
}
