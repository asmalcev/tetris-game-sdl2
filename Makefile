BINNAME = tetris_sdl2

AUTHOR_DIR = ./src/Components/Author/

build:
	g++ src/main.cpp src/Components/Button/*.cpp src/Components/Menu/*.cpp src/Components/Author/*.cpp src/Components/LeaderBoard/*.cpp src/Components/LeaderBoardController/*.cpp src/Components/Presenter/*.cpp src/Components/TetrisEngine/*.cpp src/Components/VisibleElement/*.cpp  src/Utils/*.cpp src/Components/Link/*.cpp src/Components/LinkedList/*.cpp -lSDL2 -lSDL2_ttf -o build/$(BINNAME)

build-dev:
	g++ src/main.cpp src/Components/Button/*.cpp src/Components/Menu/*.cpp src/Components/LeaderBoard/*.cpp src/Components/LeaderBoardController/*.cpp src/Components/Presenter/*.cpp src/Components/TetrisEngine/*.cpp src/Components/VisibleElement/*.cpp  src/Utils/*.cpp src/Components/Link/*.cpp src/Components/LinkedList/*.cpp -lSDL2 -lSDL2_ttf -o build/$(BINNAME)

run: build/$(BINNAME)
	build/$(BINNAME)

all: build

.PHONY: all run build clear

author.o:
	g++ AUTHOR_DIR/*.cpp -o AUTHOR_DIR/author.o
