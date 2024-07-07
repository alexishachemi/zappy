/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** library utils functions
*/

#pragma once

#include <sys/select.h>
#include "socknet.h"

#define NPRE "[NETWORK] "
#define NLOG(netptr, lvl, f...) (LOG(&netptr->logger, lvl, NPRE f))
#define FALSE_NLOG(netptr, lvl, f...) (LOG_FALSE(&netptr->logger, lvl, NPRE f))
#define TRUE_NLOG(netptr, lvl, f...) (LOG_TRUE(&netptr->logger, lvl, NPRE f))
#define NULL_NLOG(netptr, lvl, f...) (LOG_NULL(&netptr->logger, lvl, NPRE f))

#define NRESP ((net_header_t){.type = NET_RESPONSE, .data_size = 0})
#define DATA_CHUNK 1024

// transfer handling

bool net_send_packet(net_t *net, const net_transfer_t *transfer);
bool net_recv_packet(net_t *net, int sock);
bool net_fetch_packets(net_t *net);
bool net_send_queued(net_t *net);

// client handling

void nets_clear_sock_transfer(net_t *net, int sock);
bool nets_fetch_clients(net_t *net);

// socket utils

int net_open_socket(port_t port);

// memory management

void *alloc_sock(void);
void *alloc_transfer(void);

void free_transfer(void *t);
void free_sock(void *c);
