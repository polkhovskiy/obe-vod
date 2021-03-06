/*****************************************************************************
 * x264cli.h: x264cli common
 *****************************************************************************
 * Copyright (C) 2003-2013 x264 project
 *
 * Authors: Laurent Aimar <fenrir@via.ecp.fr>
 *          Loren Merritt <lorenm@u.washington.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@x264.com.
 *****************************************************************************/

#ifndef X264_CLI_H
#define X264_CLI_H

#include "common/common.h"

/* In microseconds */
#define UPDATE_INTERVAL 250000
#define MAX_SCC 1

typedef void *hnd_t;

static inline uint64_t gcd( uint64_t a, uint64_t b )
{
    while( 1 )
    {
        int64_t c = a % b;
        if( !c )
            return b;
        a = b;
        b = c;
    }
}

static inline uint64_t lcm( uint64_t a, uint64_t b )
{
    return ( a / gcd( a, b ) ) * b;
}

static inline char *get_filename_extension( char *filename )
{
    char *ext = filename + strlen( filename );
    while( *ext != '.' && ext > filename )
        ext--;
    ext += *ext == '.';
    return ext;
}

void x264_cli_log( const char *name, int i_level, const char *fmt, ... );
void x264_cli_printf( int i_level, const char *fmt, ... );

#define RETURN_IF_ERR( cond, name, ret, ... )\
if( cond )\
{\
    x264_cli_log( name, X264_LOG_ERROR, __VA_ARGS__ );\
    return ret;\
}

#define FAIL_IF_ERR( cond, name, ... ) RETURN_IF_ERR( cond, name, -1, __VA_ARGS__ )

typedef enum
{
    RANGE_AUTO = -1,
    RANGE_TV,
    RANGE_PC
} range_enum;

typedef struct __attribute__ ((__packed__)) {
    int hour;
    int min;
    int sec;
    int frame;
} cli_timecode_t;

typedef struct {
    FILE *scc_file;
    int sff;
    cli_timecode_t timecode;
} scc_opt_t;

typedef struct{
    int fps_num;
    int fps_den;
    int mod;
    int cc_count;
    int frame_doubling;
} cli_timecode_ctx_t;

typedef struct {
    int b_progress;
    int i_seek;
    hnd_t hin;
    hnd_t hout;
    FILE *qpfile;
    double timebase_convert_multiplier;
    int i_pulldown;
    int write_timecode;
    int drop_frame;
    cli_timecode_t timecode;
    cli_timecode_ctx_t *timecode_ctx;
    int num_scc;
    scc_opt_t scc_opts[MAX_SCC];
    int echostar_captions;
} cli_opt_t;

#endif
