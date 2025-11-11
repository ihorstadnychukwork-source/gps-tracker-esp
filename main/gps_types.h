#ifndef GPS_TYPES_H
#define GPS_TYPES_H



#ifdef __cplusplus
extern "C" {
#endif

// Структура для координат GPS
typedef struct {
    //char latitude_char[20];
    float latitude;     // десяткові градуси
    float longitude;    // десяткові градуси
    char lat_dir;       // N / S
    char lon_dir;       // E / W
} GPS_Coordinate;

// Структура для дати й часу UTC
typedef struct {
    int hh, mm, ss; // година, хвилина, секунда
    int dd, mo, yy; // день, місяць, рік (2 останні цифри)
} DateTime;

// Структура для швидкості й курсу
typedef struct{
    float value, average;// поточна швидкість, середня швидкість
    double course; // напрям руху
    char unit[4]; // одиниця ("kmh", "mps", тощо)
} Speed; 

#ifdef __cplusplus
}
#endif

#endif
