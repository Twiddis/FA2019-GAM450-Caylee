#pragma once
#include "Resources/ResourceBase.hpp"

namespace CayleeEngine::res
{
class Sprite : public ResourceBase<Sprite>
{
public:
  Sprite();
  Sprite(const char *filepath);
  ~Sprite();

  void LoadImageFromFile(const char *filepath);
  constexpr SDL_Texture* GetTexture() { return mTexture; }

private:
  SDL_Texture *mTexture;
};
}