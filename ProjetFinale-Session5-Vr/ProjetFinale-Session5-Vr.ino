//247-616: programme pour ESP32 qui comprend des pilotes et un service de base de temps
//Historique:
// 2021-10-31, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteEntree1.h"

#include "piloteMoteur1.h"
#include "piloteMoteur2.h"
#include "piloteMoteur3.h"
#include "piloteMoteur4.h"
#include "InterfaceDriver1"
#include "InterfaceDriver2"

#include "piloteAnalogue1.h"
#include "piloteI2C1.h"
#include "serviceTaskServer.h"
#include "serviceBaseDeTemps.h"
#include "interfaceEntree1.h"
#include "processusTacheLenteDansLoop.h"
#include "processusDemonstration.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void main_initialise(void);
void setup(void);
void loop(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void main_initialise(void)
{
  piloteEntree1_initialise();

  piloteMoteur1_initialise();
  piloteMoteur2_initialise();
  piloteMoteur3_initialise();
  piloteMoteur4_initialise();
  InterfaceDriver1_Initialise();
  InterfaceDriver2_Initialise();

  piloteAnalogue1_initialise();
  piloteI2C1_initialise();
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  interfaceEntree1_initialise();
  processusDemonstration_initialise();
  processusTacheLenteDansLoop_initialise();
  processusTacheLenteDansLoop_initialise();
}

void setup(void) 
{
  Serial.begin(115200);//pour le "debug"
  main_initialise();
  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();
}

void loop(void) 
{
  serviceTaskServer_gestion.execute();
  serviceBaseDeTemps_gereDansLoop();
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
//pas de fonctions publiques
