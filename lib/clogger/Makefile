##
## EPITECH PROJECT, 2024
## clogger
## File description:
## Makefile
##

NAME	=	clogger

LIB		=	lib${NAME}.a

INC		=	clogger.h

CC		=	gcc

TMPDIR	=	tmp

INST_BIN_DIR	=	/usr/local/lib

INST_INC_DIR	=	/usr/local/include

# Source

SRC		=	$(shell find src -type f -name '*.c')

OBJ		=	$(SRC:%.c=$(TMPDIR)/%.o)

# flags

INCDIRS	=	include

INCLIBS	=

CFLAGS	+=	-Wall -Wextra

CFLAGS	+=	$(addprefix -I,$(INCDIRS))

LDFLAGS	+=	$(addprefix -l,$(INCLIBS))

# rules

$(LIB):	$(OBJ)
	ar rc $(LIB) $(OBJ)

all: $(LIB)

install:	$(LIB)
	sudo cp $(LIB) $(INST_BIN_DIR)
	sudo cp include/$(INC) $(INST_INC_DIR)
	sudo ldconfig

uninstall:
	sudo rm -f $(INST_BIN_DIR)/$(LIB)
	sudo rm -f $(INST_INC_DIR)/$(INC)
	sudo ldconfig

reinstall: uninstall install

clean:
	rm -rf $(TMPDIR)
	rm -rf $(shell find . -type f -name '*.gc*')

fclean: clean
	rm -f $(LIB)
	rm -f $(NAME)

re: fclean all

debug:	$(LIB)
	gcc -o $(NAME) tests/main.c $(LDFLAGS) $(CFLAGS) -L. -l$(NAME)

$(TMPDIR)/%.o:	%.c
	@mkdir -p $(@D)
	gcc -o $@ -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: all install uninstall reinstall clean fclean re debug
