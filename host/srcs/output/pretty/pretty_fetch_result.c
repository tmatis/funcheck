/* Funcheck - A tool for checking functions calls return protections
 * Copyright (C) 2023  Theo Matis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "../../logs/logs.h"
#include "../../utils/color.h"
#include "../../config/config.h"
#include "../utils/output_utils.h"
#include "../output.h"
#include "pretty_output.h"

/**
 * @brief Write the fail fetch result in pretty format
 * 
 * @param t_fetch_result_display the fetch result to write
 */
static void write_fetch_result_fail(t_fetch_result_display *fetch_result_display)
{
    fprintf(stdout, "\n");
    fprintf(
        stdout,
        "┏%s %s%s %s\n",
        B_RED,
        BOLD,
        fetch_result_display->crash_name,
        RESET);
    backtrace_print_pretty(fetch_result_display->backtrace);
    printf("\nNo test ran because of a crash in functions fetching\n");
}

/**
 * @brief Write the success fetch result in pretty format
 * 
 * @param fetch_result_display the fetch result to write
 */
static void write_fetch_result_success(t_fetch_result_display *fetch_result_display)
{
    char buffer[1024];

    snprintf(
        buffer,
        sizeof(buffer),
        "Functions detected count: %s%zi%s",
        BOLD,
        count_testable_functions(fetch_result_display->function_tree),
        RESET);
    log_info(buffer);
    if (is_option_set(TRACK_ALLOCATIONS_MASK, get_config()))
        write_allocation_track_pretty(
            fetch_result_display->function_tree,
            NULL,
            NULL);
    fprintf(stdout, "\n");
}

/**
 * @brief Write the fetch result in pretty format
 * 
 * @param fetch_result_display the fetch result to write
 */
void write_function_fetch_result_pretty(
    t_fetch_result_display *fetch_result_display)
{
    t_task_end task_end = fetch_result_display->crash_name
                              ? TASK_END_CRASH
                              : TASK_END_SUCCESS;
    write_delim_bar();
    log_task("Testable functions fetching", task_end);

    if (fetch_result_display->crash_name)
        write_fetch_result_fail(fetch_result_display);
    else
        write_fetch_result_success(fetch_result_display);
}