//piloteCAN1:
//Historique: 
// 2018-11-12, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteCAN1.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//Declarations de fonctions privees:
static unsigned int piloteCAN1_idEstAccepte(unsigned int id);


//Declarations de variables privees:
extern CAN_HandleTypeDef hcan1; //défini par le hal dans main

//Definitions de variables privees:
CAN_RxHeaderTypeDef piloteCAN1_reception;
CAN_TxHeaderTypeDef piloteCAN1_transmission;
CAN_FilterTypeDef piloteCAN1_filtre;
unsigned int piloteCAN1_CasierPostal;

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
// pas de definitions publiques

//Fonctions publiques:

//Definitions de fonctions privees:
static unsigned int piloteCAN1_idEstAccepte(unsigned int id)
{
  // Multi-ID : on teste d'abord les nouveaux defines, s'ils existent
  #ifdef PILOTECAN1_IDENTIFICATION_EN_RECEPTION_0
  if (id == PILOTECAN1_IDENTIFICATION_EN_RECEPTION_0)
  {
    return 1;
  }
  #endif

  #ifdef PILOTECAN1_IDENTIFICATION_EN_RECEPTION_1
  if (id == PILOTECAN1_IDENTIFICATION_EN_RECEPTION_1)
  {
    return 1;
  }
  #endif

  #ifdef PILOTECAN1_IDENTIFICATION_EN_RECEPTION_2
  if (id == PILOTECAN1_IDENTIFICATION_EN_RECEPTION_2)
  {
    return 1;
  }
  #endif

  #ifdef PILOTECAN1_IDENTIFICATION_EN_RECEPTION_3
  if (id == PILOTECAN1_IDENTIFICATION_EN_RECEPTION_3)
  {
    return 1;
  }
  #endif

  // Compatibilité avec l’ancienne version : 1 seul ID
  #ifdef PILOTECAN1_IDENTIFICATION_EN_RECEPTION
  if (id == PILOTECAN1_IDENTIFICATION_EN_RECEPTION)
  {
    return 1;
  }
  #endif

  // Si on arrive ici ? ID non accepté
  return 0;
}


unsigned int piloteCAN1_messageDisponible(void)
{
  return HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_FILTER_FIFO0);  
}

unsigned int piloteCAN1_messageTransmis(void)
{
  return HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
}

unsigned char piloteCAN1_litUnMessageRecu(unsigned char *DonneesRecues)
{
  // Tant qu'il reste des messages dans le FIFO CAN
  while (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_FILTER_FIFO0) > 0)
  {
    // On lit un message
    if (HAL_CAN_GetRxMessage(&hcan1, CAN_FILTER_FIFO0,
                             &piloteCAN1_reception, DonneesRecues) != HAL_OK)
    {
      // Erreur de lecture ? on considère qu'il n'y a rien d'utilisable
      return PILOTECAN1_PAS_DISPONIBLE;
    }

    // On regarde si l'ID de cette trame nous intéresse
    if (piloteCAN1_idEstAccepte(piloteCAN1_reception.StdId))
    {
      // OUI ? on retourne les données au dessus (service/proc)
      return PILOTECAN1_DISPONIBLE;
    }

    // NON ? on ignore cette trame et on continue la boucle
    // (on a déjà "jeté" le message du FIFO en l'ayant lu)
  }

  // Si on a vidé le FIFO et qu'on n'a rien trouvé pour nous
  return PILOTECAN1_PAS_DISPONIBLE;
}


unsigned int piloteCAN1_transmetDesDonnes(unsigned int Identification11Bits,
                                          unsigned char *Donnees,
                                          unsigned char Nombre)
{
  piloteCAN1_transmission.StdId = Identification11Bits; // << 5;
  piloteCAN1_transmission.DLC = Nombre;
  if (HAL_CAN_AddTxMessage(&hcan1, &piloteCAN1_transmission,
                           Donnees, &piloteCAN1_CasierPostal) != HAL_OK)
  {
    return PILOTECAN1_PAS_TRANSMIS;
  }
  return PILOTECAN1_TRANSMIS;
}

unsigned int piloteCAN1_initialise(void)
{
  piloteCAN1_transmission.ExtId = 0;
  piloteCAN1_transmission.IDE = CAN_ID_STD;
  piloteCAN1_transmission.RTR = CAN_RTR_DATA;
  piloteCAN1_transmission.TransmitGlobalTime = DISABLE;
  
  piloteCAN1_filtre.FilterIdHigh = PILOTECAN1_IDENTIFICATION_EN_RECEPTION ;// << 5;
  piloteCAN1_filtre.FilterIdLow = 0x0;
  piloteCAN1_filtre.FilterMaskIdHigh = PILOTECAN1_MASQUE_11_BITS_EN_RECEPTION ;//<< 21;
  piloteCAN1_filtre.FilterMaskIdLow = 0x0;
  piloteCAN1_filtre.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  piloteCAN1_filtre.FilterBank = 13;
  piloteCAN1_filtre.FilterMode = CAN_FILTERMODE_IDMASK;
  piloteCAN1_filtre.FilterScale = CAN_FILTERSCALE_32BIT;
  piloteCAN1_filtre.FilterActivation = ENABLE;
  if (HAL_CAN_ConfigFilter(&hcan1, &piloteCAN1_filtre) != HAL_OK)
  {
    return PILOTECAN1_ERREUR;
  }
//#define TEST
//#ifdef TEST
//  piloteCAN1_filtre.FilterIdHigh = (PILOTECAN1_IDENTIFICATION_EN_RECEPTION+1) << 5;
//  piloteCAN1_filtre.FilterMaskIdHigh = (PILOTECAN1_MASQUE_11_BITS_EN_RECEPTION+1) << 21;  
//  piloteCAN1_filtre.FilterBank = 13;
  
//  if (HAL_CAN_ConfigFilter(&hcan1, & piloteCAN1_filtre) != HAL_OK)
//  {
//    return PILOTECAN1_ERREUR;
//  }
//#endif
  
  
  if (HAL_CAN_Start(&hcan1) != HAL_OK)
  {
    return PILOTECAN1_ERREUR;
  }
  return PILOTECAN1_PAS_D_ERREUR;
}
