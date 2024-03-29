#pragma once
#include "Systems/System.hpp"
#include "Systems/Graphics/Graphics.hpp"
#include "Systems/Game/Game.hpp"
#include "Systems/Input/Input.hpp"
namespace CayleeEngine
{
class Core
{
public:
  Core() = default;
  ~Core() = default;
  
  template <typename T>
  inline void StartSystem();

  void InitializeSystems();
  void Run();
  void Shutdown();

private:
  std::vector<std::unique_ptr<System>> mSystems;
};


template <typename T>
inline void Core::StartSystem()
{
  static_assert(std::is_base_of<System, T>::value, 
                "ERROR: Attempted add something other than a system into Core\n");

  mSystems.push_back(std::move(std::make_unique<T>()));
  mSystems.back()->Enable();
}

} 