#! /usr/bin/env python3
##
## EPITECH PROJECT, 2024
## zappy
## File description:
## main
##

from socket import *
from sys import argv as av
from args import *
from network import *
from behavior import *
from communications import *
from random import *
from math import sqrt
from multiprocessing import Process

def calc_food_required(ai, map_size):
    time_units = int(sqrt(map_size)) + 1
    time_units += 3
    time_units = time_units * 7
    food_required = int(time_units / 126)
    food_required += 17
    ai.set_food_required(food_required)
    return ai

def can_connect(net, team_name, ai):
    net.get_cmd()
    if net.data_got[0] != "WELCOME\n":
        return (False, ai)
    net.data_to_send.append(team_name)
    net.send_data()
    msg = net.s.recv(2048).decode()
    msg = msg.strip("\n")
    args = msg.split(' ')
    first_arg = args[0].split("\n")
    map_size_x = int(first_arg[1])
    map_size_y = int(args[1])
    map_size = map_size_x * map_size_y
    return (True, calc_food_required(ai, map_size))

def main_loop(net, ai, team_name):
    (res, ai) = can_connect(net, team_name, ai)
    if res == False:
        print("Unable to connect to server: not enough slots left")
        return
    response = ai.action()
    net.data_to_send.append(response)
    if net.data_to_send != []:
            net.send_data()
    while 1:
        net.update()


def create_classes(s, team_name, debug, zombie_mode, parsed_args):
    from behavior import behavior
    from network import network
    ai = behavior(team_name)
    id = randint(1, 1000000)
    com = communications(ai, id)
    net = network(s, ai)
    ai.add_net(net)
    ai.add_communications(com)
    ai.debug = debug
    ai.zombie_mode = zombie_mode
    ai.parsed_args = parsed_args
    return (net, ai)

def create_ai(parsed_args):
    if parsed_args[0] == 0 or parsed_args[1] == "" or parsed_args[2] == "":
        print("ERROR: Wrongs args, try './zappy_ai -help'")
        return 84

    s_adress = (parsed_args[2], parsed_args[0])
    s = socket(AF_INET, SOCK_STREAM)
    try:
        s.connect(s_adress)
    except:
        print("ERROR: Unable to connect to server")
        return 84
    (net, ai) = create_classes(s, parsed_args[1], parsed_args[3], parsed_args[4], parsed_args)
    main_loop(net, ai, parsed_args[1])
    s.close()

def main():
    args = [i for i in av]
    res = check_args(args)
    processes = []

    if (res != 1):
        return res

    parsed_args = get_args(args)
    client_nb = parsed_args[5]
    for _ in range(int(client_nb)):
        p = Process(target=create_ai, args=(parsed_args,))
        processes.append(p)
        p.start()
    for p in processes:
        p.join()
    return 0

if __name__ == '__main__':
    exit(main())
