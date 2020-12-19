#pragma
#include <SDL2/SDL.h>
#include <string>
#include "../Window/Window.hpp"
#include "../Button/Button.hpp"
#include "../TextField/TextField.hpp"

class Modal : public Window {
private:
  SDL_Texture * modalTexture;
  Button      * backBtn   = nullptr;
  TextField   * textField = nullptr;

public:

  Modal(
    SDL_Renderer * renderer,
    int w,
    int h,
    std::string msg,
    Button    * btn,
    TextField * textField
  );
  ~Modal();
  void render() override;
  void update() override;
  void click(int x, int y) override;
  void hover(int x, int y) override;
  void keyEvent(SDL_Event&) override;
};