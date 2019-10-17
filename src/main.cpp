#include "precompiled.hpp"


#include "stb/stb_image.h"

#include "Core/Core.hpp"



using namespace CayleeEngine;
int main(int , char* [])
{
  AllocConsole();
  freopen("CONOUT$", "w", stdout);

  Core core;

  core.InitializeSystems();
  core.Run();
  core.Shutdown();
  
  return 0;
}
