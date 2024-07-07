##
## EPITECH PROJECT, 2024
## zappy
## File description:
## communications
##

from network import *
from behavior import *
from random import *

class communications:
    def __init__(self, ai, id):
        self.ai = ai
        self.id = str(id)

    def get_last_msg(self):
        message = self.ai.net.last_msg[0]
        if message:
            message = message.strip("\n")
            args = message.split(' ')
            return args
        return ""

    def check_arrived_players(self):
        nb = 0

        msg_list = self.ai.net.last_msg
        for msg in msg_list:
            msg = msg.strip("\n")
            msg = msg.split(' ')
            args = msg[2].split('-')
            if args[0] == "answer":
                if args[1] == self.id and args[3] == "arrived":
                    nb += 1
        return nb

    def wait_players(self, players_list, required_players):
        arrived_players = required_players
        while arrived_players > 0:
            self.ai.broadcast("info-" + self.id + "-waiting" + players_list)
            self.ai.turn_right()
            arrived_players -= self.check_arrived_players()
            self.ai.net.last_msg = []
        self.ai.net.last_msg = []
        return True

    def is_answer_ok(self):
        msg = self.get_last_msg()
        args = msg[2].split('-')
        if args[0] == "answer":
            if args[1] == self.id and args[3] == "ok":
                return True
        return False

    def check_answers(self, players_remaining, current_list):
        players_list = current_list
        players_required = players_remaining

        msg_list = self.ai.net.last_msg
        for msg in msg_list:
            if (players_required < 1):
                return (players_required, players_list)
            msg = msg.strip("\n")
            msg = msg.split(' ')
            args = msg[2].split('-')
            if args[0] == "answer":
                if args[1] == self.id and args[3] == "ok":
                    players_list = players_list + "-" + args[2]
                    players_required -= 1
        return (players_required, players_list)

    def call_players(self, lv, nb):
        required_players = nb
        players_list = ""
        time_to_wait = self.ai.elevation_level * 3

        self.ai.broadcast("help-" + self.id + "-" + str(lv) + "-" + str(required_players) + "-need_players")
        self.ai.net.last_msg = []
        for i in range (randint(time_to_wait, time_to_wait + 25)):
            self.ai.turn_right()
        (required_players, players_list) = self.check_answers(required_players, players_list)
        self.ai.net.last_msg = []
        if required_players <= 0:
            return self.wait_players(players_list, nb)
        self.ai.broadcast("info-" + self.id + "-cancelled")
        return False

    def get_direction(self, player_id):
        direction = 0

        self.ai.net.last_msg = []
        self.ai.net.get_msg()
        msg = self.get_last_msg()
        args = msg[2].split('-')
        if (args[0] != "info" or args[1] != player_id):
            return self.get_direction(player_id)
        direction = msg[1].strip(",")
        direction = int(direction)
        self.ai.net.last_msg = []
        return direction

    def move_toward_player(self, player_id):
        direction = self.get_direction(player_id)

        self.ai.net.get_msg()
        if direction > 3 and direction < 7:
            self.ai.turn_right()
            self.ai.turn_right()
        while direction != 3 and direction != 7 and direction != -1:
            self.ai.move_forward()
            direction = self.get_direction(player_id)
        if direction == 3:
            self.ai.turn_left()
        if direction == 7:
            self.ai.turn_right()
        while direction > 0:
            self.ai.move_forward()
            direction = self.get_direction(player_id)

    def follow_sound(self, player_id):
        self.move_toward_player(player_id)
        self.ai.broadcast("answer-" + player_id + "-" + self.id + "-arrived")
        self.ai.net.get_cmd()
        if self.ai.net.data_got[0] == "Elevation underway\n":
            self.ai.net.get_cmd()
            if self.ai.net.data_got[0] == ("Current level: " + str((self.ai.elevation_level + 1)) + "\n"):
                self.ai.elevation_level += 1
                self.ai.forking()
                self.ai.net.last_msg = []

    def is_accepted(self, args):
        i = 3

        if (args[2] == "cancelled"):
            return False
        for i in range (len(args)):
            if args[i] and args[i] == self.id:
                return True
        return False

    def have_enough_players(self, player_id):
        while 1:
            self.ai.net.get_msg()
            msg = self.get_last_msg()
            args = msg[2].split('-')
            if (args[0] == "info"):
                if (args[1] == player_id):
                    return self.is_accepted(args)
            self.ai.net.last_msg = []

    def meet_requirements(self, msg):
        msg = msg.strip("\n")
        msg = msg.split(' ')
        args = msg[2].split('-')
        if args[0] == "info" and args[2] == "cancelled":
            return True
        if args[0] != "help":
            return False
        if int(args[2]) == self.ai.elevation_level and args[4] == "need_players":
            self.ai.broadcast("answer-" + args[1] + "-" + self.id + "-ok")
            player_id = args[1]
            self.ai.net.last_msg = []
            if self.have_enough_players(player_id):
                self.follow_sound(player_id)
                return True
        return False

    def check_msg_list(self):
        if not self.ai.net.last_msg:
            return False
        for msg in self.ai.net.last_msg:
            if self.meet_requirements(msg):
                self.ai.net.last_msg = []
                return True
        self.ai.net.last_msg = []
        return False
