#pragma once
#include "../Window/Window.hpp"
#include "../Button/Button.hpp"

class LeaderBoard : public Window {
private:
  SDL_Rect textPos;
  SDL_Texture* leaderBoardTexture;

public:
  Button* backBtn;
  
  LeaderBoard(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  );
  ~LeaderBoard();
  void render() override;
  void update() override;
  void click(int x, int y) override;
  void hover(int x, int y) override;
  void keyEvent(SDL_Event&) override {};
};