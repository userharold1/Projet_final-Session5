//piloteI2C1:
//Historique: 
// 2021-04-19, Yves Roy, creation

//INCLUSIONS
#include <Wire.h>
#include "main.h"
#include "piloteI2C1.h"

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
unsigned char piloteI2C1_lisUnOctet(unsigned char Adresse)
{
  Wire.requestFrom((uint8_t)Adresse, (uint8_t)1);
  return (unsigned char)(Wire.read()); 
}

void piloteI2C1_ecrisUnOctet(unsigned char Adresse, unsigned char Octet)
{
  Wire.beginTransmission((uint8_t)Adresse);
  Wire.write((uint8_t)Octet);
  Wire.endTransmission();
}

unsigned int piloteI2C1_lisUnEntier(unsigned char Adresse)
{
  Wire.requestFrom((uint8_t)Adresse, (uint8_t)2);
  return (unsigned int)(Wire.read() | (((unsigned int)Wire.read()) << 8));   
}

void piloteI2C1_ecrisUnEntier(unsigned char Adresse, unsigned int Entier)
{
  Wire.beginTransmission((uint8_t)Adresse);
  Wire.write((unsigned char)(Entier >> 8));
  Wire.write((unsigned char)(Entier & 0xFF));
  Wire.endTransmission();  
}

void piloteI2C1_initialise(void)
{
  Wire.begin(23,22);  
}
