/***********************************************************************************************************************
 * This file was generated by the S32 Config Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef adc_config_1_H
#define adc_config_1_H

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * The global macro will be used in function call of the module.
 *
 */
/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "adc_driver.h"

/*******************************************************************************
 * Definitions 
 ******************************************************************************/

/*Device instance number */
#define INST_ADC_CONFIG_1  (0U)

/*******************************************************************************
 * Global variables 
 ******************************************************************************/

/* User configurations */

/* Converter configuration 0 */
extern const adc_converter_config_t adc_config_1_ConvConfig0;

/* Hw Average configuration 0 */
extern const adc_average_config_t adc_config_1_HwAvgConfig0;



#endif /* adc_config_1_H */
