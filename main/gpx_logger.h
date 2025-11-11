#ifndef GPX_LOGGER_H
#define GPX_LOGGER_H

#include "gps_types.h"
#include "gps_parser.h"


#ifdef __cplusplus
extern "C" {
#endif

void save_to_gpx(const DateTime *dt, GPS_Coordinate *gc, Speed *sp);
void close_gpx(const DateTime *dt);
int file_exists(const char *filename);

#ifdef __cplusplus
}
#endif

#endif