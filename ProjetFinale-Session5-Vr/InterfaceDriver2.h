#ifndef INTERFACEDRIVER2_H
#define INTERFACEDRIVER2_H

// Description: déclarations des fonctions de la drive Moteur 2. 


//Declarations de fonctions
//void InterfaceDriver2_EN(unsigned char moteur, unsigned char niveau);
void InterfaceDriver2_IN1(unsigned char moteur, unsigned char niveau);
void InterfaceDriver2_IN2(unsigned char moteur, unsigned char niveau);
void InterfaceDriver2_Vitesse(unsigned char moteur, unsigned char vitesse);
void InterfaceDriver2_Initialise(void);



#endif 