#ifndef HW_CONFIG_H
#define HW_CONFIG_H
#include "driver/uart.h"


#ifdef __cplusplus
extern "C" {
#endif

#define UART_GPS UART_NUM_2
#define RX2 GPIO_NUM_16
#define TX2 GPIO_NUM_17
#define PIN_NUM_MISO GPIO_NUM_19
#define PIN_NUM_MOSI GPIO_NUM_23
#define PIN_NUM_CLK GPIO_NUM_18
#define PIN_NUM_CS GPIO_NUM_13
#define SPI_SD SPI2_HOST
#define BAUD 9600
#define GPS_RX_BUF_SIZE 1024
#define GPS_LINE_MAX 120


#ifdef __cplusplus
}
#endif

#endif