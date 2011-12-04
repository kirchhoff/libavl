/*   
 *   
 *   Copyright (C) 2011 Adrien Oliva
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SYSLOG_H__
#define __SYSLOG_H__

#if LOGLEVEL != 0
#       include <stdio.h>
#endif

#if LOGLEVEL > 0
#       define ELOG(fmt, args...) printf("[E] %s:%u "fmt"\n", __func__,\
                                                        __LINE__,\
                                                        ##args)
#else
#       define ELOG(fmt, args...)
#endif

#if LOGLEVEL > 1
#       define WLOG(fmt, args...) printf("[W] %s:%u "fmt"\n", __func__,\
                                                        __LINE__,\
                                                        ##args)
#else
#       define WLOG(fmt, args...)
#endif

#if LOGLEVEL > 2
#       define ILOG(fmt, args...) printf("[I] %s:%u "fmt"\n", __func__,\
                                                        __LINE__,\
                                                        ##args)
#else
#       define ILOG(fmt, args...)
#endif

#if LOGLEVEL > 3
#       define DLOG(fmt, args...) printf("[D] %s:%u "fmt"\n", __func__,\
                                                        __LINE__,\
                                                        ##args)
#else
#       define DLOG(fmt, args...)
#       define ENTER_FN
#endif

#if LOGLEVEL > 4
#       define ENTER_FN printf("[F] -----> %s (%u)\n", __func__, __LINE__)
#else
#       define ENTER_FN
#endif

#define MIN(a, b) ((a) < (b)? (a):(b))
#define MAX(a, b) ((a) < (b)? (b):(a))

typedef enum {
        ok                  = 0,
        not_available       ,
        quit_unexpectedly   ,
        not_implemented     ,
        file_io             ,
        mem_error           ,
        already_present     ,
        not_exist           ,
        wrong_argument
} err_code;

typedef enum {
        false   = 0,
        true    = 1
} bool;

#endif
