//InterfaceDriver1
//INCLUSIONS
#include "main.h"
#include "piloteMoteur1.h"
#include "piloteMoteur2.h"

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

void InterfaceDriver1_EN(unsigned char moteur, unsigned char niveau) 
{
    switch(moteur) 
    {
        case MOTEUR1: 
        piloteMoteur1_EN_metA(niveau); 
        break;
        case MOTEUR2: 
        piloteMoteur2_EN_metA(niveau); 
        break;

        default: 
        break;
    }
}

void InterfaceDriver1_IN1(unsigned char moteur, unsigned char niveau) 
{ 
    switch(moteur)
     {
        case MOTEUR1: 
        piloteMoteur1_IN1_metA(niveau); 
        break;
        case MOTEUR2: 
        piloteMoteur2_IN1_metA(niveau); 
        break;

        default: 
        break;
    }
}

void InterfaceDriver1_IN2(unsigned char moteur, unsigned char niveau) 
{ 
    switch(moteur) 
    {
        case MOTEUR1: 
        piloteMoteur1_IN2_metA(niveau); 
        break;
        case MOTEUR2: 
        piloteMoteur2_IN2_metA(niveau); 
        break;

        default: 
        break;
    }
}

void InterfaceDriver1_Initialise(void)
{
  piloteMoteur1_EN_metA(LOW);
  piloteMoteur1_IN1_metA(LOW);
  piloteMoteur1_IN2_metA(LOW);

  piloteMoteur2_EN_metA(LOW);
  piloteMoteur2_IN1_metA(LOW);
  piloteMoteur2_IN2_metA(LOW);

}