BINNAME = tetris_sdl2

build:
	g++ src/dev.cpp -lSDL2 -lSDL2_ttf -o build/$(BINNAME)

run: 
	build/$(BINNAME)

all: build

.PHONY: all run build