#include "arduino_secrets.h"

/**************************************************************************************************

Nom du fichier : PCF8574.c
Auteur : Harold Kouadio                 
Date de crÃ©ation : 2025-05-13
Version 1.0
	 
Fichier qui contient les fonctions pour communiquer avec le PCF8574


	
***************************************************************************************************/

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	
#include <stdio.h>          // Prototype de declarations des fonctions I/O
#include "piloteI2C1.h"

// *************************************************************************************************
//  FONCTIONS
// *************************************************************************************************

//***************************************************************************************************
unsigned int vLireSuiveurPCF(unsigned char ucVal)
// Auteur: Harold Kouadio
// Date: 2025-05-13
// Version: 1.0
//
// Description          : Fonction de lecture sur le PCF
// ParamÃ¨tres d'entrÃ©es : l'adresse ucVal1 
// ParamÃ¨tres de sortie : Aucune            
//
//**************************************************************************************************
{  
 return piloteI2C1_lisUnEntier(ucVal); 
}


//***************************************************************************************************
void vEcrireSuiveurPCF(void)
// Auteur: Harold Kouadio
// Date: 2025-05-13
// Version: 1.0
//
// Description          : Fonction d'Ã©cirute sur le PCF pour activer le capteur
// ParamÃ¨tres d'entrÃ©es : Aucun
// ParamÃ¨tres de sortie : Aucun
//
//**************************************************************************************************
{  
  piloteI2C1_ecrisUnEntier(0x44 , 0x7F);
}