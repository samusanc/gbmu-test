NAME        = gbmu

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++17 -g
CXXFLAGS    += $(shell sdl2-config --cflags)
LDFLAGS     = $(shell sdl2-config --libs)

SRCS        = main.cpp \
              src/GameBoy.cpp \
              src/bus/Bus.cpp \
              src/cpu/CPU.cpp \
              src/ppu/PPU.cpp \
              src/cartridge/Cartridge.cpp \
              src/timer/Timer.cpp \
              src/joypad/Joypad.cpp \
              src/display/Display.cpp

OBJ_DIR     = build
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
