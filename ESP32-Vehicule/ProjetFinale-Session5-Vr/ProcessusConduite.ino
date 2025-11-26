#include "main.h"
#include "InterfaceDriver1.h"
#include "InterfaceDriver2.h"

// ===============================
// Fonctions privées
// ===============================

// ===============================
// Fonctions publiques
// ===============================


void processusConduite_arret(void) 
{
  // Driver 1
  InterfaceDriver1_IN1(MOTEUR1, HIGH);  // ← HIGH au lieu de LOW
  InterfaceDriver1_IN2(MOTEUR1, HIGH);  // ← HIGH au lieu de LOW

  InterfaceDriver1_IN1(MOTEUR2, HIGH);
  InterfaceDriver1_IN2(MOTEUR2, HIGH);

  // Driver 2
  InterfaceDriver2_IN1(MOTEUR3, HIGH);
  InterfaceDriver2_IN2(MOTEUR3, HIGH);

  InterfaceDriver2_IN1(MOTEUR4, HIGH);
  InterfaceDriver2_IN2(MOTEUR4, HIGH);

  // Vitesse à fond pour maximiser le freinage
  InterfaceDriver1_Vitesse(MOTEUR1, 255);  // Maximum
  InterfaceDriver1_Vitesse(MOTEUR2, 255);

  InterfaceDriver2_Vitesse(MOTEUR3, 255);
  InterfaceDriver2_Vitesse(MOTEUR4, 255);
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

void processusConduite_tourneADroite_vitesseFaible(void)
{
  InterfaceDriver1_IN1(MOTEUR1, HIGH);
  InterfaceDriver1_IN2(MOTEUR1, LOW);

  InterfaceDriver1_IN1(MOTEUR2, LOW);
  InterfaceDriver1_IN2(MOTEUR2, HIGH);

  InterfaceDriver2_IN1(MOTEUR3, HIGH);
  InterfaceDriver2_IN2(MOTEUR3, LOW);

  InterfaceDriver2_IN1(MOTEUR4, LOW);
  InterfaceDriver2_IN2(MOTEUR4, HIGH);

  // vitesse réduite
  InterfaceDriver1_Vitesse(MOTEUR1, 180);
  InterfaceDriver1_Vitesse(MOTEUR2, 180);

  InterfaceDriver2_Vitesse(MOTEUR3, 180);
  InterfaceDriver2_Vitesse(MOTEUR4, 180);
}

void processusConduite_tourneAGauche_vitesseFaible(void)
{
  InterfaceDriver1_IN1(MOTEUR1, LOW);
  InterfaceDriver1_IN2(MOTEUR1, HIGH);

  InterfaceDriver1_IN1(MOTEUR2, HIGH);
  InterfaceDriver1_IN2(MOTEUR2, LOW);

  InterfaceDriver2_IN1(MOTEUR3, LOW);
  InterfaceDriver2_IN2(MOTEUR3, HIGH);

  InterfaceDriver2_IN1(MOTEUR4, HIGH);
  InterfaceDriver2_IN2(MOTEUR4, LOW);

  InterfaceDriver1_Vitesse(MOTEUR1, 180);
  InterfaceDriver1_Vitesse(MOTEUR2, 180);

  InterfaceDriver2_Vitesse(MOTEUR3, 180);
  InterfaceDriver2_Vitesse(MOTEUR4, 180);
}

void processusConduite_recul_lent(void)
{
  // Moteur 1 et 2 (avant)
  InterfaceDriver1_IN1(MOTEUR1, LOW);
  InterfaceDriver1_IN2(MOTEUR1, HIGH);

  InterfaceDriver1_IN1(MOTEUR2, LOW);
  InterfaceDriver1_IN2(MOTEUR2, HIGH);

  // Moteur 3 et 4 (arrière)
  InterfaceDriver2_IN1(MOTEUR3, LOW);
  InterfaceDriver2_IN2(MOTEUR3, HIGH);

  InterfaceDriver2_IN1(MOTEUR4, LOW);
  InterfaceDriver2_IN2(MOTEUR4, HIGH);

  // vitesse réduite
  InterfaceDriver1_Vitesse(MOTEUR1, 150);
  InterfaceDriver1_Vitesse(MOTEUR2, 150);
  InterfaceDriver2_Vitesse(MOTEUR3, 150);
  InterfaceDriver2_Vitesse(MOTEUR4, 150);
}


       
void processusConduite_initialise(void) 
{
  serviceBaseDeTemps_execute[PROCESSUSCONDUITEPHASE] = processusConduite_arret;
}
