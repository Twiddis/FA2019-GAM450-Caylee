#include "precompiled.hpp"
#include "WindowRenderer.hpp"

namespace CayleeEngine
{
WindowRenderer::WindowRenderer() : mWindow(nullptr), mRenderer(nullptr)
{
  if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't initialize SDL: %s", SDL_GetError());

  if (SDL_CreateWindowAndRenderer(960, 540, SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't create window and renderer: %s", SDL_GetError());

  SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

WindowRenderer::~WindowRenderer()
{
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
}
}