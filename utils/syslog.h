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
#   include <iostream>
#endif

/** \def ELOG(fmt, args...)
 * \brief Macro to log error.
 *
 * \param fmt Format of message logged.
 * \param args Argument(s) needed by format message.
 *
 * If \c LOGLEVEL macro is set to a value higher than 0, the \c ELOG
 * macro will be expanded to a message on \c stdout, with flag \c [E],
 * the name of function and current line, and your message. The \c fmt
 * and \c args... arguments use the \c printf format.
 */
#if LOGLEVEL > 0
#   define ELOG(fmt, args...) printf("[E] %s:%u "fmt"\n", __func__,\
                                                          __LINE__,\
                                                          ##args)
#else
#   define ELOG(fmt, args...)
#endif

/** \def WLOG(fmt, args...)
 * \brief Macro to log warning.
 *
 * \param fmt Format of message logged.
 * \param args Argument(s) needed by format message.
 *
 * If \c LOGLEVEL macro is set to a value higher than 1, the \c WLOG
 * macro will be expanded to a message on \c stdout, with flag \c [W],
 * the name of function and current line, and your message. The \c fmt
 * and \c args... arguments use the \c printf format.
 */
#if LOGLEVEL > 1
#   define WLOG(fmt, args...) printf("[W] %s:%u "fmt"\n", __func__,\
                                                          __LINE__,\
                                                          ##args)
#else
#   define WLOG(fmt, args...)
#endif

/** \def ILOG(fmt, args...)
 * \brief Macro to log information.
 *
 * \param fmt Format of message logged.
 * \param args Argument(s) needed by format message.
 *
 * If \c LOGLEVEL macro is set to a value higher than 2, the \c ILOG
 * macro will be expanded to a message on \c stdout, with flag \c [I],
 * the name of function and current line, and your message. The \c fmt
 * and \c args... arguments use the \c printf format.
 */
#if LOGLEVEL > 2
#   define ILOG(fmt, args...) printf("[I] %s:%u "fmt"\n", __func__,\
                                                          __LINE__,\
                                                          ##args)
#else
#   define ILOG(fmt, args...)
#endif

/** \def DLOG(fmt, args...)
 * \brief Macro to log debug info.
 *
 * \param fmt Format of message logged.
 * \param args Argument(s) needed by format message.
 *
 * If \c LOGLEVEL macro is set to a value higher than 3, the \c DLOG
 * macro will be expanded to a message on \c stdout, with flag \c [D],
 * the name of function and current line, and your message. The \c fmt
 * and \c args... arguments use the \c printf format.
 */
#if LOGLEVEL > 3
#   define DLOG(fmt, args...) printf("[D] %s:%u "fmt"\n", __func__,\
                                                          __LINE__,\
                                                          ##args)
#else
#   define DLOG(fmt, args...)
#endif

/** \def ENTER_FN()
 * \brief Macro to log start of function.
 *
 * If \c LOGLEVEL macro is set to a value higher than 4, the \c ENTER_FN
 * macro will be expanded to a message on \c stdout, with flag \c [F],
 * the name of function and current line.
 */
#if LOGLEVEL > 4
#   define ENTER_FN() printf("[F] -----> %s (%u)\n", __func__, __LINE__)
#else
#   define ENTER_FN()
#endif

#endif
