BINNAME = tetris_sdl2

BUILD_FLAGS = -lSDL2 -lSDL2_ttf

MAIN_PATH         = ./src/main.cpp
AUTHOR_DIR        = ./src/Components/Author
MENU_DIR          = ./src/Components/Menu
MODAL_DIR         = ./src/Components/Modal
LEADERBOARD_DIR   = ./src/Components/LeaderBoard
LEADERBOARD_C_DIR = ./src/Components/LeaderBoardController
PRESENTER_DIR     = ./src/Components/Presenter
BUTTON_DIR        = ./src/Components/Button
TEXT_FIELD_DIR    = ./src/Components/TextField
ENGINE_DIR        = ./src/Components/TetrisEngine
V_ELEMENT_DIR     = ./src/Components/VisibleElement
LINK_DIR          = ./src/Components/Link
LINKED_LIST_DIR   = ./src/Components/LinkedList
UTILS_DIR         = ./src/Utils

build:
	g++ $(MAIN_PATH) $(AUTHOR_DIR)/*.cpp $(MENU_DIR)/*.cpp $(MODAL_DIR)/*.cpp $(LEADERBOARD_DIR)/*.cpp $(LEADERBOARD_C_DIR)/*.cpp $(PRESENTER_DIR)/*.cpp $(BUTTON_DIR)/*.cpp $(TEXT_FIELD_DIR)/*.cpp $(ENGINE_DIR)/*.cpp $(V_ELEMENT_DIR)/*.cpp $(LINK_DIR)/*.cpp $(LINKED_LIST_DIR)/*.cpp $(UTILS_DIR)/*.cpp $(BUILD_FLAGS) -o build/$(BINNAME)

run: build/$(BINNAME)
	build/$(BINNAME)

all: build

.PHONY: all run build clear