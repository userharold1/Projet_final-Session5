//piloteUART:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteUART.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
HardwareSerial UARTport(2); // UART2

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteUART_octetDisponible(void)
{
  return (UARTport.available() > 0);
}

unsigned char piloteUART_octetTransmis(void)
{
  return 1; 
}

unsigned char piloteUART_litUnOctetRecu(void)
{
   return (unsigned char)UARTport.read();
}

void piloteUART_transmet(unsigned char Octet)
{
 UARTport.write(Octet);
 UARTport.flush();   
}


void piloteUART_initialise(void)

{                    
  UARTport.begin(115200, SERIAL_8N1, PILOTEUART_RX_PIN, PILOTEUART_TX_PIN);
}
