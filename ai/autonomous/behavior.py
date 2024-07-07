##
## EPITECH PROJECT, 2024
## zappy
## File description:
## behavior
##

from random import *
from communications import *
from zappy_ai import *
from multiprocessing import Process
import os
import signal

nb_fork = 0

def reap_child_zombies(signum, frame):
    while True:
        try:
            pid, status = os.waitpid(-1, os.WNOHANG)
            if pid == 0:
                break
        except ChildProcessError:
            break

class behavior:

    def __init__(self, team_name):
        self.net = None
        self.communications = None
        self.team_name = team_name
        self.elevation_level = 1
        self.food = 0
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0
        self.debug = False
        self.zombie_mode = False
        self.zombify = False
        self.food_required = 0
        self.map_size = 0 
        self.parsed_args = (0, "", "", False, False)

    def add_net(self, net):
        self.net = net

    def add_communications(self, communications):
        self.communications = communications

    def set_food_required(self, food_required):
        self.food_required = food_required

    def broadcast(self, message):
        self.net.data_to_send.append("Broadcast " + message)
        self.net.send_data()
        self.net.get_cmd()

    def forking(self):
        self.net.data_to_send.append("Fork")
        self.net.send_data()
        self.net.get_cmd()
        if self.debug == True :
            self.new_instance()

    def new_instance(self):
        pid = os.fork()

        if pid == 0:
            from zappy_ai import create_ai
            create_ai(self.parsed_args)
            os._exit(0)
        else:
            signal.signal(signal.SIGCHLD, reap_child_zombies)

    def forking(self):
        self.net.data_to_send.append("Fork")
        self.net.send_data()
        self.net.get_cmd()
        if self.debug == True and nb_fork < 12 :
            self.new_instance()
            nb_fork += 1

    def set_item(self, item):
        self.net.data_to_send.append("Set " + item)
        self.net.send_data()
        self.net.get_cmd()

    def drop_items(self, linemate, deraumere, sibur, mendiane, phiras, thystame):
        for i in range (linemate):
            self.set_item("linemate")
        for i in range (deraumere):
            self.set_item("deraumere")
        for i in range (sibur):
            self.set_item("sibur")
        for i in range (mendiane):
            self.set_item("mendiane")
        for i in range (phiras):
            self.set_item("phiras")
        for i in range (thystame):
            self.set_item("thystame")

    def become_zombie(self):
        prob = randint(1, 5)
        if prob == 1:
            self.zombify = True

    def start_evolution(self):
        self.net.data_to_send.append("Incantation")
        self.net.send_data()
        self.net.get_cmd()
        if self.net.data_got[0] == "Elevation underway\n":
            self.net.get_cmd()
            if self.net.data_got[0] == ("Current level: " + str((self.elevation_level + 1)) + "\n"):
                self.elevation_level += 1
                if self.zombie_mode:
                    self.become_zombie()
                self.forking()
                self.net.last_msg = []

    def evolve(self):
        if (self.elevation_level == 1):
            self.drop_items(1, 0, 0, 0, 0, 0)
            return self.start_evolution()
        if (self.elevation_level == 2):
            if self.communications.call_players(2, 1):
                self.drop_items(1, 1, 1, 0, 0, 0)
                self.start_evolution()
            return
        if (self.elevation_level == 3):
            if self.communications.call_players(3, 1):
                self.drop_items(2, 0, 1, 0, 2, 0)
                self.start_evolution()
            return
        if (self.elevation_level == 4):
            if self.communications.call_players(4, 3):
                self.drop_items(1, 1, 2, 0, 1, 0)
                self.start_evolution()
            return
        if (self.elevation_level == 5):
            if self.communications.call_players(5, 3):
                self.drop_items(1, 2, 1, 3, 0, 0)
                self.start_evolution()
            return
        if (self.elevation_level == 6):
            if self.communications.call_players(6, 5):
                self.drop_items(1, 2, 3, 0, 1, 0)
                self.start_evolution()
            return
        if (self.elevation_level == 7):
            if self.communications.call_players(7, 5):
                self.drop_items(2, 2, 2, 2, 2, 1)
                self.start_evolution()
            return

    def eject(self):
        self.net.data_to_send.append("Eject")
        self.net.send_data()
        self.net.get_cmd()

    def take_item(self, item):
        self.net.data_to_send.append("Take " + item)
        self.net.send_data()
        self.net.get_cmd()

    def move_forward(self):
        self.net.data_to_send.append("Forward")
        self.net.send_data()
        self.net.get_cmd()

    def turn_right(self):
        self.net.data_to_send.append("Right")
        self.net.send_data()
        self.net.get_cmd()

    def turn_left(self):
        self.net.data_to_send.append("Left")
        self.net.send_data()
        self.net.get_cmd()

    def move_towards_item(self, pos, item):
        i = 1
        line = 3
        prev = 0
        player_pos = 0

        while i <= pos:
            prev = i
            i = i + line
            line += 2
            self.move_forward()
        item_line_pos = pos - prev
        if line > 3:
            player_pos = line - 3
            player_pos = player_pos / 2
        if player_pos < item_line_pos:
                self.turn_right()
        if player_pos > item_line_pos:
                self.turn_left()
        while player_pos != item_line_pos:
            self.move_forward()
            if player_pos < item_line_pos:
                player_pos += 1
            if player_pos > item_line_pos:
                player_pos -= 1
        self.take_item(item)

    def get_args(self, str):
        i = 0

        str = str.strip('\n')
        str = str[:-1]
        str = str.strip('[')
        str = str.strip(']')
        args = str.split(',')
        for i in range (len(args)):
            if i > 0:
                args[i] = args[i].lstrip(" ")
            args[i] = args[i].split(' ')
        return args

    def look(self):
        self.net.data_to_send.append("Look")
        self.net.send_data()
        self.net.get_cmd()
        response = self.net.data_got[0]
        return self.get_args(response)

    def is_stealing(self, tile, item, tile_pos):
        players = 0

        if item == "food":
            return False
        for i in tile:
            if i == "player":
                players += 1
        if players == 1 and tile_pos == 0:
            return False
        if players >= 1:
            return True
        return False

    def find_item(self, item_list):
        i = 0
        tile_pos = 0
        turn = 0

        for turn in range (4):
            items_around = self.look()
            for i in range (len(items_around)):
                tile_pos = 0
                for item in items_around[i]:
                    for item_to_find in item_list:
                        if item == item_to_find and self.is_stealing(item, item_to_find, tile_pos) == False:
                            self.move_towards_item(i, item_to_find)
                            return True
                    tile_pos += 1
            self.turn_right()
        return False

    def required_thystame(self):
        required_stones = 0
        if self.elevation_level == 7:
            required_stones += 1
        return required_stones

    def required_phiras(self):
        required_stones = 0

        if self.elevation_level == 4 or self.elevation_level == 6:
            required_stones += 1
        if self.elevation_level == 3 or self.elevation_level == 7:
            required_stones += 2
        return required_stones

    def required_mendiane(self):
        required_stones = 0

        if self.elevation_level == 5:
            required_stones += 3
        if self.elevation_level == 7:
            required_stones += 2
        return required_stones

    def required_sibur(self):
        required_stones = 0

        if self.elevation_level > 1:
            required_stones += 1
        if self.elevation_level == 4 or self.elevation_level == 7:
            required_stones += 1
        if self.elevation_level == 6:
            required_stones += 2
        return required_stones

    def required_deraumere(self):
        required_stones = 0

        if self.elevation_level == 2 or self.elevation_level > 3:
            required_stones += 1
        if self.elevation_level > 4:
            required_stones += 1
        return required_stones

    def required_linemate(self):
        required_stones = 1

        if self.elevation_level == 3 or self.elevation_level == 7:
            required_stones += 1
        return required_stones

    def get_stone_list(self):
        stone_list = []

        if self.linemate < self.required_linemate():
            stone_list.append("linemate")
        if self.deraumere < self.required_deraumere():
            stone_list.append("deraumere")
        if self.sibur < self.required_sibur():
            stone_list.append("sibur")
        if self.mendiane < self.required_mendiane():
            stone_list.append("mendiane")
        if self.phiras < self.required_phiras():
            stone_list.append("phiras")
        if self.thystame < self.required_thystame():
            stone_list.append("thystame")
        return stone_list

    def collect_items(self, item_list):
        if self.food < self.food_required + 3:
            item_list.append("food")
        if item_list == []:
            return
        self.find_item(item_list)

    def survive_cycle(self):
        if self.food > self.food_required:
            return
        if self.find_item(["food"]):
            self.food += 1
            return self.survive_cycle()
        self.move_forward()
        self.survive_cycle()

    def get_inv(self):
        self.net.data_to_send.append("Inventory")
        self.net.send_data()
        self.net.get_cmd()
        response = self.net.data_got[0]
        return self.get_args(response)

    def set_inv(self):
        inv = self.get_inv()
        try:
            for item in inv:
                if item[0] == "food":
                    self.food = int(item[1])
                if item[0] == "linemate":
                    self.linemate = int(item[1])
                if item[0] == "deraumere":
                    self.deraumere = int(item[1])
                if item[0] == "sibur":
                    self.sibur = int(item[1])
                if item[0] == "mendiane":
                    self.mendiane = int(item[1])
                if item[0] == "phiras":
                    self.phiras = int(item[1])
                if item[0] == "thystame":
                    self.thystame = int(item[1])
        except:
            print("Error: couln't read inventory cmd server response")

    def move_towards_player(self, pos, item):
        i = 1
        line = 3
        prev = 0
        player_pos = 0

        while i <= pos:
            prev = i
            i = i + line
            line += 2
            self.move_forward()
        item_line_pos = pos - prev
        if line > 3:
            player_pos = line - 3
            player_pos = player_pos / 2
        if player_pos < item_line_pos:
                self.turn_right()
        if player_pos > item_line_pos:
                self.turn_left()
        while player_pos != item_line_pos:
            self.move_forward()
            if player_pos < item_line_pos:
                player_pos += 1
            if player_pos > item_line_pos:
                player_pos -= 1
        self.eject()

    def search_for_players(self):
        i = 0
        tile_pos = 0
        turn = 0

        for turn in range (4):
            items_around = self.look()

            for i in range (len(items_around)):
                tile_pos = 0
                for item in items_around[i]:
                    if item == "player":
                        self.move_towards_player(i, "player")
                        return True
                    tile_pos += 1
            self.turn_right()
        return False

    def find_players(self, item_list):
        if self.food < self.food_required + 3:
            item_list.append("food")
        else:
            self.search_for_players()

    def action(self):
        self.set_inv()
        self.survive_cycle()
        for i in range (self.elevation_level + randint(0, 9)):
            self.turn_right()
            if self.communications.check_msg_list():
                self.net.last_msg = []
                return "Forward"
        stones_list = self.get_stone_list()
        if stones_list == []:
            self.evolve()
        self.collect_items(stones_list)
        return "Forward"

    def zombie_action(self):
        prob = randint(1, 8)
        self.set_inv()
        self.survive_cycle()
        stones_list = self.get_stone_list()
        self.find_players(stones_list)
        if (prob == 1):
            return "Right"
        if (prob == 4):
            return "Left"
        return "Forward"
