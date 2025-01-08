#ifndef INA260_HPP
#define INA260_HPP

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define INA260_ADDR (0x44)

#define INA260_REG_CONFIG (0x00)
#define INA260_REG_CURRENT (0x01)
#define INA260_REG_BUS_VOLTAGE (0x02)
#define INA260_REG_POWER (0x03)

#define INA260_REG_MFR_ID (0xFE)
#define INA260_MFR_ID (0x5449)

#define BYTE_TIMEOUT_US (5000)

/**
 * Representation of the INA260 sensor
 */
class INA260 {
public:
    /**
     * Initializes an INA260 object on an I2C bus.
     * @param i2c_type The I2C bus that this sensor is on
     */
    INA260(i2c_inst_t *i2c_type);

    /**
     * Attempts to establish a connection with the sensor.
     * @return True on successful connection, false otherwise
     */
    bool begin();

    /**
     * Reads current values, in mA.
     * @param current The resulting current
     * @return True on successful read, false otherwise
     */
    bool read_current(float *current);

    /**
     * Reads bus voltage values, in mV.
     * @param bus_voltage The resulting bus voltage
     * @return True on successful read, false otherwise
     */
    bool read_bus_voltage(float *bus_voltage);

    /**
     * Reads power values, in mW.
     * @param power The resulting power
     * @return True on successful read, false otherwise
     */
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