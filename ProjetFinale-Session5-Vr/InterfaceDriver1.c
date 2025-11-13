//InterfaceDriver1
//INCLUSIONS
#include "main.h"
#include "piloteMoteur1.h"
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

void moteur_EN_driver1(unsigned char moteur, unsigned char niveau) 
{
    switch(moteur) 
    {
        case MOTEUR1: 
        piloteMoteur1_EN_metA(niveau); 
        break;
        case MOTEUR2: 
        piloteMoteur2_EN_metA(niveau); 
        break;
    }
}

void moteur_IN1_driver1(unsigned char moteur, unsigned char niveau) 
{ 
    switch(moteur)
     {
        case MOTEUR1: 
        piloteMoteur1_IN1_metA(niveau); 
        break;
        case MOTEUR2: 
        piloteMoteur2_IN1_metA(niveau); 
        break;
    }
}

void moteur_IN2_driver1(unsigned char moteur, unsigned char niveau) 
{ 
    switch(moteur) 
    {
        case MOTEUR1: 
        piloteMoteur1_IN2_metA(niveau); 
        break;
        case MOTEUR2: 
        piloteMoteur2_IN2_metA(niveau); 
        break;
    }
}

void Moteur_Driver1_Initialise(void)
{
  piloteMoteur1_EN_metA(LOW);
  piloteMoteur1_IN1_metA(LOW);
  piloteMoteur1_IN2_metA(LOW);

  piloteMoteur2_EN_metA(LOW);
  piloteMoteur2_IN1_metA(LOW);
  piloteMoteur2_IN2_metA(LOW);

}