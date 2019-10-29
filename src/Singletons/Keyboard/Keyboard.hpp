#pragma once
#include "Singletons/Singleton.hpp"

namespace CayleeEngine
{

class Keyboard : public Singleton<Keyboard>
{
public:
  Keyboard();
  ~Keyboard();

  void ResetKeyboard();
  void SetKeyPressed(SDL_Scancode scancode) { mKeysPressed[scancode] = true; }
  void SetKeyReleased(SDL_Scancode scancode) { mKeysReleased[scancode] = true; }
  void SetKeyDown(SDL_Scancode scancode, bool b) { mKeysDown[scancode] = b; }

  bool IsKeyPressed(SDL_Scancode scancode) const { return mKeysPressed[scancode]; }
  bool IsKeyReleased(SDL_Scancode scancode) const { return mKeysReleased[scancode]; }
  bool IsKeyDown(SDL_Scancode scancode) const { return mKeysDown[scancode]; }

  const std::vector<bool>& GetKeysDown() const { return mKeysPressed; }
  const std::vector<bool>& GetKeysUp() const { return mKeysReleased; }

private:
  std::vector<bool> mKeysPressed;
  std::vector<bool> mKeysReleased;

  std::vector<bool> mKeysDown;
};


}