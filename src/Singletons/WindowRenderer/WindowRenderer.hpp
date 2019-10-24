#pragma once
#include "Singletons/Singleton.hpp"

namespace CayleeEngine
{

class WindowRenderer : public Singleton<WindowRenderer>
{
public:
  WindowRenderer();
  ~WindowRenderer();

  constexpr SDL_Window *GetWindow() { return mWindow; }
  constexpr SDL_Renderer *GetRenderer() { return mRenderer; }

private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
};


}