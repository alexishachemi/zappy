##
## EPITECH PROJECT, 2024
## socknet
## File description:
## Makefile
##

NAME	=	socknet

LIB		=	lib$(NAME).a

CC		=	gcc

TMPDIR	=	tmp

# Sources

SRC		=	$(shell find src -type f -name '*.c')

OBJ		=	$(SRC:%.c=$(TMPDIR)/%.o)

CFLAGS	+=	-W -Wall -Wextra -Iinclude -I../clogger/include -I../linked/include

LDFLAGS	=	-L../linked -linked -L../clogger -lclogger

# Rules

$(LIB):	lib $(OBJ)
	ar rc $(LIB) $(OBJ)

all:	$(LIB)

lib:
	make -C ../clogger/
	make -C ../linked/

clean:
	rm -rf $(TMPDIR)
	rm -f $(shell find . -type f -name '*.gc*')

fclean:	clean
	rm -f $(LIB)

re:	clean all

$(TMPDIR)/%.o:	%.c
	@mkdir -p $(@D)
	gcc -o $@ -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: all clean fclean re lib
