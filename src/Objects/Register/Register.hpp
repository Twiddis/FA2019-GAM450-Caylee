#pragma once
#include "Objects/Object.hpp"


namespace CayleeEngine::obj
{

class Register : public ObjectBase<Register>
{
public:
  explicit Register(std::string name);
  ~Register();

  void SetValue(int value) { mValue = value; }
  int GetValue() const { return mValue; }

private:
  std::string mName;
  int mValue;
};

}