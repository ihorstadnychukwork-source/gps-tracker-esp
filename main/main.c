#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "gps_parser.h"
#include "gpx_logger.h"
#include "gps_types.h"
#include "hw_config.h"
#include "hardware_init.h"



static const char *TAG_GPS= "GPS";

void read_gps_data(void)
{
   static DateTime gps_dt = {0};
    static GPS_Coordinate gps_pos = {0};
    static Speed gps_spd = {0};
    static bool            have_fix = false;   // маємо валідний RMC (A)
    static bool            have_spd = false;   // маємо швидкість з VTG
    static uint32_t        nmea_cnt = 0;      // лічильник отриманих NMEA рядків

    static char line[GPS_LINE_MAX];  // 🔹 буфер для збирання рядка
    static int idx = 0;              // 🔹 позиція в буфері

    uint8_t ch;
    int len = uart_read_bytes(UART_GPS, &ch, 1, pdMS_TO_TICKS(1000));
    if (len > 0) {
        if (ch == '\r') return;      // ігноруємо carriage return У NMEA рядки закінчуються \r\n
        
        if (ch == '\n') {              // Коли прийшов \n, це кінець рядка → ставимо '\0', щоб line став валідним C-рядком.
             if (idx < GPS_LINE_MAX - 1) {
            line[idx++] = (char)ch;

            } else {
            // переповнення — скидаємо поточний рядок
            idx = 0;
            }
            return;
        }


         // тут ch == '\n' → кінець рядка
        line[idx] = '\0';
        idx = 0;
        if (line[0] != '$' || strlen(line) < 6) return; // не схоже на NMEA

        ESP_LOGI(TAG_GPS, "NMEA: %s", line);
        nmea_cnt++;

        if (strncmp(line, "$GPRMC", 6) == 0) {
            // Перевірка валідності фікса (поле статусу = 'A')
            // Проста перевірка: знаходимо другу кому і дивимось символ після неї
            const char *p = line;
            for (int i = 0; i < 2 && p; i++) { p = strchr(p, ','); if (p) p++; }
            bool valid = (p && *p == 'A');

            get_uts_time(line, &gps_dt);
            get_uts_date(line, &gps_dt);
            get_latitude(line, &gps_pos);
            get_longitude(line, &gps_pos);

            have_fix = valid;
            ESP_LOGI(TAG_GPS, "Fix: %s | UTC %02d:%02d:%02d  Lat %.6f  Lon %.6f",
                    have_fix ? "A" : "V",
                     gps_dt.hh, gps_dt.mm, gps_dt.ss,
                     gps_pos.latitude, gps_pos.longitude);
        }
        else if (strncmp(line, "$GPVTG", 6) == 0) {
            get_speed(line, &gps_spd);
            gps_spd.value = gps_spd.average;     // у тебе швидкість уже в км/год
            strcpy(gps_spd.unit, "kmh");
            have_spd = true;

            ESP_LOGI(TAG_GPS, "Speed: %.3f %s", gps_spd.value, gps_spd.unit);
        }
        // ---- Коли є все потрібне — можемо писати у GPX ----
         // Щоб берегти SD, пишемо, наприклад, кожні 30 отриманих NMEA-рядків
        if (have_fix && have_spd && (nmea_cnt % 30 == 0)) {
            save_to_gpx(&gps_dt, &gps_pos, &gps_spd);
            ESP_LOGI(TAG_GPS, "GPX point saved.");
        }
    }
}
void app_main(void)
{   
    
hardware_init();

    
while (1){
    read_gps_data(); 
    vTaskDelay(pdMS_TO_TICKS(10));

}
    
}
        

 
