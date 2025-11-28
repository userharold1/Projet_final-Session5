//processusReceptionEtat:
//Historique: 
// 2018-09-30, Harold Kouadio, creation

#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocole637.h"
#include "processusReceptionEtat.h"
#include "interfaceT2.h"

//Declarations de fonctions privees:
void processusReceptionEtat_gere(void);

//Definitions de variables privees:


//Definitions de fonctions privees:

void processusReceptionEtat_gere(void)
{
 /* if(serviceProtocole637.information == INFORMATION_DISPONIBLE)
  {
    if (serviceProtocole637.nombreARecevoir >= 3)
    {
        if (serviceProtocole637.octetsRecus[0] == '1' &&
            serviceProtocole637.octetsRecus[1] == '$' &&
            serviceProtocole637.octetsRecus[2] == '1')
        {
            interfaceT2_allume();
        }
        
        if (serviceProtocole637.octetsRecus[0] == '0' &&
            serviceProtocole637.octetsRecus[1] == '0' &&
            serviceProtocole637.octetsRecus[2] == '$')
        {
            interfaceT2_eteint();
        }
        
        serviceProtocole637.information = INFORMATION_TRAITEE;
    }
    
  }*/
  
  serviceProtocole637.requete = REQUETE_ACTIVE;
serviceProtocole637.octetsATransmettre[0] = 'M';
serviceProtocole637.octetsATransmettre[1] = 'e';
serviceProtocole637.octetsATransmettre[2] = 't';
serviceProtocole637.octetsATransmettre[3] = 'a';
serviceProtocole637.octetsATransmettre[4] = 'l';
}




void processusReceptionEtat_initialise(void)
{
  interfaceT2_eteint();
  serviceBaseDeTemps_execute[PROCESSUSRECEPTIONETAT_PHASE] =
      processusReceptionEtat_gere;
}