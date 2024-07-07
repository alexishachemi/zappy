##
## EPITECH PROJECT, 2024
## arg
## File description:
## Makefile
##

NAME	=	arg

LIB		=	lib$(NAME).a

INC		=	include/arg.h

CC		=	gcc

TMPDIR	=	tmp

# Sources

SRC		=	$(shell find src -type f -name '*.c')

OBJ		=	$(SRC:%.c=$(TMPDIR)/%.o)

CFLAGS	+=	-W -Wall -Wextra -Iinclude -I../linked/include

LDFLAGS	=	-L../linked -linked

# Rules

$(LIB):	lib $(OBJ)
	ar rc $(LIB) $(OBJ)

all:	$(LIB)

lib:
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

.PHONY: all clean fclean re
