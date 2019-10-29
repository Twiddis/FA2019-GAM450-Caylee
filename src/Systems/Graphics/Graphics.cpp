#include "precompiled.hpp"
#include "Graphics.hpp"

#include "Singletons/WindowRenderer/WindowRenderer.hpp"
#include "Resources/Sprite/Sprite.hpp"
#include "Objects/ScriptField/ScriptField.hpp"
#include "Objects/Register/Register.hpp"
#include "Objects/Object.hpp"

namespace CayleeEngine
{
Graphics::Graphics() : mFont(nullptr)
{
  WindowRenderer::Initialize();
  if (TTF_Init() != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Error! Could not initialize TTF: %s", TTF_GetError());
  }

  mFont = TTF_OpenFont("../res/Fonts/arial.ttf", 25);
  if (!mFont) {
    SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Error! Could not initialize font: %s", TTF_GetError());
  }

}

Graphics::~Graphics()
{
  TTF_CloseFont(mFont);

  TTF_Quit();
  WindowRenderer::Shutdown();
}

void Graphics::StartFrame()
{
  SDL_SetRenderDrawColor(WindowRenderer::GetInstance()->GetRenderer(), 0x04, 0x04, 0x04, 0x00);
  SDL_RenderClear(WindowRenderer::GetInstance()->GetRenderer());
}

void Graphics::Update(float )
{
  DrawTextBoxes();
  DrawRegisters();
}

void Graphics::EndFrame()
{
  SDL_RenderPresent(WindowRenderer::GetInstance()->GetRenderer());
}

void Graphics::DrawTextBoxes()
{
  SDL_SetRenderDrawColor(WindowRenderer::GetInstance()->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

  for (auto &box : obj::ScriptField::GetObjects()) {
    obj::ScriptField *obj = box.get();
    SDL_Rect draw_rect;

    draw_rect.x = obj->mPositionX;
    draw_rect.y = obj->mPositionY;
    draw_rect.w = obj->mSizeX;
    draw_rect.h = obj->mSizeY;

    SDL_SetRenderDrawBlendMode(WindowRenderer::GetInstance()->GetRenderer(), SDL_BLENDMODE_ADD);
    if (SDL_RenderDrawRect(WindowRenderer::GetInstance()->GetRenderer(), &draw_rect) != 0) {
      SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Unable to render a textbox");
    }

      // Render each line of text
      // TODO: Batch calls, make more efficient
    SDL_Color text_color = { 0xFF, 0xFF, 0xFF };
    const std::string &text = obj->GetText();
      
      // Skip if theres no text
    if (text.empty())
      continue;

    size_t current_pos = 0;
    int current_line = 0;
    size_t end_of_line_pos = text.find_first_of('\n', 0);

    while (current_pos != std::string::npos) {
      SDL_Surface *text_surface = TTF_RenderText_Blended(mFont, text.substr(current_pos, end_of_line_pos - current_pos).c_str(), text_color);
      SDL_SetSurfaceBlendMode(text_surface, SDL_BLENDMODE_BLEND);

      SDL_Texture *text_texture = SDL_CreateTextureFromSurface(WindowRenderer::GetInstance()->GetRenderer(), text_surface);
      SDL_SetTextureBlendMode(text_texture, SDL_BLENDMODE_BLEND);

      int tex_w = 0;
      int tex_h = 0;
      SDL_QueryTexture(text_texture, NULL, NULL, &tex_w, &tex_h);
      SDL_Rect dest_rect = { obj->mPositionX + 10, obj->mPositionY + 10 + (tex_h * current_line), tex_w, tex_h };
      
      SDL_RenderCopy(WindowRenderer::GetInstance()->GetRenderer(), text_texture, NULL, &dest_rect);

      SDL_FreeSurface(text_surface);
      SDL_DestroyTexture(text_texture);

      if (end_of_line_pos == std::string::npos)
        break;

      current_pos = end_of_line_pos + 1;
      end_of_line_pos = text.find_first_of('\n', current_pos);
      ++current_line;
    }
  }
}

void Graphics::DrawRegisters()
{
  for (auto &box : obj::Register::GetObjects()) {
    obj::Register *obj = box.get();
    SDL_Rect draw_rect;

    draw_rect.x = obj->mPositionX;
    draw_rect.y = obj->mPositionY;
    draw_rect.w = obj->mSizeX;
    draw_rect.h = obj->mSizeY;

    if (SDL_RenderDrawRect(WindowRenderer::GetInstance()->GetRenderer(), &draw_rect) != 0) {
      SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Unable to render a register");
    }

      // Render Text
    SDL_Color text_color = { 0xFF, 0xFF, 0xFF };

    SDL_Surface *text_surface = TTF_RenderText_Blended(mFont, std::to_string(obj->GetValue()).c_str(), text_color);
    SDL_SetSurfaceBlendMode(text_surface, SDL_BLENDMODE_BLEND);

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(WindowRenderer::GetInstance()->GetRenderer(), text_surface);
    SDL_SetTextureBlendMode(text_texture, SDL_BLENDMODE_BLEND);

    int tex_w = 0;
    int tex_h = 0;
    SDL_QueryTexture(text_texture, NULL, NULL, &tex_w, &tex_h);
    SDL_Rect dest_rect = { obj->mPositionX + 10, obj->mPositionY + 10, tex_w, tex_h };

    SDL_RenderCopy(WindowRenderer::GetInstance()->GetRenderer(), text_texture, NULL, &dest_rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

  }
}
}