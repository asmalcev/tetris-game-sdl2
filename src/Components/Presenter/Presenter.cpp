#include "Presenter.hpp"

Presenter::Presenter(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h
) : Window(renderer, x, y, w, h) {

}

Presenter::~Presenter() {
  delete backBtn;
}

void Presenter::render() {

}

void Presenter::update() {

  backBtn->update();
}

void Presenter::click(int x, int y) {

  backBtn->click(x, y);
}

void Presenter::hover(int x, int y) {

  backBtn->hover(x,y);
}