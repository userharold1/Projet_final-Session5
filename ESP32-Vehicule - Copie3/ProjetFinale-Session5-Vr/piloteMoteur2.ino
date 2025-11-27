//piloteMoteur1:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteMoteur2.h"

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

void piloteMoteur2_EN_metA(unsigned char Niveau)
{
  digitalWrite(piloteMoteur2_EN_BROCHE, Niveau);
}

void piloteMoteur2_IN1_metA(unsigned char Niveau)
{
  digitalWrite(piloteMoteur2_IN1_BROCHE, Niveau);
}

void piloteMoteur2_IN2_metA(unsigned char Niveau)
{
  digitalWrite(piloteMoteur2_IN2_BROCHE, Niveau);
}


void piloteMoteur2_PWM_metA(unsigned char PWM)
{
  ledcWrite(piloteMoteur2_EN_BROCHE, PWM);
}

void piloteMoteur2_initialise(void)
{
  
  pinMode(piloteMoteur2_EN_BROCHE,OUTPUT);
  pinMode(piloteMoteur2_IN2_BROCHE,OUTPUT);
  pinMode(piloteMoteur2_IN1_BROCHE,OUTPUT);

  ledcAttach(piloteMoteur2_EN_BROCHE,2000,8);


#ifdef piloteMoteur2_ETAT_INITIAL_A_ZERO
ledcWrite(piloteMoteur2_EN_BROCHE, 0); // Sortie PWM (LED), duty cycle Ã  0	
#endif
}
