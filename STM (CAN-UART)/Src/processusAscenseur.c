/* processusTriac.c */
#include "main.h"
#include "processusAscenseur.h"
#include "serviceTriac.h"
#include "serviceBaseDeTemps.h"

// Variables privées
static unsigned char processusTriac_niveau = 0;
static unsigned char processusTriac_montee = 1;  // 1 = montée, 0 = descente
static unsigned char processusTriac_actif = 0;

/**
 * @brief  Initialisation du processus triac
 */
void processusTriac_initialise(void)
{
    processusTriac_niveau = 0;
    processusTriac_montee = 1;
    processusTriac_actif = 0;
    
    serviceTriac_fixeNiveau(0);
    processusTriac_demarre();
    serviceBaseDeTemps_execute[PROCESSUSASCENSEUR_PHASE] = processusTriac_gere;
}

/**
 * @brief  Démarre le processus
 */
void processusTriac_demarre(void)
{
    processusTriac_actif = 1;
    serviceTriac_active();
}

/**
 * @brief  Arrête le processus
 */
void processusTriac_arrete(void)
{
    processusTriac_actif = 0;
    serviceTriac_desactive();
}

/**
 * @brief  Retourne le niveau actuel
 * @retval Niveau en % (0-100)
 */
unsigned char processusTriac_obtenirNiveau(void)
{
    return processusTriac_niveau;
}

/**
 * @brief  Gestion du processus - Appelé périodiquement par serviceBaseDeTemps
 *         Incrémente/décrémente progressivement le niveau (montée/descente)
 */
void processusTriac_gere(void)
{
    static unsigned int compteurMs = 0;
    
    if (!processusTriac_actif)
    {
        return;
    }
    
    // Timer6Up à 2000Hz = appelé toutes les 0.5ms
    // Compteur pour atteindre le délai souhaité
    if (++compteurMs < (PROCESSUSTRIAC_DELAI_MS_PAR_ETAPE * 2))
    {
        return;
    }
    compteurMs = 0;
    
    // Montée ou descente
    if (processusTriac_montee)
    {
        // Phase de montée
        if (processusTriac_niveau < PROCESSUSTRIAC_NIVEAU_MAX)
        {
            processusTriac_niveau += PROCESSUSTRIAC_INCREMENT;
            if (processusTriac_niveau > PROCESSUSTRIAC_NIVEAU_MAX)
            {
                processusTriac_niveau = PROCESSUSTRIAC_NIVEAU_MAX;
            }
        }
        else
        {
            // Atteint le max, passer en descente
            processusTriac_montee = 0;
        }
    }
    else
    {
        // Phase de descente
        if (processusTriac_niveau > 0)
        {
            if (processusTriac_niveau >= PROCESSUSTRIAC_INCREMENT)
            {
                processusTriac_niveau -= PROCESSUSTRIAC_INCREMENT;
            }
            else
            {
                processusTriac_niveau = 0;
            }
        }
        else
        {
            // Atteint le min, repasser en montée
            processusTriac_montee = 1;
        }
    }
    
    // Appliquer le nouveau niveau
    serviceTriac_fixeNiveau(processusTriac_niveau);
}