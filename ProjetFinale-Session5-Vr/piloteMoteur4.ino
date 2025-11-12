//piloteMoteur1:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteMoteur4.h"

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

void piloteMoteur4_EN_metA(unsigned char Niveau)
{
  ledcWrite(piloteMoteur4_EN_BROCHE, Niveau);
}

void piloteMoteur4_IN1_metA(unsigned char Niveau)
{
  ledcWrite(piloteMoteur4_IN1_BROCHE, Niveau);
}

void piloteMoteur4_IN2_metA(unsigned char Niveau)
{
  ledcWrite(piloteMoteur4_IN2_BROCHE, Niveau);
}



void piloteMoteur4_initialise(void)
{
  
  pinMode(piloteMoteur4_EN_BROCHE,OUTPUT);
  ledcAttach(piloteMoteur4_EN_BROCHE,2000,8);

#ifdef piloteMoteur4_ETAT_INITIAL_A_UN
ledcWrite(piloteMoteur4_EN_BROCHE, 1); // Sortie PWM (LED), duty cycle Ã  0	
#endif

#ifdef piloteMoteur4_ETAT_INITIAL_A_ZERO
ledcWrite(piloteMoteur4_EN_BROCHE, 0); // Sortie PWM (LED), duty cycle Ã  0	
#endif
}
