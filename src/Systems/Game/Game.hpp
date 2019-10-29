#pragma once
#include "Systems/System.hpp"
#include "Objects/Object.hpp"
#include "Objects/ScriptField/ScriptField.hpp"
#include "Objects/Register/Register.hpp"

namespace CayleeEngine
{
class Game : public System
{
public:
  Game();
  ~Game();

  void StartFrame();
  void Update(float dt);
  void EndFrame();

private:
  obj::ScriptField *mScriptField;
  obj::Register *mACC;
  obj::Register *mDATA;

  void Build();

  bool mIsBuilt;
};
}