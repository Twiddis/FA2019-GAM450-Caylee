#include "precompiled.hpp"
#include "Sprite.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace CayleeEngine::res
{
Sprite::Sprite() : mSurface(nullptr)
{
}

Sprite::Sprite(const char *filepath) : mSurface(nullptr)
{
  LoadImageFromFile(filepath);
}

Sprite::~Sprite()
{
  if (mSurface) {
    SDL_FreeSurface(mSurface);
    mSurface = nullptr;
  }
}

void Sprite::LoadImageFromFile(const char *filepath)
{
  if (mSurface) {
    SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, 
                "Overwritten already loaded image with: %s", filepath);
    SDL_FreeSurface(mSurface);
    mSurface = nullptr;
  }

  int req_format = STBI_rgb_alpha;
  int width, height, orig_format;

  unsigned char* data = stbi_load("../res/test.bmp", &width, &height, &orig_format, req_format);
  
  if (!data) {
    ("Loading image failed: %s", stbi_failure_reason());
  }

}

}