##
## EPITECH PROJECT, 2024
## arg++
## File description:
## Makefile
##

NAME	=	arg++

LIB		=	lib$(NAME).a

CC		=	g++

TMPDIR	=	tmp

LIBDIR	=	$(realpath ../)

# Sources

SRC		=	$(shell find src -type f -name '*.cpp')

OBJ		=	$(SRC:%.cpp=$(TMPDIR)/%.o)

CFLAGS	+=	-W -Wall -Wextra -Iinclude

LDFLAGS	=

INCLIBS	=	arg linked

CFLAGS 	+= 	$(foreach lib,$(INCLIBS),-I$(LIBDIR)/$(lib)/include/)

LDFLAGS	+=	$(foreach lib,$(INCLIBS),-L$(LIBDIR)/$(lib)/)

LDFLAGS	+=	$(foreach lib,$(INCLIBS),-l$(lib))

# Rules

$(LIB):	lib $(OBJ)
	ar rc $(LIB) $(OBJ)

all:	$(LIB)

lib:
	for lib in $(INCLIBS); do make -C $(LIBDIR)/$$lib; done

lclean:
	for lib in $(INCLIBS); do make -C $(LIBDIR)/$$lib fclean; done

clean:
	rm -rf $(TMPDIR)
	rm -f $(shell find . -type f -name '*.gc*')

fclean:	clean lclean
	rm -f $(LIB)

re:	clean all

$(TMPDIR)/%.o:	%.cpp
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: all clean fclean re lib
