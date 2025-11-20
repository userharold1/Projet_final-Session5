//piloteMoteur1:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteMoteur1.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:

void piloteMoteur1_EN_metA(unsigned char Niveau)
{
  digitalWrite(piloteMoteur1_EN_BROCHE, Niveau);
}

void piloteMoteur1_IN1_metA(unsigned char Niveau)
{
  digitalWrite(piloteMoteur1_IN1_BROCHE, Niveau);
}

void piloteMoteur1_IN2_metA(unsigned char Niveau)
{
  digitalWrite(piloteMoteur1_IN2_BROCHE, Niveau);
}

void piloteMoteur1_PWM_metA(unsigned char PWM)
{
  ledcWrite(piloteMoteur1_EN_BROCHE, PWM);
}

void piloteMoteur1_initialise(void)
{
  
  pinMode(piloteMoteur1_EN_BROCHE,OUTPUT);
  pinMode(piloteMoteur1_IN2_BROCHE,OUTPUT);
  pinMode(piloteMoteur1_IN1_BROCHE,OUTPUT);

  ledcAttach(piloteMoteur1_EN_BROCHE,2000,8);

#ifdef piloteMoteur1_ETAT_INITIAL_A_ZERO
ledcWrite(piloteMoteur1_EN_BROCHE, 0); // Sortie PWM (LED), duty cycle Ã  0	
#endif
}
