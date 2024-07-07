/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_jobs
*/

#include <string.h>
#include "server.h"

static bool check_job(server_t *server, player_t *player, job_t *job)
{
    if (job->jdata.check)
        return job->jdata.check(server, player,
            job->jdata.arg, job->jdata.data);
    return true;
}

static bool start_job(server_t *server, player_t *player, job_t *job)
{
    job->started = true;
    if (job->jdata.check_first && !check_job(server, player, job)
        && job->jdata.failure) {
        job->jdata.failure(server, player, job->jdata.arg, job->jdata.data);
        return false;
    }
    if (job->jdata.start)
        job->jdata.start(server, player, job->jdata.arg, job->jdata.data);
    return true;
}

static void clear_job(job_t *job)
{
    memset(job, 0, sizeof(job_t));
}

static void end_job(server_t *server, player_t *player, job_t *job)
{
    if (check_job(server, player, job) && job->jdata.sucess)
        job->jdata.sucess(server, player, job->jdata.arg, job->jdata.data);
    else if (job->jdata.failure)
        job->jdata.failure(server, player, job->jdata.arg, job->jdata.data);
    if (job->jdata.arg)
        free(job->jdata.arg);
    clear_job(job);
    for (int i = 0; i < MAX_JOBS; i++) {
        if (player->jobs[i].enabled)
            player->jobs[i].priority++;
    }
}

static void update_job(server_t *server, player_t *player, job_t *job)
{
    if (job->enabled && !job->started)
        job->enabled = start_job(server, player, job);
    if (!job->enabled)
        return;
    job->f = job->f > 0 ? job->f - 1 : 0;
    if (job->f == 0)
        end_job(server, player, job);
}

void player_update_jobs(server_t *server, player_t *player)
{
    job_t *current_job = NULL;
    job_t *to_update = NULL;

    if (!server || !player || player->elevation_status == ELEV_MEMB)
        return;
    for (int i = 0; i < MAX_JOBS; i++) {
        current_job = player->jobs + i;
        if (!current_job->enabled)
            continue;
        if (!to_update || current_job->priority > to_update->priority)
            to_update = current_job;
    }
    if (to_update)
        update_job(server, player, to_update);
}

static int get_biggest_priority(job_t *jobs, job_t *current_job)
{
    int lowest = MAX_JOBS - 1;

    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs + i != current_job
            && jobs[i].enabled && jobs[i].priority <= lowest) {
            lowest = jobs[i].priority - 1;
        }
    }
    return lowest;
}

static bool get_free_job(player_t *player, job_t **job)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (!player->jobs[i].enabled) {
            *job = player->jobs + i;
            clear_job(*job);
            return true;
        }
    }
    return false;
}

void player_schedule_job(server_t *server, player_t *player, const char *msg)
{
    job_t *job = NULL;

    if (!get_free_job(player, &job))
        return;
    job->enabled = job_build(server, player, msg, job);
    job->priority = get_biggest_priority(player->jobs, job);
    if (job->enabled)
        return;
    nets_send(&server->net, player->sock, "ko");
    clear_job(job);
}
