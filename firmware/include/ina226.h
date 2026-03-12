/**
 * @file ina226.h
 * @brief INA226 Power Monitor Driver
 */

#ifndef INA226_H
#define INA226_H

#include <stdint.h>
#include <stdbool.h>

/*===========================================================================*/
/* INA226 Register Addresses                                                 */
/*===========================================================================*/

#define INA226_REG_CONFIG       0x00    // Configuration Register
#define INA226_REG_SHUNT_V      0x01    // Shunt Voltage Register
#define INA226_REG_BUS_V        0x02    // Bus Voltage Register
#define INA226_REG_POWER        0x03    // Power Register
#define INA226_REG_CURRENT      0x04    // Current Register
#define INA226_REG_CAL          0x05    // Calibration Register
#define INA226_REG_MASK         0x06    // Mask/Enable Register
#define INA226_REG_ALERT        0x07    // Alert Limit Register
#define INA226_REG_MFG_ID       0xFE    // Manufacturer ID (0x5449)
#define INA226_REG_DIE_ID       0xFF    // Die ID (0x2260)

/*===========================================================================*/
/* INA226 Configuration Bits                                                 */
/*===========================================================================*/

// Averaging mode (bits 11:9)
#define INA226_AVG_1            (0 << 9)
#define INA226_AVG_4            (1 << 9)
#define INA226_AVG_16           (2 << 9)
#define INA226_AVG_64           (3 << 9)
#define INA226_AVG_128          (4 << 9)
#define INA226_AVG_256          (5 << 9)
#define INA226_AVG_512          (6 << 9)
#define INA226_AVG_1024         (7 << 9)

// Bus voltage conversion time (bits 8:6)
#define INA226_VBUS_140US       (0 << 6)
#define INA226_VBUS_204US       (1 << 6)
#define INA226_VBUS_332US       (2 << 6)
#define INA226_VBUS_588US       (3 << 6)
#define INA226_VBUS_1100US      (4 << 6)
#define INA226_VBUS_2116US      (5 << 6)
#define INA226_VBUS_4156US      (6 << 6)
#define INA226_VBUS_8244US      (7 << 6)

// Shunt voltage conversion time (bits 5:3)
#define INA226_VSHUNT_140US     (0 << 3)
#define INA226_VSHUNT_204US     (1 << 3)
#define INA226_VSHUNT_332US     (2 << 3)
#define INA226_VSHUNT_588US     (3 << 3)
#define INA226_VSHUNT_1100US    (4 << 3)
#define INA226_VSHUNT_2116US    (5 << 3)
#define INA226_VSHUNT_4156US    (6 << 3)
#define INA226_VSHUNT_8244US    (7 << 3)

// Operating mode (bits 2:0)
#define INA226_MODE_POWER_DOWN  0
#define INA226_MODE_SHUNT_TRIG  1
#define INA226_MODE_BUS_TRIG    2
#define INA226_MODE_BOTH_TRIG   3
#define INA226_MODE_POWER_DOWN2 4
#define INA226_MODE_SHUNT_CONT  5
#define INA226_MODE_BUS_CONT    6
#define INA226_MODE_BOTH_CONT   7

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

typedef struct {
    int32_t  current_ma;        // Current in mA (signed, + = discharge)
    uint32_t bus_voltage_mv;    // Bus voltage in mV
    int32_t  shunt_voltage_uv;  // Shunt voltage in µV (signed)
    uint32_t power_mw;          // Power in mW
} ina226_data_t;

/*===========================================================================*/
/* Function Prototypes                                                       */
/*===========================================================================*/

/**
 * @brief Initialize INA226 power monitor
 * @param i2c_addr I2C address (typically 0x40)
 * @param cal_value Calibration register value
 * @return true on success
 */
bool ina226_init(uint8_t i2c_addr, uint16_t cal_value);

/**
 * @brief Read all measurements from INA226
 * @param data Pointer to data structure
 * @return true on success
 */
bool ina226_read(ina226_data_t *data);

/**
 * @brief Read raw shunt voltage
 * @return Shunt voltage in 2.5µV units (signed)
 */
int16_t ina226_read_shunt_raw(void);

/**
 * @brief Read raw bus voltage
 * @return Bus voltage in 1.25mV units
 */
uint16_t ina226_read_bus_raw(void);

/**
 * @brief Read current from current register
 * @return Current in LSB units (depends on calibration)
 */
int16_t ina226_read_current_raw(void);

/**
 * @brief Check if INA226 is present
 * @return true if manufacturer ID matches
 */
bool ina226_check_id(void);

/**
 * @brief Reset INA226
 */
void ina226_reset(void);

#endif /* INA226_H */
