/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** socknet++
*/

#include "socknet.hpp"

socknet::Net::Net(port p, const std::filesystem::path &logPath, bool useStdout)
{
    const char *path = logPath == "" ? nullptr : logPath.c_str();

    if (!net_init(&net, p, path, useStdout))
        throw NetError("Failed to initialize the network module");
}

socknet::Net::~Net()
{
    deinit();
}

void socknet::Net::deinit()
{
    net_deinit(&net);
}

socknet::status socknet::Net::update()
{
    return net_update(&net);
}

bool socknet::Net::isBusy() const
{
    return net_is_busy(&net);
}

bool socknet::Net::setLogLevel(logLevel level)
{
    return net_set_log_level(&net, level);
}

bool socknet::Net::willSend() const
{
    return net_has_to_send(&net);
}

bool socknet::Net::willRecv() const
{
    return net_has_to_recv(&net);
}

bool socknet::Net::hasIncoming() const
{
    return nets_has_incoming(&net);
}

bool socknet::Net::hasOutgoing() const
{
    return nets_has_outgoing(&net);
}

bool socknet::Net::host()
{
    return nets_host(&net);
}

bool socknet::Net::send(int sock, const std::string &data)
{
    return nets_send(&net, sock, data.c_str());
}

bool socknet::Net::recv(int &sockBuf, std::string &dataBuf)
{
    net_transfer_t transfer = {.sock = 0, .data = nullptr};

    if (!nets_recv(&net, &transfer))
        return false;
    sockBuf = transfer.sock;
    dataBuf = transfer.data;
    free(transfer.data);
    return true;
}

bool socknet::Net::acceptIncoming(int &sockBuf)
{
    return nets_accept_incoming(&net, &sockBuf);
}

bool socknet::Net::acceptOutgoing(int &sockBuf)
{
    return nets_accept_outgoing(&net, &sockBuf);
}

bool socknet::Net::kick(int sock)
{
    return nets_kick(&net, sock);
}

bool socknet::Net::connect(const std::string &host, port host_p)
{
    return netc_connect(&net, host.c_str(), host_p);
}

bool socknet::Net::send(const std::string &data)
{
    return netc_send(&net, data.c_str());
}

bool socknet::Net::recv(std::string &dataBuf)
{
    net_transfer_t transfer = {.sock = 0, .data = nullptr};

    if (!netc_recv(&net, &transfer))
        return false;
    dataBuf = transfer.data;
    free(transfer.data);
    return true;
}

bool socknet::Net::disconnect()
{
    return netc_disconnect(&net);
}

bool socknet::Net::isConnected() const
{
    return netc_is_connected(&net);
}

bool socknet::Net::canWriteFd(int fd, unsigned int timeoutMs)
{
    return net_can_write_fd(fd, timeoutMs);
}

bool socknet::Net::canReadFd(int fd, unsigned int timeoutMs)
{
    return net_can_read_fd(fd, timeoutMs);
}

bool socknet::Net::readFd(int fd, std::string &dataBuf)
{
    char *str = NULL;

    str = net_read_fd(fd);
    if (!str)
        return false;
    dataBuf = str;
    free(str); 
    return true;
}

socknet::port socknet::Net::getSockPort(int sock)
{
    return net_get_port(sock);
}
