#pragma once
#include "../Window/Window.hpp"
#include "../Button/Button.hpp"
#include "../Modal/Modal.hpp"
#include "../TetrisEngine/TetrisEngine.hpp"
#include "../VisibleElement/VisibleElement.hpp"

class Presenter : public Window {
private:
  TetrisEngine   * tetris;
  VisibleElement * nshape;
  VisibleElement * counter;
  SDL_Texture    * fieldTexture;
  SDL_Rect fieldBox;
  int timer;
  bool isModalOpened;

  const SDL_Color colors[5] = {
    {245, 245, 245},
    {30, 136, 229},
    {229, 57, 53},
    {253, 216, 53},
    {94, 53, 177}
  };

  void fillFieldTexture();
  void fillShapeTexture();
  void fillCounterTexture();

public:
  Button * backBtn     = nullptr;
  Modal  * modalWindow = nullptr;

  Presenter(
    SDL_Renderer * renderer,
    int x,
    int y,
    int w,
    int h
  );
  ~Presenter();
  void render() override;
  void update() override;
  void click(int x, int y) override;
  void hover(int x, int y) override;
  void keyEvent(SDL_Event&) override;
  void reload();
  void updateField();
};