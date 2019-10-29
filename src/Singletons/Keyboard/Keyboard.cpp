#include "precompiled.hpp"
#include "Keyboard.hpp"

namespace CayleeEngine
{
Keyboard::Keyboard() : mKeysPressed(SDL_NUM_SCANCODES, false),
                       mKeysReleased(SDL_NUM_SCANCODES, false),
                       mKeysDown(SDL_NUM_SCANCODES, false)
{
  
}

Keyboard::~Keyboard()
{
}
void Keyboard::ResetKeyboard()
{
  std::fill(mKeysPressed.begin(), mKeysPressed.end(), false);
  std::fill(mKeysReleased.begin(), mKeysReleased.end(), false);
}
}