//247-616: programme pour ESP32 qui comprend des pilotes et un service de base de temps
//Historique:
// 2021-10-31, Yves Roy, creation

//INCLUSIONS
#include "main.h"

#include "piloteWiFiUDP.h"
#include "piloteMoteur1.h"
#include "piloteMoteur2.h"
#include "piloteMoteur3.h"
#include "piloteMoteur4.h"
#include "InterfaceDriver1.h"
#include "InterfaceDriver2.h"


#include "piloteI2C1.h"
#include "serviceTaskServer.h"
#include "serviceBaseDeTemps.h"

#include "InterfaceDetecteurDeLigne.h"

#include "ProcessusSuiveurDeLigne.h"
#include "ProcessusConduite.h"
#include "processusVehicule.h"
#include "serviceWiFiUDP.h"
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
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  piloteWiFiUDP_initialise();

  serviceWiFiUDP_initialise();
  processusVehicule_initialise();
  piloteMoteur1_initialise();
  piloteMoteur2_initialise();
  piloteMoteur3_initialise();
  piloteMoteur4_initialise();
  InterfaceDriver1_Initialise();
  InterfaceDriver2_Initialise();
  processusConduite_initialise();

  piloteI2C1_initialise();
  
 
  processusSuiveurDeLigne_initialise();
  processusVehicule_initialise();
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
