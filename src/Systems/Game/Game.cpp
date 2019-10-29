#include "precompiled.hpp"
#include "Game.hpp"

#include "Singletons/Keyboard/Keyboard.hpp"
#include "Singletons/DFA/DFA.hpp"
#include "Singletons/Parser/Parser.hpp"
#include "Singletons/Interpreter/Interpreter.hpp"

namespace CayleeEngine
{
Game::Game() : mScriptField(nullptr), mACC(nullptr), mDATA(nullptr), mIsBuilt(false)
{
  DFA::GetInstance()->Initialize();
  Parser::GetInstance()->Initialize();
  Interpreter::GetInstance()->Initialize();

  mScriptField = static_cast<obj::ScriptField*>(obj::ScriptField::Create());
  mScriptField->mPositionX = 100;
  mScriptField->mPositionY = 100;
  mScriptField->mSizeX = 700;
  mScriptField->mSizeY = 800;

  mACC = static_cast<obj::Register*>(obj::Register::Create("ACC"));
  mACC->mPositionX = 1000;
  mACC->mPositionY = 100;
  mACC->mSizeX = 100;
  mACC->mSizeY = 100;

  mDATA = static_cast<obj::Register*>(obj::Register::Create("DATA"));
  mDATA->mPositionX = 1000;
  mDATA->mPositionY = 200;
  mDATA->mSizeX = 100;
  mDATA->mSizeY = 100;
}

Game::~Game()
{
  DFA::GetInstance()->Shutdown();
  Parser::GetInstance()->Shutdown();
  Interpreter::GetInstance()->Shutdown();
}

void Game::StartFrame()
{
  
}

void Game::Update(float )
{
    // Text Input
  for (size_t i = static_cast<size_t>(SDL_SCANCODE_A); i < SDL_NUM_SCANCODES; ++i) {
    if (Keyboard::GetInstance()->IsKeyPressed(static_cast<SDL_Scancode>(i)))
    {
        // Alphabet Characters
      if (i >= SDL_SCANCODE_A && i <= SDL_SCANCODE_Z)
        mScriptField->AddCharacter(static_cast<char>(i - SDL_SCANCODE_A) + 'A');

      // Numerical Characters
      else if (i >= SDL_SCANCODE_1 && i <= SDL_SCANCODE_0) {
        if (i == SDL_SCANCODE_0)
          mScriptField->AddCharacter('0');
        else
          mScriptField->AddCharacter(static_cast<char>(i - SDL_SCANCODE_1) + '1');
      }

      // Other
      else if (i == SDL_SCANCODE_MINUS) {
        if (Keyboard::GetInstance()->IsKeyDown(SDL_SCANCODE_LSHIFT) ||
          Keyboard::GetInstance()->IsKeyDown(SDL_SCANCODE_RSHIFT))
        {
          mScriptField->AddCharacter('_');
        }
        else
        {
          mScriptField->AddCharacter('-');
        }
      }
      else if (i == SDL_SCANCODE_SEMICOLON) {
        if (Keyboard::GetInstance()->IsKeyDown(SDL_SCANCODE_LSHIFT) ||
          Keyboard::GetInstance()->IsKeyDown(SDL_SCANCODE_RSHIFT))
        {
          mScriptField->AddCharacter(':');
        }

      }

      else if (i == SDL_SCANCODE_RETURN)
        mScriptField->AddCharacter('\n');
      else if (i == SDL_SCANCODE_BACKSPACE)
        mScriptField->DeleteCharacter();
      else if (i == SDL_SCANCODE_SPACE)
        mScriptField->AddCharacter(' ');

      else if (i == SDL_SCANCODE_F4)
        Build();
      else if (i == SDL_SCANCODE_F5)
        Interpreter::GetInstance()->ExecuteNext();
      else if (i == SDL_SCANCODE_F8)
      {
        PrintVisitor printer;

        Parser::GetInstance()->Walk(&printer);
      }
    } 
  }
}
void Game::EndFrame()
{
}
void Game::Build()
{
  std::vector<Token> token_stream;
  DFA::GetInstance()->Tokenize(mScriptField->GetText().c_str(), token_stream);
  Parser::GetInstance()->Parse(token_stream);

  mACC->SetValue(0);
  mDATA->SetValue(0);

  Interpreter::GetInstance()->SetInstructions(Parser::GetInstance()->GetInstructions());
  Interpreter::GetInstance()->AddRegister("ACC", mACC);
  Interpreter::GetInstance()->AddRegister("DATA", mDATA);
}
}