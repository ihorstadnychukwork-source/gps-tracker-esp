#include "driver/uart.h"
#include "driver/spi_master.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "hw_config.h"
#include "esp_log.h"


#include "hw_config.h"


    static const char *TAG = "GPS_INIT";


    void hardware_init(void) {
    //------------------------------UART GPS-----------------------------
    //ініціалізація UART---------------------------------------------
    const uart_port_t uart_num = UART_NUM_2;
    uart_config_t uart_config = {
        .baud_rate = BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,

    };
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    uart_set_pin(UART_GPS, TX2, RX2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_GPS, 4096, 4096, 0, NULL, 0);
    ESP_LOGI("UART", "GPS UART initialized");

    //------------------------SD card-----------------------
    // створюємо структуру з налаштуваннями ліній SPI (GPIO для MOSI, MISO, CLK)
    // spi_bus_config_t buscfg = {...} Описує GPIO для SPI-шини
     sdmmc_host_t host = SDSPI_HOST_DEFAULT();
     host.max_freq_khz = 4000;

    spi_bus_config_t buscfg = { 
        .miso_io_num = PIN_NUM_MISO,  // пін для прийому даних від Slave → Master (DO)
        .mosi_io_num = PIN_NUM_MOSI,  // пін для передачі даних Master → Slave (DI)
        .sclk_io_num = PIN_NUM_CLK,   // пін для тактового сигналу (SPI Clock)
        .quadwp_io_num = -1,          // не використовується (для Quad SPI)
        .quadhd_io_num = -1,          // не використовується (для Quad SPI)

    };
    // ініціалізуємо SPI-шину
    // spi_bus_initialize() Активує SPI-контролер у ESP32
    ESP_ERROR_CHECK(spi_bus_initialize(SPI_SD, &buscfg, SPI_DMA_CH_AUTO)); 

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = 13;
    slot_config.host_id = host.slot;
   
    // створюємо структуру з параметрами конкретного SPI-пристрою (наприклад SD-карти)
    sdspi_device_config_t dev_cfg = SDSPI_DEVICE_CONFIG_DEFAULT();
    dev_cfg.gpio_cs = PIN_NUM_CS;    // пін CS
    dev_cfg.host_id = host.slot;       // SPI2 або SPI3
    
    esp_vfs_fat_mount_config_t mount_config ={
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    sdmmc_card_t *card;
    //ESP_ERROR_CHECK(esp_vfs_fat_sdspi_mount("/sdcard", &host, &dev_cfg, &mount_config, &card));
   esp_err_t ret = esp_vfs_fat_sdspi_mount("/sdcard", &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        ESP_LOGE("TEST", "SD init failed: %s", esp_err_to_name(ret));
        return;
    }
     sdmmc_card_print_info(stdout, card);
    }
