/*
 *   Mymeco (or My Media Collector) is a software that give you all tools
 *   to manage your video collection. This include fetching meta-information
 *   of video like director, actors or synopsis directly from internet or
 *   technical information like codec, resolution from video file itself.
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
#   ifdef __cplusplus
#       include <iostream>
#   else
#       include <stdio.h>
#   endif
#endif

#if LOGLEVEL > 0
#   ifdef __cplusplus
#       define ELOG(info) do {\
                std::wcout << "[E] " << __func__ << ":" << __LINE__ << " ";\
                std::wcout << info << std::endl;\
        } while (0)
#   else
#       define ELOG(fmt, args...) printf("[E] %s:%u "fmt"\n", __func__,\
                                                        __LINE__,\
                                                        ##args)
#   endif
#else
#       define ELOG(fmt, args...)
#endif

#if LOGLEVEL > 1
#   ifdef __cplusplus
#       define WLOG(info) do {\
                std::wcout << "[W] " << __func__ << ":" << __LINE__ << " ";\
                std::wcout << info << std::endl;\
        } while (0)
#   else
#       define WLOG(fmt, args...) printf("[W] %s:%u "fmt"\n", __func__,\
                                                        __LINE__,\
                                                        ##args)
#   endif
#else
#       define WLOG(fmt, args...)
#endif

#if LOGLEVEL > 2
#   ifdef __cplusplus
#       define ILOG(info) do {\
                std::wcout << "[I] " << __func__ << ":" << __LINE__ << " ";\
                std::wcout << info << std::endl;\
        } while (0)
#   else
#       define ILOG(fmt, args...) printf("[I] %s:%u "fmt"\n", __func__,\
                                                        __LINE__,\
                                                        ##args)
#   endif
#else
#       define ILOG(fmt, args...)
#endif

#if LOGLEVEL > 3
#   ifdef __cplusplus
#       define DLOG(info) do {\
                std::wcout << "[D] " << __func__ << ":" << __LINE__ << " ";\
                std::wcout << info << std::endl;\
        } while (0)
#   else
#       define DLOG(fmt, args...) printf("[D] %s:%u "fmt"\n", __func__,\
                                                        __LINE__,\
                                                        ##args)
#   endif
#else
#       define DLOG(fmt, args...)
#       define ENTER_FN
#endif

#if LOGLEVEL > 4
#   ifdef __cplusplus
#       define ENTER_FN() std::wcout << "[F] -> " << __func__ << ":" << __LINE__ << std::endl
#   else
#       define ENTER_FN() printf("[F] -----> %s (%u)\n", __func__, __LINE__)
#   endif
#else
#       define ENTER_FN()
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) < (b)) ? (b) : (a))

typedef enum {
        ok                  = 0,
        not_available       ,
        quit_unexpectedly   ,
        not_implemented     ,
        file_io             ,
        mem_error           ,
        already_present     ,
        not_exist           ,
        wrong_argument      ,
        internal_error      ,
} err_code;

#ifndef __cplusplus
typedef enum {
        false   = 0,
        true    = 1
} bool;
#endif

#define   NO_ERROR      0x0000
#define  LEX_ERROR      0x0001
#define  SYN_ERROR      0x0002
#define NULL_ERROR      0x8000

#endif
