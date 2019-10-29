#include "precompiled.hpp"
#include "Sprite.hpp"

#include "Singletons/WindowRenderer/WindowRenderer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace CayleeEngine::res
{
Sprite::Sprite() : mTexture(nullptr)
{
}

Sprite::Sprite(const char *filepath) : mTexture(nullptr)
{
  LoadImageFromFile(filepath);
}

Sprite::~Sprite()
{
  if (mTexture) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }
}

void Sprite::LoadImageFromFile(const char *filepath)
{
  if (mTexture) {
    SDL_LogWarn(SDL_LOG_CATEGORY_RENDER,
                "Overwritten already loaded image with: %s", filepath);
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }

  int req_format = STBI_rgb_alpha;
  int width, height, orig_format;

  unsigned char* data = stbi_load(filepath, &width, &height, &orig_format, req_format);
  
  if (!data || stbi_failure_reason()) {
    SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Loading image failed: %s", stbi_failure_reason());
    return;
  }

  int depth, pitch;
  Uint32 pixel_format;
  if (req_format == STBI_rgb) {
    depth = 24;
    pitch = 3 * width;
    pixel_format = SDL_PIXELFORMAT_RGB24;
  }
  else { // STBI_rgb_alpha (RGBA)
    depth = 32;
    pitch = 4 * width;
    pixel_format = SDL_PIXELFORMAT_RGBA32;
  }

  SDL_Surface* surface = 
    SDL_CreateRGBSurfaceWithFormatFrom(static_cast<void*>(data),
                                       width, height, depth, pitch, pixel_format);
  
  if (!surface) {
    SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Creating surface failed: %s", SDL_GetError());
    stbi_image_free(data);
    return;
  }

  mTexture = SDL_CreateTextureFromSurface(WindowRenderer::GetInstance()->GetRenderer(), surface);

  if (!mTexture) {
    SDL_LogWarn(SDL_LOG_CATEGORY_RENDER,
      "Unable to Create SDL Texture: %s", SDL_GetError());
  }

  stbi_image_free(data);
  SDL_FreeSurface(surface);
}
}