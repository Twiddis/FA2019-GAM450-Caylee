#include "precompiled.hpp"
#include "Input.hpp"
#include "Singletons/Keyboard/Keyboard.hpp"


namespace CayleeEngine
{
Input::Input()
{
  Keyboard::Initialize();


}
Input::~Input()
{
  Keyboard::Shutdown();
}

void Input::StartFrame()
{
  Keyboard::GetInstance()->ResetKeyboard();

  SDL_Event sdl_event;
  while (SDL_PollEvent(&sdl_event)) {
    if (sdl_event.type == SDL_QUIT)
      exit(0);

    if (sdl_event.type == SDL_KEYDOWN) {
  //    std::cout << sdl_event.key.keysym.scancode << " Down" << std::endl;
      Keyboard::GetInstance()->SetKeyPressed(sdl_event.key.keysym.scancode);
      Keyboard::GetInstance()->SetKeyDown(sdl_event.key.keysym.scancode, true);
    }
    if (sdl_event.type == SDL_KEYUP) {
 //     std::cout << sdl_event.key.keysym.scancode << " Up" << std::endl;
      Keyboard::GetInstance()->SetKeyReleased(sdl_event.key.keysym.scancode);
      Keyboard::GetInstance()->SetKeyDown(sdl_event.key.keysym.scancode, false);
    }
  }

}

void Input::Update(float )
{


}
void Input::EndFrame()
{
}
}