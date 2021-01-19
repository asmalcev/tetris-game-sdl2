BINNAME = tetris_sdl2

BUILD_FLAGS = -lSDL2 -lSDL2_ttf

MAIN_PATH         = ./src
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

BUILD_DIR = ./build

build: $(BUILD_DIR)/main.o $(BUILD_DIR)/author.o $(BUILD_DIR)/menu.o $(BUILD_DIR)/modal.o $(BUILD_DIR)/leaderboard.o $(BUILD_DIR)/leaderboardcontroller.o $(BUILD_DIR)/presenter.o $(BUILD_DIR)/button.o $(BUILD_DIR)/textfield.o $(BUILD_DIR)/engine.o $(BUILD_DIR)/velement.o $(BUILD_DIR)/link.o $(BUILD_DIR)/linkedlist.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/fallingpoints.o $(BUILD_DIR)/field.o
	g++ $^ $(BUILD_FLAGS) -o $(BUILD_DIR)/$(BINNAME)

$(BUILD_DIR)/main.o: $(MAIN_PATH)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/author.o: $(AUTHOR_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/menu.o: $(MENU_DIR)/Menu.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/fallingpoints.o: $(MENU_DIR)/FallingPoint.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/modal.o: $(MODAL_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/leaderboard.o: $(LEADERBOARD_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/leaderboardcontroller.o: $(LEADERBOARD_C_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/presenter.o: $(PRESENTER_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/button.o: $(BUTTON_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/textfield.o: $(TEXT_FIELD_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/engine.o: $(ENGINE_DIR)/TetrisEngine.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/field.o: $(ENGINE_DIR)/Field.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/velement.o: $(V_ELEMENT_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/link.o: $(LINK_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/linkedlist.o: $(LINKED_LIST_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

$(BUILD_DIR)/utils.o: $(UTILS_DIR)/*.cpp
	g++ $(BUILD_FLAGS) -c $< -o $@

run: $(BUILD_DIR)/$(BINNAME)
	$(BUILD_DIR)/$(BINNAME)

all: build

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all run build clean