#include "precompiled.hpp"
#include "Core/Core.hpp"

using namespace CayleeEngine;
int main(int , char* [])
{
  AllocConsole();
  freopen("CONOUT$", "w", stdout);
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

  Core core;

  core.InitializeSystems();
  core.Run();
  core.Shutdown();
  
  return 0;
}
