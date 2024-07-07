##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Main Makefile
##

# Variables

SERVER	=	zappy_server
GUI		=	zappy_gui
AI		=	zappy_ai

S_DIR	=	server
G_DIR	=	gui
A_DIR	=	ai

# Rules

all:
	$(MAKE) $(SERVER)
	$(MAKE) $(GUI)
	$(MAKE) $(AI)

$(SERVER):
	$(MAKE) -j$(nproc) -C $(S_DIR) $@
	cp $(S_DIR)/$(SERVER) .

$(GUI):
	$(MAKE) -C $(G_DIR) $@
	cp $(G_DIR)/$(GUI) .

$(AI):
	cp $(A_DIR)/autonomous/$(AI) .
	cp $(A_DIR)/hivemind/$(AI) $(AI)_hm

client:
	$(MAKE) -C $(S_DIR) client
	cp $(S_DIR)/client ./client

clean:
	$(MAKE) -C $(S_DIR) $@
	$(MAKE) -C $(G_DIR) $@
	rm -f $(shell find . -name "*.log")

fclean: clean
	$(MAKE) -C $(S_DIR) $@
	$(MAKE) -C $(G_DIR) $@
	rm -f $(SERVER)
	rm -f $(GUI)
	rm -f $(AI)
	rm -f $(AI)_hm
	rm -f client
	rm -f unit_tests

re:	fclean all

unit_tests:
	@$(MAKE) -C $(S_DIR) $@
	@mv $(S_DIR)/unit_tests .

tests_run: unit_tests
	@./unit_tests

.PHONY: all clean fclean re $(SERVER) $(GUI) $(AI) client
