BINNAME = tetris_sdl2

build:
	g++ src/main.cpp src/Components/Button/*.cpp src/Components/Menu/*.cpp src/Components/Author/*.cpp src/Utils/*.cpp src/Components/Link/*.cpp -lSDL2 -lSDL2_ttf -o build/$(BINNAME)

run: 
	build/$(BINNAME)

all: build

.PHONY: all run build