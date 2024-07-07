/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <atomic>
#include <signal.h>
#include "arg.hpp"
#include "Gui.hpp"

std::atomic<bool> running(true);
static const char *helpMsg =
"USAGE:\t./zappy_gui [-h host] -p port\n"
"OPTIONS:\n"
"\t-h host\t  host adress (default: 127.0.0.1)\n"
"\t-p port\t  port of the server\n"
"\t-g name\t  graphical environment (available: sfml, raylib. default: sfml)";

void sigHandler(int sig)
{
    static int sigCount = 0;
    (void)sig;
    running = false;
    if (sigCount++ > 0)
        exit(0);
}

void printHelp(void)
{
    std::cerr << helpMsg << std::endl;
}

int startGui(const std::string &host, socknet::port port, const std::string &graphicsName)
{
    gui::Gui g(host, port);

    g.setGraphics(graphicsName);
    while (g.update() && running);
    return 0;
}

int main(int ac, const char **av)
{
    arg::Parser argParser(ac, av);
    std::string host = "127.0.0.1";
    std::string graphicsName = "sfml";
    int port = -1;

    signal(SIGINT, sigHandler);
    if (argParser.has("help")) {
        printHelp();
        return 0;
    }
    if (argParser.has("h"))
        host = (std::string)argParser["h"];
    if (argParser.has("p"))
        port = (int)argParser["p"];
    if (argParser.has("g"))
        graphicsName = (std::string)argParser["g"];
    if (port < 0) {
        std::cerr << "Missing/Bad host port (-p). Must be positive integer" << std::endl;
        return 84;
    }
    return startGui(host, port, graphicsName);
}
