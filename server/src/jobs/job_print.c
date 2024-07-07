/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** job_print
*/

#include <ncurses.h>
#include "job.h"

static job_t *get_job_by_priority(job_t *jobs, int priority)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs[i].enabled && jobs[i].priority == priority)
            return jobs + i;
    }
    return NULL;
}

bool job_print_array(job_t *jobs)
{
    job_t *job = NULL;
    bool printed = false;

    for (int i = MAX_JOBS - 1; i >= 0; i--) {
        job = get_job_by_priority(jobs, i);
        if (!job)
            break;
        if (i == MAX_JOBS - 1) {
            printw("JOBS: ");
            printed = true;
        } else {
            printw(" <- ");
        }
        printw("%s %d", job->name, job->f);
    }
    if (printed)
        printw("\n");
    return printed;
}
