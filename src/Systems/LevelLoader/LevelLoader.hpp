#pragma once
#include "Systems/System.hpp"

namespace CayleeEngine
{
class LevelLoader : public System
{
public:
  LevelLoader();
  ~LevelLoader();

  void StartFrame();
  void Update(float dt);
  void EndFrame();

private:
  
};
}