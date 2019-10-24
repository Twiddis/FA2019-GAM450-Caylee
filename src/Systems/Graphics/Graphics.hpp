#include "Systems/System.hpp"
#include "Resources/Sprite/Sprite.hpp"
namespace CayleeEngine
{
class Graphics : public System
{
public:
  Graphics();
  ~Graphics();

  void StartFrame();
  void Update(float dt);
  void EndFrame();

private:
  res::Sprite::Key mTest;
};
}