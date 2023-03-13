#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <errno.h>
#include "../utils/bool.h"
#include "../utils/color.h"
#include "logs.h"

/**
 * @brief Log a message with the INFO level
 * 
 * @param message The message to log
 */
void log_info(const char *message)
{
    fprintf(
        stdout,
        "%s%s INFO %s %s\n",
        B_BLUE,
        BOLD,
        RESET,
        message);
}

/**
 * @brief Log a message with the WARN level
 * 
 * @param message The message to log
 */
void log_warn(const char *message)
{
    fprintf(
        stderr,
        "%s%s WARN %s %s\n",
        B_YELLOW,
        BOLD,
        RESET,
        message);
}

/**
 * @brief Log a message with the ERROR level
 * 
 * @param message The message to log
 */
void log_error(const char *message)
{
    fprintf(
        stderr,
        "%s%s ERROR %s %s\n",
        B_RED,
        BOLD,
        RESET,
        message);
}

/**
 * @brief Log a message with the FATAL level
 * 
 * @param message The message to log
 * @param show_errno If true, the error message will be appended to the log
 */
void log_fatal(const char *message, bool_t show_errno)
{
    fprintf(
        stderr,
        "\n%s%s FATAL %s %s",
        B_RED,
        BOLD,
        RESET,
        message);
    if (show_errno)
        fprintf(stderr, ": %s", strerror(errno));
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

/**
 * @brief  Log a message with the SUCCESS level
 * 
 * @param message The message to log
 */
void log_success(const char *message)
{
    fprintf(
        stdout,
        "%s%s SUCCESS %s %s\n",
        B_GREEN,
        BOLD,
        RESET,
        message);
}

/**
 * @brief Log a task
 * 
 * @param message The message to log
 * @param task_end The task end status
 */
void log_task(const char *message, t_task_end task_end)
{
    fprintf(
        stdout,
        "%s%s TASK %s %s ",
        B_CYAN,
        BOLD,
        RESET,
        message);

    switch (task_end)
    {
    case TASK_END_SUCCESS:
        fprintf(
            stdout,
            "%s%s ✓ %s\n",
            B_GREEN,
            BOLD,
            RESET);
        break;
    case TASK_END_CRASH:
        fprintf(
            stdout,
            "%s%s CRASH %s\n",
            B_RED,
            BOLD,
            RESET);
        break;
    }
}