#include "Systems/System.hpp"

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
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;

};
}