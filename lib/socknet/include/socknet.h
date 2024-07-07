/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** socknet
*/

#pragma once
#include <netinet/in.h>
#include "linked.h"
#include "clogger.h"

#define QUEUE_SIZE 10
#define SELECT_TIMEOUT_MS 100
#define CLIENT_RESPONSE_TIMEOUT 10000
#define SERVER_RESPONSE_TIMEOUT 30000
#define MAX_PACKET_SIZE 1024

typedef unsigned int port_t;

/// @brief Type of a network module
typedef enum {
    NET_NO_TYPE,
    NET_SERVER,
    NET_CLIENT
} net_type_t;

typedef enum {
    NET_OK,
    NET_ERROR,
    NET_DISCONNECT
} net_status_t;

//////////////////////////////////////////////////////////////// Main Module //

/// @brief Server component of a network module
/// @param incoming list of `net_connection_t` for incoming connections
/// @param outgoing list of `net_connection_t` for outgoing connections
/// @param clients list of `net_connection_t` for connected clients
typedef struct {
    list_t incoming;
    list_t outgoing;
    list_t clients;
} net_server_t;

/// @brief Client component of a network module
/// @param is_connected boolean used internally to know if the client is
/// connected
typedef struct {
    bool is_connected;
} net_client_t;

/// @brief Main network module
/// @param sock socket of the network module
/// @param type type of the network module
/// @param to_send list of `net_transfer_t` containing packets to send
/// @param to_recv list of `net_transfer_t` containing packets recieved
/// @param logger internal logging module
/// @param server server component of the network module
/// @param client client component of the network module
typedef struct {
    int sock;
    port_t port;
    net_type_t type;
    list_t to_send; // transfer_t
    list_t to_recv; // transfer_t
    logger_t logger;
    union {
        net_server_t server;
        net_client_t client;
    };
} net_t;

//////////////////////////////////////////////////////////////////// Packets //

/// @brief Data structure representing a transfer of a packet
/// @param sock socket to be sent or recieved from
/// @param data data to be sent or recieved
typedef struct {
    int sock;
    char *data;
} net_transfer_t;

///////////////////////////////////////////////////////////////////// Common //

/// @brief Initializes a network module of any type.
/// @param net the network module
/// @param port the port to listen on, 0 to let the kernel choose
/// @param log_path the path to the log file, NULL to disable logging
/// @param use_stdout true to log to stdout, false otherwise
/// @return true if the initialization was successful, false otherwise
/// @note this function must be called before any other function of the library
bool net_init(net_t *net, port_t port, const char *log_path, bool use_stdout);

/// @brief Deinitializes a network module of any type.
/// @param net the network module
void net_deinit(net_t *net);

/// @brief Updates a network module. This function must be called in a loop to
/// keep the network module up to date. This is the main function of the
/// library. It performs all internal operations like sending queued packets
/// that can be sent, reading packets that can be read, and for servers,
/// accepting (using the `accept` function) new connections and disconnecting
/// clients with broken pipes.
/// @param net the network module
/// @return the status of the network module
net_status_t net_update(net_t *net);

/// @brief Checks if a network module has packets to send of to revieve
/// @param net the network module
/// @return true if the network module has packets to send or to recieve,
/// false otherwise
bool net_is_busy(const net_t *net);

/// @brief Sets the log level of the network module
/// @param net the network module to set the log level of
/// @param lvl the log level to set
/// @return true if the log level was set, false otherwise
bool net_set_log_level(net_t *net, log_level_t lvl);

/// @brief Checks if a file descriptor is ready to be written to
/// @param fd the file descriptor to check
/// @param timeout_ms the timeout in milliseconds
/// @return true if the file descriptor is ready to be written to, false
/// otherwise
bool net_can_write_fd(int fd, unsigned int timeout_ms);

/// @brief Checks if a file descriptor is ready to be read from
/// @param fd the file descriptor to check
/// @param timeout_ms the timeout in milliseconds
/// @return true if the file descriptor is ready to be read from, false
/// otherwise
bool net_can_read_fd(int fd, unsigned int timeout_ms);

/// @brief Reads a file descriptor and returns the data read
/// @param fd the file descriptor to read from
/// @return the data read from the file descriptor, NULL if an error occured
/// @note the caller gains ownership of the returned data and must free it
char *net_read_fd(int fd);

