/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** job_command_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(job_build, good_cmd_no_args)
{
    server_t server = {0};
    player_t player = {0};
    job_t job = {0};

    cr_assert(job_build(&server, &player, "Forward", &job));
    cr_assert_str_eq(job.name, "Forward");
    cr_assert_null(job.jdata.arg);
    cr_assert_eq(job.f, 7);
    cr_assert_eq(job.jdata.check_first, false);
    cr_assert_eq(job.jdata.check, NULL);
    cr_assert_eq(job.jdata.start, NULL);
    cr_assert_neq(job.jdata.sucess, NULL);
    cr_assert_eq(job.jdata.failure, NULL);
    cr_assert_not(job.started);
}

Test(job_build, good_cmd_with_args)
{
    server_t server = {0};
    player_t player = {0};
    job_t job = {0};

    cr_assert(job_build(&server, &player, "Broadcast hello!", &job));
    cr_assert_str_eq(job.name, "Broadcast");
    cr_assert_str_eq(job.jdata.arg, "hello!");
    cr_assert_eq(job.f, 7);
    cr_assert_eq(job.jdata.check_first, false);
    cr_assert_eq(job.jdata.check, NULL);
    cr_assert_eq(job.jdata.start, NULL);
    cr_assert_neq(job.jdata.sucess, NULL);
    cr_assert_eq(job.jdata.failure, NULL);
    cr_assert_not(job.started);
    free(job.jdata.arg);
}

Test(job_build, bad_cmd)
{
    server_t server = {0};
    player_t player = {0};
    job_t job = {0};

    cr_assert_not(job_build(&server, &player, "badcmd", &job));
    cr_assert_null(job.jdata.arg);
    cr_assert_eq(job.f, 0);
    cr_assert_eq(job.jdata.check_first, false);
    cr_assert_eq(job.jdata.check, NULL);
    cr_assert_eq(job.jdata.start, NULL);
    cr_assert_eq(job.jdata.sucess, NULL);
    cr_assert_eq(job.jdata.failure, NULL);
    cr_assert_not(job.started);
}

Test(job_build, bad_cmd_no_args)
{
    server_t server = {0};
    player_t player = {0};
    job_t job = {0};

    cr_assert_not(job_build(&server, &player, "Broadcast", &job));
    cr_assert_null(job.jdata.arg);
}
