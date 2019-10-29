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
  TTF_Font *mFont;
  void DrawTextBoxes();
  void DrawRegisters();
};
}