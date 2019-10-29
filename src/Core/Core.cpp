#include "precompiled.hpp"
#include "Core.hpp"

namespace CayleeEngine
{
  void Core::InitializeSystems()
  {
    StartSystem<Input>();
    StartSystem<Graphics>();
    StartSystem<Game>();
  }

void Core::Run()
{
  bool is_running = true;
  while (is_running) {
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