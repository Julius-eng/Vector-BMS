/**
 * @file ltc6811.h
 * @brief LTC6811-1 Battery Stack Monitor Driver
 */

#ifndef LTC6811_H
#define LTC6811_H

#include <stdint.h>
#include <stdbool.h>
#include "bms_config.h"

/*===========================================================================*/
/* LTC6811 Commands                                                          */
/*===========================================================================*/

#define LTC6811_CMD_WRCFGA      0x0001  // Write Configuration Register Group A
#define LTC6811_CMD_RDCFGA      0x0002  // Read Configuration Register Group A
#define LTC6811_CMD_RDCVA       0x0004  // Read Cell Voltage Register Group A
#define LTC6811_CMD_RDCVB       0x0006  // Read Cell Voltage Register Group B
#define LTC6811_CMD_RDCVC       0x0008  // Read Cell Voltage Register Group C
#define LTC6811_CMD_RDCVD       0x000A  // Read Cell Voltage Register Group D
#define LTC6811_CMD_RDAUXA      0x000C  // Read Auxiliary Register Group A
#define LTC6811_CMD_RDAUXB      0x000E  // Read Auxiliary Register Group B
#define LTC6811_CMD_RDSTATA     0x0010  // Read Status Register Group A
#define LTC6811_CMD_RDSTATB     0x0012  // Read Status Register Group B
#define LTC6811_CMD_ADCV        0x0260  // Start Cell Voltage ADC Conversion
#define LTC6811_CMD_ADAX        0x0460  // Start Auxiliary ADC Conversion
#define LTC6811_CMD_CLRCELL     0x0711  // Clear Cell Voltage Register Groups
#define LTC6811_CMD_CLRAUX      0x0712  // Clear Auxiliary Register Groups

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

typedef struct {
    uint16_t cell_voltage[BMS_CELLS_PER_IC];    // Cell voltages in 100µV units
    uint16_t gpio_voltage[5];                    // GPIO voltages (thermistors)
    uint16_t ref_voltage;                        // Reference voltage
    uint16_t sum_of_cells;                       // Sum of all cells
    uint16_t die_temp;                           // Internal die temperature
    uint8_t  discharge_flags;                    // Discharge control bits
    bool     pec_valid;                          // PEC check passed
} ltc6811_data_t;

typedef struct {
    ltc6811_data_t ic[BMS_NUM_LTC6811];
} ltc6811_chain_t;

/*===========================================================================*/
/* Function Prototypes                                                       */
/*===========================================================================*/

/**
 * @brief Initialize LTC6811 driver and isoSPI interface
 * @return true on success
 */
bool ltc6811_init(void);

/**
 * @brief Wake up LTC6811 from sleep
 */
void ltc6811_wakeup(void);

/**
 * @brief Write configuration to all LTC6811 in chain
 * @param discharge_bits Discharge enable bits for each cell
 * @return true on success
 */
bool ltc6811_write_config(uint16_t discharge_bits[BMS_NUM_LTC6811]);

/**
 * @brief Start cell voltage ADC conversion
 * @param mode ADC mode (0=422Hz, 1=27kHz, 2=7kHz, 3=26Hz)
 */
void ltc6811_start_cell_adc(uint8_t mode);

/**
 * @brief Read cell voltages from all LTC6811 in chain
 * @param data Pointer to chain data structure
 * @return true if all PEC checks pass
 */
bool ltc6811_read_cell_voltages(ltc6811_chain_t *data);

/**
 * @brief Start auxiliary (GPIO/temp) ADC conversion
 */
void ltc6811_start_aux_adc(void);

/**
 * @brief Read auxiliary voltages (thermistors)
 * @param data Pointer to chain data structure
 * @return true if all PEC checks pass
 */
bool ltc6811_read_aux_voltages(ltc6811_chain_t *data);

/**
 * @brief Calculate PEC15 checksum
 * @param data Data buffer
 * @param len Length of data
 * @return 15-bit PEC value
 */
uint16_t ltc6811_calc_pec(uint8_t *data, uint8_t len);

/**
 * @brief Convert raw ADC value to millivolts
 * @param raw Raw 16-bit ADC value (100µV units)
 * @return Voltage in millivolts
 */
static inline uint16_t ltc6811_raw_to_mv(uint16_t raw) {
    return (raw + 5) / 10;  // Round to nearest mV
}

#endif /* LTC6811_H */
