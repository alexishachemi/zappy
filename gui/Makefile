##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

NAME	=	zappy_gui

CC		=	g++

SRCDIR	=	ZappyGui

TMPDIR	=	tmp

LIBDIR	=	$(realpath ../lib)

# SRC

SRC		=	$(shell find $(SRCDIR) -type f -name '*.cpp')

OBJ		=	$(SRC:%.cpp=$(TMPDIR)/%.o)

INCDIRS	=	$(shell find $(SRCDIR) -name '*.hpp' -exec dirname {} \; | sort -u\
 | sed 's/^/-I/')

LDFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

INCLIBS	=	raylib socknet++ arg++ arg socknet clogger linked

LIBS	=	$(foreach lib,$(INCLIBS),$(LIBDIR)/$(lib)/lib$(lib).a)

CFLAGS 	+= 	$(foreach lib,$(INCLIBS),-I$(LIBDIR)/$(lib)/include/)

LDFLAGS	+=	$(foreach lib,$(INCLIBS),-L$(LIBDIR)/$(lib)/)

LDFLAGS	+=	$(foreach lib,$(INCLIBS),-l$(lib))

CFLAGS	+=	-std=c++20 $(INCDIRS) -O3

# Rules

all: lib
	$(MAKE) -j$(nproc) $(NAME)

$(NAME): lib $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(CFLAGS)

lib:
	for lib in $(INCLIBS); do make -j$(nproc) -C $(LIBDIR)/$$lib; done

$(TMPDIR)/%.o:	%.cpp
	@mkdir -p $(@D)
	g++ -o $@ -c $< $(LDFLAGS) $(CFLAGS)

clean:
	rm -rf $(TMPDIR)

lclean:
	for lib in $(INCLIBS); do make -C $(LIBDIR)/$$lib fclean; done

bclean:
	rm -f $(NAME)

oclean: clean bclean

fclean: clean bclean lclean

asan:	CFLAGS += -fsanitize=address -g3
asan:	$(NAME)

re: fclean all

ore: oclean all

.PHONE: all clean fclean re lib lclean blean olean asan re
