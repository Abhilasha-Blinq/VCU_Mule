/*
 * delay.c
 *
 *  Created on: 07-Jul-2025
 *      Author: Rohit
 */
#include "stdio.h"
#include "pdb_driver.h"

void delay(uint32_t cnt)
{
	while(cnt!=0)
	{
		cnt--;
	}
}

bool calculateIntValue(const pdb_timer_config_t *pdbConfig, uint32_t uSec, uint16_t * intVal)
{

    /* Local variables used to store different parameters
     * such as frequency and prescalers
     */
    uint32_t    intVal_l            = 0;
    uint8_t     pdbPrescaler        = (1 << pdbConfig->clkPreDiv);
    uint8_t     pdbPrescalerMult    = 0;
    uint32_t    pdbFrequency;

    bool resultValid = false;

    /* Get the Prescaler Multiplier from the configuration structure */
    switch (pdbConfig->clkPreMultFactor)
    {
        case PDB_CLK_PREMULT_FACT_AS_1:
            pdbPrescalerMult    =   1U;
            break;
        case PDB_CLK_PREMULT_FACT_AS_10:
            pdbPrescalerMult    =   10U;
            break;
        case PDB_CLK_PREMULT_FACT_AS_20:
            pdbPrescalerMult    =   20U;
            break;
        case PDB_CLK_PREMULT_FACT_AS_40:
            pdbPrescalerMult    =   40U;
            break;
        default:
            /* Defaulting the multiplier to 1 to avoid dividing by 0*/
            pdbPrescalerMult    =   1U;
            break;
    }

    /* Get the frequency of the PDB clock source and scale it
     * so that the result will be in microseconds.
     */
    CLOCK_SYS_GetFreq(CORE_CLOCK, &pdbFrequency);
    pdbFrequency /= 1000000;

    /* Calculate the interrupt value for the prescaler, multiplier, frequency
     * configured and time needed.
     */
    intVal_l = (pdbFrequency * uSec) / (pdbPrescaler * pdbPrescalerMult);

    /* Check if the value belongs to the interval */
    if((intVal_l == 0) || (intVal_l >= (1 << 16)))
    {
        resultValid = false;
        (*intVal) = 0U;
    }
    else
    {
        resultValid = true;
        (*intVal) = (uint16_t)intVal_l;
    }

    return resultValid;
}



