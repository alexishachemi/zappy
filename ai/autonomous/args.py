#! /usr/bin/env python3
##
## EPITECH PROJECT, 2024
## zappy
## File description:
## args
##

def check_args(args):
    if len(args) == 2 and args[1] == "-help":
        print("USAGE: ./zappy_ai -p port -n team_name -h machine [-d] [-z] [-c client_nb]")
        return 0
    if len(args) < 7 or len(args) > 9:
        print("ERROR: Wrongs args, try './zappy_ai -help'")
        return 84
    return 1

def get_args(args):
    i = 0
    debug = False
    zombie_mode = False
    client_nb = 1
    try:
        for i in range (len(args)):
            if (args[i] == "-p"):
                port = int(args[i + 1])
            if (args[i] == "-n"):
                team_name = args[i + 1]
            if (args[i] == "-h"):
                machine = args[i + 1]
            if (args[i] == "-d"):
                debug = True
            if (args[i] == "-z"):
                zombie_mode = True
            if (args[i] == "-c"):
                client_nb = args[i + 1]
        return (port, team_name, machine, debug, zombie_mode, client_nb)
    except:
        return (0, "", "", False, False, 1)
