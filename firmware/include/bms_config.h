/**
 * @file bms_config.h
 * @brief Vector BMS Configuration
 */

#ifndef BMS_CONFIG_H
#define BMS_CONFIG_H

/*===========================================================================*/
/* Cell Configuration                                                        */
/*===========================================================================*/

#define BMS_NUM_CELLS           24      // Total cells (2x LTC6811)
#define BMS_NUM_LTC6811         2       // Number of LTC6811 ICs
#define BMS_CELLS_PER_IC        12      // Cells per LTC6811

#define BMS_NUM_THERMISTORS     3       // Temperature sensors

/*===========================================================================*/
/* Voltage Limits (mV)                                                       */
/*===========================================================================*/

#define CELL_OV_THRESHOLD       4200    // Over-voltage cutoff
#define CELL_OV_RECOVERY        4150    // OV recovery threshold
#define CELL_UV_THRESHOLD       2800    // Under-voltage cutoff
#define CELL_UV_RECOVERY        3000    // UV recovery threshold
#define CELL_BALANCE_THRESHOLD  3300    // Start balancing above this

#define CELL_BALANCE_DELTA      10      // Balance if cell > min + delta (mV)

/*===========================================================================*/
/* Current Limits (mA)                                                       */
/*===========================================================================*/

#define PACK_MAX_CHARGE_CURRENT     60000   // 60A charge
#define PACK_MAX_DISCHARGE_CURRENT  120000  // 120A discharge
#define PACK_SHORT_CIRCUIT_CURRENT  200000  // 200A short circuit

/*===========================================================================*/
/* Temperature Limits (°C × 10)                                              */
/*===========================================================================*/

#define TEMP_OT_CHARGE          450     // 45°C max charge temp
#define TEMP_OT_DISCHARGE       600     // 60°C max discharge temp
#define TEMP_UT_CHARGE          0       // 0°C min charge temp
#define TEMP_UT_DISCHARGE       -200    // -20°C min discharge temp

/*===========================================================================*/
/* Current Sensing                                                           */
/*===========================================================================*/

#define SHUNT_RESISTANCE_UOHM   100     // 0.1 mΩ = 100 µΩ
#define INA226_I2C_ADDR         0x40    // INA226 I2C address

// INA226 calibration: CAL = 0.00512 / (Current_LSB × R_shunt)
// For 1mA/bit LSB and 0.1mΩ: CAL = 0.00512 / (0.001 × 0.0001) = 51200
#define INA226_CAL_VALUE        51200

/*===========================================================================*/
/* CAN Configuration                                                         */
/*===========================================================================*/

#define CAN_BITRATE             500000  // 500 kbps
#define CAN_BMS_ID              10      // BMS CAN ID for VESC

/*===========================================================================*/
/* Timing                                                                    */
/*===========================================================================*/

#define CELL_SAMPLE_INTERVAL_MS     100     // Cell voltage sample rate
#define CURRENT_SAMPLE_INTERVAL_MS  10      // Current sample rate
#define BALANCE_CHECK_INTERVAL_MS   1000    // Balance check rate
#define CAN_TX_INTERVAL_MS          100     // CAN message rate

#endif /* BMS_CONFIG_H */
