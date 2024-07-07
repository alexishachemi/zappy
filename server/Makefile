##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

NAME	=	zappy_server

INC		=	include/linked.h

CC		=	gcc

TMPDIR	=	tmp

LIBDIR	=	$(realpath ../lib)

# Sources

SRC		=	$(shell find src -type f -name '*.c' ! -name 'main.c')

MAIN	=	src/main.c

MOBJ	=	$(MAIN:%.c=$(TMPDIR)/%.o) $(OBJ)

OBJ		=	$(SRC:%.c=$(TMPDIR)/%.o)

INCLIBS	=	socknet clogger arg linked

LIBS	=	$(foreach lib,$(INCLIBS),$(LIBDIR)/$(lib)/lib$(lib).a)

CFLAGS	+=	-W -Wall -Wextra -Iinclude

CFLAGS 	+= 	$(foreach lib,$(INCLIBS),-I$(LIBDIR)/$(lib)/include/)

LDFLAGS	=	-lm -lncurses

LDFLAGS	+=	$(foreach lib,$(INCLIBS),-L$(LIBDIR)/$(lib)/)

LDFLAGS	+=	$(foreach lib,$(INCLIBS),-l$(lib))

# Tests

TNAME	=	unit_tests

TDIR	=	$(realpath ../tests/unit_tests/server/)

TSRC	=	$(shell find $(TDIR)/src -type f -name '*.c')

TOBJ	=	$(TSRC:%.c=$(TMPDIR)/%.o)

TFLAGS	=	-lcriterion -lgcov --coverage -I$(TDIR)/include

# Rules

$(NAME):	lib $(MOBJ)
	$(CC) -o $(NAME) $(MOBJ) $(CFLAGS) $(LDFLAGS)

all:	$(NAME)

lib:
	for lib in $(INCLIBS); do make -C $(LIBDIR)/$$lib; done

clean:
	rm -rf $(TMPDIR)
	rm -f $(shell find . -type f -name '*.gc*')
	rm -f *.log

lclean:
	for lib in $(INCLIBS); do make -C $(LIBDIR)/$$lib fclean; done

fclean:	lclean clean
	rm -f $(NAME)
	rm -f $(TNAME)
	rm -f test_server
	rm -f client

re:	clean all

$(TNAME):	CFLAGS += $(TFLAGS)
$(TNAME):	lib $(TOBJ) $(OBJ)
	$(CC) -o $@ $(TOBJ) $(OBJ) $(CFLAGS) $(LDFLAGS)

tests_run:	$(TNAME)
	./$(TNAME)

test_server:	lib $(OBJ)
	$(CC) -o $@ tests/$@.c $(OBJ) $(CFLAGS) $(LDFLAGS)

client:	lib $(OBJ)
	$(CC) -o $@ tests/test_client.c $(OBJ) $(CFLAGS) $(LDFLAGS)

debug:	test_server test_client

$(TMPDIR)/%.o:	%.c
	@mkdir -p $(@D)
	gcc -o $@ -c $< $(CFLAGS) $(LDFLAGS)

asan:	CFLAGS += -fsanitize=address -g3
asan:	all

.PHONY: all clean fclean re unit_tests tests_run lib
