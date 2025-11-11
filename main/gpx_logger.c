#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "gps_parser.h"


int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void save_to_gpx(const DateTime *dt, GPS_Coordinate *gc, Speed *sp){
    char filename[50];

    // 🟢 додаємо .gpx і форматуємо красиво
    sprintf(filename, "/sdcard/track_%02d-%02d-%d.gpx",dt->dd, dt->mo, dt->yy );

    int already_exists = file_exists(filename);

    FILE *file = fopen(filename, "a");
    if(!file){
        printf("Помилка: не вдалося створити GPX файл!\n");
        return;
    }
    
    if (!already_exists)  {
        fprintf(file,
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<gpx version=\"1.1\" creator=\"Igor GPS Logger\" xmlns=\"http://www.topografix.com/GPX/1/1\">\n"
            "  <trk>\n"
            "    <name>GPS Track</name>\n"
            "    <trkseg>\n"
        );
        
    }

     fprintf(file,
        "      <trkpt lat=\"%.6f\" lon=\"%.6f\">\n"
        "        <ele>0.0</ele>\n"
        "        <time>20%02d-%02d-%02dT%02d:%02d:%02dZ</time>\n"
        "        <speed>%.2f</speed>\n"
        "      </trkpt>\n",
        gc->latitude, gc->longitude,
        dt->yy, dt->mo, dt->dd,
        dt->hh, dt->mm, dt->ss,
        sp->value
    );
    fclose(file);
}

void close_gpx(const DateTime *dt) {
    char filename[50];
    sprintf(filename, "track_%02d-%02d-%02d.gpx", dt->dd, dt->mo, dt->yy);

    FILE *file = fopen(filename, "a");
    if (file) {
        fprintf(file, "    </trkseg>\n  </trk>\n</gpx>\n");
        fclose(file);
    }
}