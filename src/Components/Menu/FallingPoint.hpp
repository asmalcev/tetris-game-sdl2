#include <SDL2/SDL.h>

class FallingPoint {
private:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box;
  int startY;

public:
  FallingPoint(
    SDL_Renderer* renderer,
    int x,
    int y,
    int size
  );
  ~FallingPoint() {}
  void render();
  void update();
};