#include "precompiled.hpp"
#include "Graphics.hpp"

namespace CayleeEngine
{
Graphics::Graphics() : mWindow(nullptr), mRenderer(nullptr)
{


  if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                "Couldn't initialize SDL: %s", SDL_GetError());

  if (SDL_CreateWindowAndRenderer(960, 540, SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                "Couldn't create window and renderer: %s", SDL_GetError());



}
Graphics::~Graphics()
{
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
}

void Graphics::StartFrame()
{
  SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(mRenderer);
}

void Graphics::Update(float )
{
}

void Graphics::EndFrame()
{
}
}