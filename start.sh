#!/bin/bash
##
## EPITECH PROJECT, 2024
## zappy
## File description:
## start script
##

make -s
./zappy_server -x 10 -y 10 -c 6 -n team -p $1 &
sleep 1
./zappy_gui -p $1 -g raylib &
sleep 2
./zappy_ai_hm -p $1 -n team -m 5 &
