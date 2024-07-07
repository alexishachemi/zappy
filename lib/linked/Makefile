##
## EPITECH PROJECT, 2024
## linked
## File description:
## Makefile
##

NAME	=	linked

LIB		=	lib$(NAME).a

INC		=	include/linked.h

CC		=	gcc

TMPDIR	=	tmp

# Sources

SRC		=	$(shell find src -type f -name '*.c')

OBJ		=	$(SRC:%.c=$(TMPDIR)/%.o)

CFLAGS	+=	-W -Wall -Wextra -Iinclude

# Rules

$(LIB):	$(OBJ)
	ar rc $(LIB) $(OBJ)

all:	$(LIB)

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
