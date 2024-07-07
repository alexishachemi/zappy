##
## EPITECH PROJECT, 2024
## zappy
## File description:
## network
##

from socket import *
from select import *
from behavior import *
from sys import *
from time import *

class network:

    def __init__(self, s, ai):
        self.data_to_send = []
        self.data_got = []
        self.s = s
        self.behavior = ai
        self.last_msg = []

    def send_data(self):
        print("AI: " + self.data_to_send[0])
        self.data_to_send[0] += "\n"
        self.s.send(self.data_to_send[0].encode("utf-8"))
        self.data_to_send.pop(0)

    def fix_cmd_not_found(self, response, type):
        if response.count('\n') > 1:
            cmd = 0
            args = response.split("\n")
            args = args[:-1]
            for arg in args:
                arg_type = arg.split(" ")[0]
                if arg_type == "message":
                    self.last_msg.append(arg)
                else:
                    self.msg_got = []
                    self.msg_got.append(arg + "\n")
                    cmd += 1
                    if arg == "dead":
                        self.s.close()
                        exit()
            if cmd == 0 and type == 1:
                self.get_cmd()
            return True
        return False

    def get_cmd(self):
        response = self.s.recv(2048).decode()
        if not response:
            print("Connection closed\n")
            exit()
        else:
            print("SERVER: " + response.rstrip("\n"))
            if response.find(' '):
                args = response.split(' ')
                if args and args[0] and args[0] == "message":
                    args[2] = args[2].rstrip("\n")
                    if self.fix_cmd_not_found(response, 1):
                        return
                    self.last_msg.append(response)
                    self.get_cmd()
                    return
            if self.fix_cmd_not_found(response, 1):
                return
            self.data_got = []
            self.data_got.append(response)
            if response == "dead\n":
                self.s.close()
                exit()

    def get_msg(self):
        response = self.s.recv(2048).decode()
        if not response:
            print("Connection closed\n")
            exit()
        else:
            print("SERVER: " + response.rstrip("\n"))
            if response.find(' '):
                args = response.split(' ')
                if args and args[0] and args[0] == "message":
                    if self.fix_cmd_not_found(response, 2):
                        return
                    self.last_msg.append(response)
                    return
            if self.fix_cmd_not_found(response, 1):
                return
            self.data_got = []
            self.data_got.append(response)
            if response == "dead\n":
                self.s.close()
            self.get_msg()

    def can_read(self):
        s_list = [self.s]
        r_data, w_data, ex = select(s_list, [], s_list)
        if r_data[0] == self.s:
            return True
        return False

    def update(self):
        if  self.can_read():
            self.get_cmd()
        print(self.behavior.zombify == True)
        if (self.behavior.zombify == True and self.behavior.zombie_mode == True):
            message = self.behavior.zombie_action()
        else:
            message = self.behavior.action()
        self.data_to_send.append(message)
        if self.data_to_send != []:
            self.send_data()
