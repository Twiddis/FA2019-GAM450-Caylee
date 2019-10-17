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

private:
  SDL_Surface *mSurface;
};
}