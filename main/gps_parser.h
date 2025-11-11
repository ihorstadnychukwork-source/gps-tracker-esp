#ifndef _GPS_PARSER_H_
#define _GPS_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gps_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void get_uts_time(const char *nmea, DateTime *dt);
void get_uts_date(const char *nmea, DateTime *dt);
void print_datetime(const DateTime *dt);
void get_latitude(const char *nmea, GPS_Coordinate *gc);
void get_longitude(const char *nmea, GPS_Coordinate *gc);
void get_speed(const char *nmea, Speed *sp);
void get_course( const char *nmea,  Speed *sp);


#ifdef __cplusplus
}
#endif


#endif  // _GPS_PARSER_H_