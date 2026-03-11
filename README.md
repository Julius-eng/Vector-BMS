# Vector BMS

Open-source Battery Management System designed for high-voltage lithium battery packs with VESC integration.

## Overview

Vector BMS is a modular BMS supporting up to **24 series cells** (24S) with:
- Active cell monitoring and balancing
- High-current sensing (up to 120A)
- CAN bus communication (VESC-compatible)
- USB interface for configuration
- Isolated design for safety

## Hardware Architecture

### Schematic Structure

```
Vector_BMS.kicad_sch (Main)
├── Power management
├── Cell monitoring (LTC6811 × 2)
├── Current sensing
├── High-side switching
└── Connectors

MCU.kicad_sch
├── STM32L476 microcontroller
├── CAN interface (isolated)
├── isoSPI interface
└── USB interface

cell.kicad_sch / cell2.kicad_sch
└── Per-cell balancing circuits (×12 each)
```

### Key Components

| Component | Part Number | Function |
|-----------|-------------|----------|
| MCU | STM32L476RGT6 | ARM Cortex-M4, 80MHz, low power |
| Cell Monitor | LTC6811-1 (×2) | 12-cell stack monitor, ±1.2mV accuracy |
| isoSPI | LTC6820 | Isolated SPI for LTC6811 daisy chain |
| Current Sensor | INA226 | 16-bit I2C power monitor |
| Shunt Resistor | WSLP5931L1000FEA | 0.1mΩ, 15W, ±1% |
| CAN Transceiver | ISO1050DUBR | Isolated CAN 2.0B |
| USB-UART | CP2104 | USB to UART bridge |
| DC-DC | LM5165 | Wide-input buck converter |
| Balance FET | DMG2305UX-7 | P-ch MOSFET, SOT-23 |
| High-side Switch | IRFL4105PBF | N-ch logic-level MOSFET |

### Cell Configuration

- **Maximum cells:** 24S (two LTC6811 in daisy chain)
- **Cell voltage range:** 0V to 5V per cell (compatible with most Li-ion/LiFePO4)
- **Balance current:** ~100mA per cell (passive balancing)
- **Temperature monitoring:** 3× NTC thermistors

### Current Sensing

- **Shunt:** 0.1mΩ (WSLP5931, 15×7.6mm)
- **Max continuous:** 120A
- **Resolution:** ~0.3µV LSB (INA226 at ±40.96mV range)
- **Power dissipation:** 1.44W at 120A

## VESC Integration

Vector BMS is designed to work with [VESC](https://vesc-project.com/) motor controllers via CAN bus.

### CAN Communication

- **Protocol:** CAN 2.0B, 500 kbps (configurable)
- **Isolation:** Galvanically isolated via ISO1050
- **Messages supported:**
  - Battery voltage (total pack)
  - Individual cell voltages
  - Current (charge/discharge)
  - State of Charge (SoC)
  - Temperature
  - Fault status

### VESC Firmware Compatibility

The BMS communicates using VESC's CAN status messages:
- `CAN_PACKET_BMS_V_TOT` — Total pack voltage
- `CAN_PACKET_BMS_V_CELL` — Individual cell voltages
- `CAN_PACKET_BMS_I` — Pack current
- `CAN_PACKET_BMS_AH_WH` — Ah/Wh consumed
- `CAN_PACKET_BMS_SOC_SOH_TEMP` — SoC, SoH, temperature

VESC Tool can display BMS data in real-time and log it alongside motor controller data.

## MCU Capabilities

### STM32L476RGT6 Features

- **Core:** ARM Cortex-M4 @ 80MHz with FPU
- **Memory:** 1MB Flash, 128KB SRAM
- **Power:** Ultra-low-power modes (down to 30nA shutdown)

### Firmware Functions

1. **Cell Monitoring**
   - Read cell voltages via isoSPI (LTC6811)
   - Detect over/under-voltage conditions
   - Calculate State of Charge (SoC)

2. **Balancing Control**
   - Passive balancing via discharge resistors
   - Configurable balance threshold
   - Temperature-aware balancing

3. **Current Measurement**
   - Read shunt voltage via I2C (INA226)
   - Coulomb counting for SoC
   - Over-current protection

4. **Protection**
   - Over-voltage cutoff
   - Under-voltage cutoff
   - Over-current protection
   - Over-temperature protection
   - Short-circuit detection

5. **Communication**
   - CAN bus (VESC protocol)
   - USB serial (configuration/debugging)
   - Optional: UART, I2C expansion

6. **User Interface**
   - Status LEDs
   - Buzzer for alerts
   - OLED display support (optional)

## Connectors

| Connector | Function |
|-----------|----------|
| J1 | Main battery input |
| J2 | Charger input |
| J3 | OLED display |
| J12 | CAN bus |
| J14 | Serial/debug |
| J17 | Power button |
| J24 | USB (CP2104) |

## Getting Started

### Prerequisites

- KiCad 9.0+ for schematic/PCB editing
- STM32CubeIDE or PlatformIO for firmware development
- VESC Tool for motor controller integration

### Building

1. Clone the repository
2. Open `Vector_BMS.kicad_pro` in KiCad
3. Review schematic and PCB layout
4. Generate BOM and fabrication files

### Firmware

*Firmware repository link TBD*

The MCU firmware handles:
- LTC6811 communication via SPI/isoSPI
- INA226 current sensing via I2C
- CAN message transmission to VESC
- Protection state machine
- USB configuration interface

## License

*License TBD*

## Contributing

Contributions welcome! Please open an issue or pull request.

## Acknowledgments

- VESC Project for the open-source motor controller ecosystem
- Analog Devices for LTC6811 reference designs
- Arrow DAO community
