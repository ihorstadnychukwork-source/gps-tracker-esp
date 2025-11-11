#include "gps_parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// --- Група: Час і дата ---
void get_uts_time(const char *nmea, DateTime *dt){
      
        const char *p = strchr(nmea, ',');
        if(!p) return;
        p++;

        char time_str[7];
        if (strlen(p) < 6) return;
        memcpy(time_str, p, 6);
        time_str[6] = '\0';

        char hh[3], mm[3], ss[3];
        memcpy(hh, time_str, 2); hh[2] = '\0';
        memcpy(mm, &time_str[2], 2); mm[2] = '\0';
        memcpy(ss, &time_str[4], 2); ss[2] = '\0';

        dt->hh = atoi(hh);
        dt->mm = atoi(mm);
        dt->ss = atoi(ss);
}

void get_uts_date(const char *nmea, DateTime *dt){
        const char *p = nmea;
        for (int i = 0; i < 9; i++) {// 9 кома
            p = strchr(p, ','); // знайти наступну кому
            if (!p) return; // якщо більше немає ком
            p++; // перейти після знайденої коми
    }
        if (strlen(p) < 6) return;

        char date_str[7];
        memcpy(date_str, p, 6);
        date_str[6] = '\0';

        char dd[3], mo[3], yy[3];
        memcpy(dd,  date_str, 2); dd[2] = '\0';
        memcpy(mo, &date_str[2], 2); mo[2] = '\0';
        memcpy(yy, &date_str[4], 2); yy[2] = '\0';

        dt->dd = atoi(dd);
        dt->mo = atoi(mo);
        dt->yy = atoi(yy);
}

void print_datetime(const DateTime *dt){
    printf("UTC: %02d.%02d.%02d %02d:%02d:%02d\n",
           dt->dd, dt->mo, dt->yy,
           dt->hh, dt->mm, dt->ss);

}

// --- Група: Координати ---

void get_latitude(const char *nmea, GPS_Coordinate *gc){
    const char *p = nmea;
    for(int i = 0; i < 3; i++){
        p = strchr(p, ',');
        if(!p) return;
        p++;
    }
    const char *start = p;
    const char *end = strchr(start, ',');
    const char *indikator_SN = strchr(end , ',');
    
    if(!end) return;

    int len = end - start;


    char latitude [20];
    if(len >= sizeof(latitude)) len = sizeof(latitude) -1;
 
    memcpy(latitude, p, len);
    latitude[len] = '\0';

    
    char lat_dir = *(end + 1);
    

    double latitude_f = atof(latitude);
    double degree = (int) latitude_f / 100;
    double min = latitude_f - (degree * 100);
    double dec = degree + (min / 60);
       
    gc->latitude = dec;
    gc->lat_dir = lat_dir;
}

void get_longitude(const char *nmea, GPS_Coordinate *gc){
    const char *p = nmea;
    // цикл для того щоб перейти до ',' під 5 номером,
    for(int i = 0; i < 5; i++){
        p = strchr(p, ','); // 
        if(!p) return;
        p++;
    }

    const char *start = p;
    const char *end = strchr(start, ',');
  
    
    if(!end) return;

    int len = end - start;

    char longitude[20];
    if(len >= sizeof(longitude)) len = sizeof(longitude) - 1;
    memcpy(longitude, p, len);
    longitude[len] = '\0';

    char lon_dir = *(end + 1);


    double longitude_f = atof(longitude); 
    double degree = (int) longitude_f / 100;  
    double min = longitude_f - (degree * 100);  
    double dec = degree + (min / 60);

    gc->lon_dir = lon_dir;
    gc->longitude = dec;
}

// --- Група: Швидкість і курс ---

void get_speed(const char *nmea, Speed *sp){
    const char *p = nmea;

    // 🔵 Має бути <6, бо швидкість — після 7-ї коми (рахуючи з 0)
    for(int i = 0; i < 7; i++){
        p = strchr(p, ','); 
        if (!p) return; // якщо не знайдено кому — виходимо
        p++;    // 🟢 пересуваємось після коми
    }
     // 🟢 Перевіряємо, щоб далі був якийсь текст
     
    if (*p == ',' || *p == '\0') return;

    const char *start = p;
    const char *end = strchr(start, ','); // 🔵 знаходимо наступну кому
    // 🟢 перевірка, якщо немає кінця
     if (!end) return;


    int len = end - start;
    
    char data_speed[10];
    ////"якщо рядок довше ніж розмір буфера — обрізаємо".
    if(len >= sizeof(data_speed)) len = sizeof(data_speed) - 1;

    memcpy(data_speed, start, len);
    data_speed[len] = '\0'; // 🔵 термінатор після копіювання

    // 🟢 Конвертуємо текст у число
    sp->average = atof(data_speed);
}

void get_course( const char *nmea,  Speed *sp){
    const char *p = nmea;

    for(int i = 0; i < 3; i++){
        p = strchr(p, ',');
        if (!p) return;
        p++;
    }
    if(*p == ',' || *p =='\0') return;

    const char *start = p;
    const char *end  = strchr(p, ',');
    int len = end - start;

    char data_course[7];
    if( len >= sizeof(data_course)) len = sizeof(data_course) - 1;

    memcpy(data_course, start, len);
    data_course[len] = '\0';

    sp->course = atof(data_course);
}
