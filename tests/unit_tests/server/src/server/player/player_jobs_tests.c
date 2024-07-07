/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_jobs_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(player_schedule_job, simple_job)
{
    server_t server = {0};
    player_t player = {0};
    job_t *job = player.jobs;

    player_schedule_job(&server, &player, "Forward");
    cr_assert_str_eq(job->name, "Forward");
    cr_assert_eq(job->priority, MAX_JOBS - 1);
    cr_assert_not(job->started);
    cr_assert(job->enabled);
}
