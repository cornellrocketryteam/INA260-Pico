#include "ina260.hpp"
#include <cstdio>

INA260::INA260(i2c_inst_t *i2c_type) {
    i2c = i2c_type;
}

bool INA260::begin() {
    uint16_t id = get_id();
    if (id != INA260_MFR_ID) {
#ifdef VERBOSE
        fprintf(stderr, "Error: Voltage sensor got manufacturer ID value of %d\n", id);
#endif
        return false;
    }
    return true;
}

bool INA260::read_current(float *current) {
    uint8_t reg = INA260_REG_CURRENT;
    uint8_t data[2];

    if (i2c_write_timeout_us(i2c, INA260_ADDR, &reg, 1, true, BYTE_TIMEOUT_US) < 1) {
        return false;
    }
    if (i2c_read_timeout_us(i2c, INA260_ADDR, data, 2, false, 2 * BYTE_TIMEOUT_US) < 1) {
        return false;
    }

    *current = (float)((data[0] << 8) | data[1]) * 1.25;
    return true;
}

bool INA260::read_bus_voltage(float *bus_voltage) {
    uint8_t reg = INA260_REG_BUS_VOLTAGE;
    uint8_t data[2];

    if (i2c_write_timeout_us(i2c, INA260_ADDR, &reg, 1, true, BYTE_TIMEOUT_US) < 1) {
        return false;
    }
    if (i2c_read_timeout_us(i2c, INA260_ADDR, data, 2, false, 2 * BYTE_TIMEOUT_US) < 1) {
        return false;
    }

    *bus_voltage = (float)((data[0] << 8) | data[1]) * 1.25;
    return true;
}

bool INA260::read_power(float *power) {
    uint8_t reg = INA260_REG_POWER;
    uint8_t data[2];

    if (i2c_write_timeout_us(i2c, INA260_ADDR, &reg, 1, true, BYTE_TIMEOUT_US) < 1) {
        return false;
    }
    if (i2c_read_timeout_us(i2c, INA260_ADDR, data, 2, false, 2 * BYTE_TIMEOUT_US) < 1) {
        return false;
    }

    *power = (float)((data[0] << 8) | data[1]) * 10;
    return true;
}

uint16_t INA260::get_id() {
    uint8_t reg = INA260_REG_MFR_ID;
    uint8_t val[2];

    i2c_write_timeout_us(i2c, INA260_ADDR, &reg, 1, true, BYTE_TIMEOUT_US);
    i2c_read_timeout_us(i2c, INA260_ADDR, val, 2, false, BYTE_TIMEOUT_US);

    return (val[0] << 8) | val[1];
}