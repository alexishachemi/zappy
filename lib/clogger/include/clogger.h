/*
** EPITECH PROJECT, 2023
** clogger
** File description:
** logging functions
*/

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define LOG_SIZE 2048
#define EXPAND(m) #m
#define STRINGIFY(m) EXPAND(m)
#define LOG_MAX_LINES 100
#define LOG_LEVEL_SIZE 9
#define SEP " - "
#define LOG_META __DATE__ " "  __TIME__ SEP __FILE__ ":" STRINGIFY(__LINE__)

/// @brief Convenience macro for writing log messages using printf-style
/// formatting. Includes metadata.
/// @param lptr logger pointer
/// @param lvl log level
/// @param f format string
/// @param ... arguments to the format string
/// @note Does nothing if lptr is NULL.
/// @note Does nothing if the log level of lptr is higher than lvl.
#define LOG(lptr, lvl, f...) logger_log(lptr, lvl, LOG_META SEP f)

/// @brief Behaves like LOG but always returns true.
/// @param lptr logger pointer
/// @param lvl log level
/// @param f format string
/// @param ... arguments to the format string
/// @return true
#define LOG_TRUE(lptr, lvl, f...) logger_log_true(lptr, lvl, LOG_META SEP f)

/// @brief Behaves like LOG but always returns false.
/// @param lptr logger pointer
/// @param lvl log level
/// @param f format string
/// @param ... arguments to the format string
/// @return false
#define LOG_FALSE(lptr, lvl, f...) logger_log_false(lptr, lvl, LOG_META SEP f)

/// @brief Behaves like LOG but always returns NULL.
/// @param lptr logger pointer
/// @param lvl log level
/// @param f format string
/// @param ... arguments to the format string
/// @return NULL
#define LOG_NULL(lptr, lvl, f...) logger_log_null(lptr, lvl, LOG_META SEP f)

typedef enum {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
    CRITICAL = 4,
} log_level_t;

typedef struct {
    log_level_t level;
    const char *str;
} log_level_str_t;

typedef struct {
    FILE *fs;
    FILE *os;
    log_level_t level;
} logger_t;

/// @brief Initializes the logger. This function must be called even if the
/// logger is disabled. If a path is specified, the file is created if it does
/// not exists. If a file with the same name already exists, it is overriden.
/// If nothing is specified, the logger is disabled.
/// @param l logger to setup.
/// @param path path to the log file, if NULL no log is written to a file.
/// @param clear_file wether to clear the file at `path` before logging.
/// @param os file stream to directly write to, if NULL, no stream is set.
/// Setting both `path` and `os` allows to log in a file and in an output
/// stream at the same time.
/// @return true if the logger was successfully setup, false otherwise.
bool logger_init(logger_t *l, const char *path,
    bool clear_file, FILE *os);

/// @brief Deinitializes the logger.
/// @param l logger to deinitialize
void logger_deinit(logger_t *l);

/// @brief Set the log level of a logger.
/// @param l logger to set the log level of
/// @param level log level
/// @return true if the operation was succesful, false otherwise
bool logger_set_level(logger_t *l, log_level_t lvl);

/// @brief Set the log level of a logger using a string representation.
/// @param logger logger to set the log level of
/// @param str string representation of the log level
/// @return true if the operation was succesful, false otherwise
bool logger_set_level_str(logger_t *logger, const char *str);

/// @brief Get the string representation of a log level.
/// @param level log level
/// @param buf buffer to store the string representation. Must be at least
/// LOG_LEVEL_SIZE bytes long.
/// @return true if the operation was succesful, false otherwise
bool get_log_level_str(log_level_t lvl, char *buf);

/// @brief Clears the file at `path` if it is longer than LOG_MAX_LINES.
/// @param path path to the log file, if invalid, the function is a no-op
void trim_log_file(const char *path);

/// @brief Writes a log message to the logger using printf-style formatting.
/// Use this function directtly if you want to write log messages without
/// metadata or have your own metadata format. Otherwise, prefer the LOG macro.
/// @param l the logger to write to
/// @param level log level
/// @param f format string
/// @param args arguments to the format string
/// @note Does nothing if lptr is NULL.
/// @note Does nothing if the log level of lptr is higher than lvl.
void logger_va_log(logger_t *l, log_level_t lvl, const char *f, va_list args);

/// @brief Writes a log message to the logger using printf-style formatting.
/// Use this function directtly if you want to write log messages without
/// metadata or have your own metadata format. Otherwise, prefer the LOG macro.
/// @param l the logger to write to
/// @param level log level
/// @param f format string
/// @param ... arguments to the format string
/// @note Does nothing if lptr is NULL.
/// @note Does nothing if the log level of lptr is higher than lvl.
void logger_log(logger_t *l, log_level_t lvl, const char *f, ...);

/// @brief Behaves like logger_log but always returns true.
/// @param l the logger to write to
/// @param level log level
/// @param f format string
/// @param ... arguments to the format string
/// @return true
bool logger_log_true(logger_t *l, log_level_t lvl, const char *f, ...);

/// @brief Behaves like logger_log but always returns false.
/// @param l the logger to write to
/// @param level log level
/// @param f format string
/// @param ... arguments to the format string
/// @return false
bool logger_log_false(logger_t *l, log_level_t lvl, const char *f, ...);

/// @brief Behaves like logger_log but always returns NULL.
/// @param l the logger to write to
/// @param level log level
/// @param f format string
/// @param ... arguments to the format string
/// @return NULL
void *logger_log_null(logger_t *l, log_level_t lvl, const char *f, ...);
