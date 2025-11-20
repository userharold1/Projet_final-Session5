//InterfaceDriver2
//INCLUSIONS
#include "main.h"
#include "piloteMoteur3.h"
#include "piloteMoteur4.h"
#include "InterfaceDriver2.h"

//Definitions privees
#define MOTEUR1 1
#define MOTEUR2 2
#define MOTEUR3 3
#define MOTEUR4 4

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:



void InterfaceDriver2_IN1(unsigned char moteur, unsigned char niveau) 
{ 
    switch(moteur)
     {
        case MOTEUR3: 
        piloteMoteur3_IN1_metA(niveau); 
        break;
        case MOTEUR4: 
        piloteMoteur4_IN1_metA(niveau); 
        break;

        default: break;
    }
}

void InterfaceDriver2_IN2(unsigned char moteur, unsigned char niveau) 
{ 
    switch(moteur) 
    {
        case MOTEUR3: 
        piloteMoteur3_IN2_metA(niveau); 
        break;
        case MOTEUR4: 
        piloteMoteur4_IN2_metA(niveau); 
        break;

        default: break;
    }
}

void InterfaceDriver2_Vitesse(unsigned char moteur, unsigned char vitesse)
{
    switch(moteur) 
    {
        case MOTEUR3: 
        piloteMoteur3_PWM_metA(vitesse); 
        break;
        case MOTEUR4: 
        piloteMoteur4_PWM_metA(vitesse); 
        break;

        default: break;
    }
}

void InterfaceDriver2_Initialise(void)
{
 // piloteMoteur3_EN_metA(LOW);
  piloteMoteur3_IN1_metA(LOW);
  piloteMoteur3_IN2_metA(LOW);

 // piloteMoteur4_EN_metA(LOW);
  piloteMoteur4_IN1_metA(LOW);
  piloteMoteur4_IN2_metA(LOW);

  piloteMoteur3_PWM_metA(LOW);
  piloteMoteur4_PWM_metA(LOW);

}