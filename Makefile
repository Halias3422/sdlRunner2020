NAME= runner

SRC_PATH= ./src/
OBJ_PATH= ./obj/
INC_PATH= ./includes/

SOURCES= main.cpp \
		 sdl_functions.cpp\
		 print.cpp\
		 generation.cpp\
		 Background.cpp\
		 Player.cpp \
		 Platform.cpp \

INCLUDES= runner.h \
		  Background.h \
		  Player.h \
		  Platform.h \

OBJECTS= $(SOURCES:.cpp=.o)

INC= $(addprefix $(INC_PATH), $(INCLUDES))
SRC= $(addprefix $(SRC_PATH), $(SOURCES))
OBJ= $(addprefix $(OBJ_PATH), $(OBJECTS))

FLAGS= -std=c++11 -Wall -Werror -Wextra 
MAC_SDL= -I $(shell sdl2-config --cflags) $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer
LINUX_SDL= -Wl,-rpath=/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_mixer

all:
	make $(NAME)

$(NAME): $(OBJ) Makefile
	g++ $(FLAGS) -o $(NAME) $(OBJ) -I.$(MAC_SDL)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp $(INC)
	if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	g++ $(FLAGS) -I $(INC_PATH) $(shell sdl2-config --cflags) -o $@ -c $<

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
