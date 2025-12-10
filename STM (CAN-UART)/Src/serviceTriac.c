/* serviceTriac.c */
#include "serviceTriac.h"
#include "piloteIOT2.h"

// Variables privées
// Variables privées
unsigned char serviceTriac_actif = 0;
unsigned char serviceTriac_niveau = 0;

// délai exprimé en TICKS de 100 µs
static unsigned int serviceTriac_delaiTicks = SERVICETRIAC_MAX_TICKS;

// gestion par demi-période
static volatile unsigned char attenteDeclenchement = 0;
static volatile unsigned int  compteurTicks = 0;

extern TIM_HandleTypeDef htim7;

/**
 * @brief  Initialisation du service triac
 */
void serviceTriac_initialise(void)
{
    serviceTriac_actif = 0;
    serviceTriac_niveau = 0;
    serviceTriac_delaiTicks = SERVICETRIAC_MAX_TICKS;
    compteurTicks = 0;
    attenteDeclenchement = 0;
    piloteIOT2_metLaSortieA(1);
}

/**
 * @brief  Active le contrôle du triac
 */
void serviceTriac_active(void)
{
    serviceTriac_actif = 1;
}

/**
 * @brief  Désactive le contrôle du triac
 */
void serviceTriac_desactive(void)
{
    serviceTriac_actif = 0;
    piloteIOT2_metLaSortieA(1);
    HAL_TIM_Base_Stop_IT(&htim7);
}

/**
 * @brief  Retourne l'état du triac
 * @retval 1 si actif, 0 si inactif
 */
unsigned char serviceTriac_estActif(void)
{
    return serviceTriac_actif;
}

/**
 * @brief  Fixe le niveau de puissance du triac
 * @param  niveau_pourcent : Niveau en % (0-100)
 */
void serviceTriac_fixeNiveau(unsigned char niveau_pourcent)
{
    if (niveau_pourcent > 100)
    {
        niveau_pourcent = 100;
    }

    serviceTriac_niveau = niveau_pourcent;

    // 0%  -> délai MAX (triac déclenché très tard  ? faible lumière)
    // 100%-> délai MIN (triac déclenché très tôt  ? forte lumière)

    unsigned int delta = (SERVICETRIAC_MAX_TICKS - SERVICETRIAC_MIN_TICKS);

    serviceTriac_delaiTicks =
        SERVICETRIAC_MAX_TICKS - ( (unsigned int)niveau_pourcent * delta / 100 );

    // sécurité
    if (serviceTriac_delaiTicks < SERVICETRIAC_MIN_TICKS)
        serviceTriac_delaiTicks = SERVICETRIAC_MIN_TICKS;

    if (serviceTriac_delaiTicks > SERVICETRIAC_MAX_TICKS)
        serviceTriac_delaiTicks = SERVICETRIAC_MAX_TICKS;
}

/**
 * @brief  Retourne le niveau actuel
 * @retval Niveau en % (0-100)
 */
unsigned char serviceTriac_obtenirNiveau(void)
{
    return serviceTriac_niveau;
}

/**
 * @brief  Interruption TIM7 - Déclenche le triac après le délai
 */
void serviceTriac_ITTimer7(void)
{
  if (!serviceTriac_actif)
    {
        return;
    }

    if (!attenteDeclenchement)
    {
        // Rien à faire sur cette demi-période
        return;
    }

    // On avance le délai : +1 tick = +100 µs
    if (compteurTicks < serviceTriac_delaiTicks)
    {
        compteurTicks++;
    }

    if (compteurTicks >= serviceTriac_delaiTicks)
    {
        // On a atteint le délai ? pulse gate sur le triac
        attenteDeclenchement = 0;   // ne pas relancer dans la même demi-période

        piloteIOT2_metLaSortieA(0);

        // Petite impulsion (~quelques µs ; garde ça court pour ne pas bloquer l'IT trop longtemps)
        for (volatile unsigned int i = 0; i < 2000; i++)
        {
            __NOP();  // ou rien, juste une boucle
        }

        piloteIOT2_metLaSortieA(1);
    }
}

/**
 * @brief  Interruption Zero Crossing - Détecte le passage par zéro
 */
void serviceTriac_ITZeroCross(void)
{
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); // LED verte ON
   if (!serviceTriac_actif)
    {
        return;
    }

    // Nouvelle demi-période : on repart de zéro
    compteurTicks = 0;
    attenteDeclenchement = 1;
    
}