#pragma once
#include "Systems/System.hpp"

namespace CayleeEngine
{
class Input : public System
{
public:
  Input();
  ~Input();

  void StartFrame();
  void Update(float dt);
  void EndFrame();

private:

};
}