/// @brief Gets the port of a socket
/// @param sock the socket to get the port of
/// @return the port of the socket, 0 if an error occured
port_t net_get_port(int sock);

/// @brief Gets the ip of a socket
/// @param net the network module
/// @return the ip of the socket, NULL if an error occured
bool net_has_to_send(const net_t *net);

/// @brief Checks if a network module has packets to recieve
/// @param net the network module
/// @return true if the network module has packets to recieve, false otherwise
bool net_has_to_recv(const net_t *net);

/// @brief Checks if a network module is a server
/// @param net the network module
/// @return true if the network module is a server, false otherwise
bool nets_has_incoming(const net_t *net);

/// @brief Checks if a network module is a server
/// @param net the network module
/// @return true if the network module is a server, false otherwise
bool nets_has_outgoing(const net_t *net);

////////////////////////////////////////////////////////////// Server (nets) //

/// @brief Initializes a network module as a server
/// @param net the server module to initialize
/// @return true if the initialization was successful, false otherwise
bool nets_host(net_t *net);

/// @brief Queues a packet to be sent. `data` is copied to an internal list.
/// @param net the server module
/// @param sock the socket to send the packet to
/// @param data the data to send
/// @return true if the packet was queued, false otherwise
bool nets_send(net_t *net, int sock, const char *data);

/// @brief Dequeues a packet from the recieved packets.
/// The caller gains ownership of all allocated memory contained in `t_buf`
/// @param net the server module
/// @param t_buf the transfer buffer to store the transfer info
/// @return true if a packet was recieved, false otherwise
bool nets_recv(net_t *net, net_transfer_t *t_buf);

/// @brief "Accepts" incoming connections. This does not call the
/// `accept` syscall. It moves already accepted connections from the internal
/// incoming list to the connected clients list. One example use of this
/// function is sending a welcome message when a user connects. Note that
/// even if you do not plan to have such behaviour in your program, the
/// function must be called either way.
/// @param net the server module
/// @param sock_buf the socket buffer to store the socket of the incoming
/// @return true if an incoming connection was accepted, false otherwise
bool nets_accept_incoming(net_t *net, int *sock_buf);

/// @brief "Accepts" outgoing connections. Outgoing connection are clients that
/// have been disconnected and are now ready to be removed from the outgoing
/// list.
/// @param net the server module
/// @param c_buf the connection buffer to store the connection info
/// @return true if an outgoing connection was accepted, false otherwise
bool nets_accept_outgoing(net_t *net, int *sock_buf);

/// @brief Kicks a client from the server. This moves the client from the
/// connected clients list to the outgoing list.
/// @param net the server module
/// @param sock the socket of the client to kick
/// @return true if the client was kicked, false otherwise
bool nets_kick(net_t *net, int sock);

/// @brief Checks if a given file socket descriptor is connected to the
/// server module
/// @param net the server module
/// @param sock the socket to check
/// @return true if the socket is connected, false otherwise
bool nets_sock_is_client(net_t *net, int sock);

////////////////////////////////////////////////////////////// Client (netc) //

/// @brief Initializes A client module and connects it to as server
/// @param net the client module
/// @param host string representation of an ipv4 host address
/// (i.e. 127.0.0.1)
/// @param port port to open the connection to (i.e. server's port)
/// @return true if the connection was successful, false otherwise
bool netc_connect(net_t *net, const char *host, port_t port);

/// @brief Queues a packet to be sent to the server.
/// `data` is copied to an internal list.
/// @param net the client module
/// @param data the data to send
/// @return true if the packet was sent, false otherwise
bool netc_send(net_t *net, const char *data);

/// @brief Dequeues a packet from the recieved packets.
/// The caller gains ownership of all allocated memory contained in `t_buf`
/// @param net the client module
/// @param t_buf the transfer buffer to store the transfer info
/// @return true if a packet was recieved, false otherwise
bool netc_recv(net_t *net, net_transfer_t *t_buf);

/// @brief Disconnects a client from a server
/// @param net the client module
/// @return true if the disconnection was successful, false otherwise
bool netc_disconnect(net_t *net);

/// @brief Checks if a client is connected to a server
/// @param net the client module
/// @return true if the client is connected, false otherwise
bool netc_is_connected(const net_t *net);
