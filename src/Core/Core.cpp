#include "precompiled.hpp"
#include "Core.hpp"

namespace CayleeEngine
{
void Core::Run()
{
  while (true)
  {
    float dt = 0.016f;
    for (auto &sys : mSystems) {
      if (sys->IsEnabled())
        sys->StartFrame();
    }

    for (auto &sys : mSystems) {
      if (sys->IsEnabled())
        sys->Update(dt);
    }

    for (auto &sys : mSystems) {
      if (sys->IsEnabled())
        sys->EndFrame();
    }
  }
}

void Core::Shutdown()
{
  while (!mSystems.empty())
    mSystems.pop_back();
}
}