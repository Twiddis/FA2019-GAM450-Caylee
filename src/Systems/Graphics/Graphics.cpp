#include "precompiled.hpp"
#include "Graphics.hpp"

#include "Singletons/WindowRenderer/WindowRenderer.hpp"


namespace CayleeEngine
{
Graphics::Graphics()
{
  WindowRenderer::Initialize();

  mTest = res::Sprite::Create("../res/Textures/Orange.jpg");
}

Graphics::~Graphics()
{
  WindowRenderer::Shutdown();
}

void Graphics::StartFrame()
{
  SDL_SetRenderDrawColor(WindowRenderer::GetInstance()->GetRenderer(), 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderClear(WindowRenderer::GetInstance()->GetRenderer());
}

void Graphics::Update(float )
{
  SDL_Rect rect;
  rect.w = 100;
  rect.h = 100;
  rect.x = 100;
  rect.y = 0;

  SDL_RenderCopy(WindowRenderer::GetInstance()->GetRenderer(), mTest->GetTexture(), NULL, &rect);
  
}

void Graphics::EndFrame()
{
  SDL_RenderPresent(WindowRenderer::GetInstance()->GetRenderer());
}
}