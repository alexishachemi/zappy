/*
** EPITECH PROJECT, 2024
** socknet++
** File description:
** Main header
*/

#pragma once

extern "C" {
    #include "socknet.h"
};

#include <filesystem>
#include <iostream>

namespace socknet
{
    using port = port_t;
    using status = net_status_t;
    using logLevel = log_level_t;

    class Net
    {
        net_t net;

        public:
            Net(port p, const std::filesystem::path &logPath = "", bool useStdout = false);
            ~Net();

            void deinit();
            status update();
            bool isBusy() const;
            bool setLogLevel(logLevel level);
            bool willSend() const;
            bool willRecv() const;
            bool hasIncoming() const;
            bool hasOutgoing() const;

            bool host();
            bool send(int sock, const std::string &data);
            bool recv(int &sockBuf, std::string &dataBuf);
            bool acceptIncoming(int &sockBuf);
            bool acceptOutgoing(int &sockBuf);
            bool kick(int sock);

            bool connect(const std::string &host, port host_p);
            bool send(const std::string &data);
            bool recv(std::string &dataBuf);
            bool disconnect();
            bool isConnected() const;

            static bool canWriteFd(int fd, unsigned int timeoutMs);
            static bool canReadFd(int fd, unsigned int timeoutMs);
            static bool readFd(int fd, std::string &dataBuf);
            static port getSockPort(int sock);

            class NetError: public std::runtime_error
            {
                public:
                    NetError(const std::string &msg): std::runtime_error(msg) {}
            };
    };
}
