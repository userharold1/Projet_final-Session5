//InterfaceDriver2
//INCLUSIONS
#include "main.h"
#include "piloteMoteur3.h"
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

void InterfaceDriver2_EN(unsigned char moteur, unsigned char niveau) 
{
    switch(moteur) 
    {
        case Moteur3: 
        piloteMoteur3_EN_metA(niveau); 
        break;
        case Moteur4: 
        piloteMoteur4_EN_metA(niveau); 
        break;

        default: break;
    }
}

void InterfaceDriver2_IN1(unsigned char moteur, unsigned char niveau) 
{ 
    switch(moteur)
     {
        case Moteur3: 
        piloteMoteur3_IN1_metA(niveau); 
        break;
        case Moteur4: 
        piloteMoteur4_IN1_metA(niveau); 
        break;

        default: break;
    }
}

void InterfaceDriver2_IN2(unsigned char moteur, unsigned char niveau) 
{ 
    switch(moteur) 
    {
        case Moteur3: 
        piloteMoteur3_IN2_metA(niveau); 
        break;
        case Moteur4: 
        piloteMoteur4_IN2_metA(niveau); 
        break;

        default: break;
    }
}

void Interfaceriver2_Initialise(void)
{
  piloteMoteur3_EN_metA(LOW);
  piloteMoteur3_IN1_metA(LOW);
  piloteMoteur3_IN2_metA(LOW);

  piloteMoteur4_EN_metA(LOW);
  piloteMoteur4_IN1_metA(LOW);
  piloteMoteur4_IN2_metA(LOW);

}