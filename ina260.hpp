#ifndef INA260_HPP
#define INA260_HPP

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define INA260_ADDR (0x44)

#define INA260_REG_CONFIG (0x00)
#define INA260_REG_CURRENT (0x01)
#define INA260_REG_BUS_VOLTAGE (0x02)
#define INA260_REG_POWER (0x03)

#define INA260_REG_MFR_ID (0xFE)
#define INA260_MFR_ID (0x5449)

#define BYTE_TIMEOUT_US (5000)

class INA260 {
public:
    INA260(i2c_inst_t *i2c_type);
    bool begin();

    bool read_current(float *current);

    bool read_bus_voltage(float *bus_voltage);

    bool read_power(float *power);
private:
    /**
     * Reads the INA260's manufacturer ID.
     * @return The resulting manufacturer ID
     */
    uint16_t get_id();

    /**
     * The I2C bus
     */
    i2c_inst_t *i2c;
};

#endif // INA260_HPP