#include "../ina260.hpp"
#include "tusb.h"

#define I2C_PORT i2c0
#define I2C_SDA 12
#define I2C_SCL 13

INA260 voltage(I2C_PORT);

int main() {
    stdio_init_all();

    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    while (!tud_cdc_connected()) {
        sleep_ms(500);
    }
    printf("Connected\n");

    float current, bus_voltage, power;

    while (!voltage.begin()) {
        printf("Error: IMU failed to initialize\n");
    }

    while (true) {
        voltage.read_current(&current);
        voltage.read_bus_voltage(&bus_voltage);
        voltage.read_power(&power);

        printf("Current: %.f mA\n", current);
        printf("Bus Voltage: %.f mV\n", bus_voltage);
        printf("Power: %.f mW\n", power);

        printf("\n----------------------------------------\n\n");

        sleep_ms(20);
    }

    return 0;
}