CC			= g++
FLAGS		= -g -W -Werror -Wall -Wextra -Wno-unknown-pragmas -std=c++17 -MMD

INC_DIR		  = include
SRC_DIR		  = src
BIN_DIR		  = bin
RESOURCES_DIR = resources

CORE_M 		= Core Core/Debug Core/Maths Core/DataStructure
GAME_M 		= Game Game/StateMachine Game/Items Game/Inputs Game/Inputs/Commands
PHYSICS_M   = Physics Physics/Collisions 
MODULES		= LowRenderer $(CORE_M) $(GAME_M) $(PHYSICS_M) Resources UI

INC_DIRS	= $(shell find $(INC_DIR) -type d)
EXE			= openGL

SRC			= $(shell find $(SRC_DIR) -name "*.cpp")
OBJ			= $(patsubst $(SRC_DIR)%.cpp, $(BIN_DIR)%.o, $(SRC))

TARGET		= $(BIN_DIR)/$(EXE)

LOC_LIB		= ./lib/
LIBS		= m GL GLEW SDL2 SOIL freetype
LIBRARIES	= $(patsubst %, -l%, $(LIBS))
INCLUDES	= $(patsubst %, -I%, $(INC_DIRS)) -I/usr/include/freetype2

.PHONY: all clean re run build folders mre mrun mrr valgrind gdb

build : all

all: $(OBJ)
	@$(CC) $(FLAGS) $^ $(LIBRARIES) -g -o $(TARGET) -L$(LOC_LIB)
	@echo "Building \e[1m$(TARGET)\e[0m"


$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $< -c $(LIBRARIES) -g $(INCLUDES) -o $@
	@echo "Compiling \e[36m$<\e[0m"

clean:
	@rm -rf $(OBJ) $(TARGET)
	@echo "\e[1;4mCleaning...\e[0m"
	@echo


re: clean folders all


run: all
	@echo "\t\e[1;4mExecuting program..\e[0m"
	@echo
	@./$(TARGET)


build: folders all


folders:
	@echo "\e[1;38;5;94mBuilding folders..\e[0m";
	@for dir in $(SRC_DIR) $(INC_DIR) $(BIN_DIR) ; do \
		if [ ! -d "./$$dir" ] ; then \
			mkdir $$dir; \
			echo "\t\e[38;5;154m./$$dir\e[0m created"; \
		fi; \
		for mod in $(MODULES); do \
			if [ ! -d "./$$dir/$$mod" ] ; then \
				mkdir $$dir/$$mod; \
				echo "\t\e[38;5;94m./$$dir\e[38;5;154m/$$mod\e[0m created";  \
			fi; \
		done; \
	done;
	@if [ ! -d "./$(RESOURCES_DIR)" ] ; then \
		mkdir $(RESOURCES_DIR); \
		echo "\t\e[38;5;154m./$(RESOURCES_DIR)\e[0m created"; \
	fi;
	@echo "\e[1;38;5;94m------------------\e[0m\n";


mre:
	@$(MAKE) -sj clean
	@$(MAKE) -sj folders
	@$(MAKE) -sj all

mrun:
	@$(MAKE) -sj run

mrr: mre mrun


valgrind: all
	@echo "\e[38;5;154mExecuting valgrind on \e[1m$(TARGET)\e[0m"
	@echo
	@valgrind --leak-check=full ./$(TARGET)


gdb: all
	@echo "\e[38;5;154mExecuting gdb on \e[1m$(TARGET)\e[0m\n"
	@echo
	@gdb ./$(TARGET)

-include $(OBJ:.o=.d)