#pragma once
#include "Singletons/Singleton.hpp"

namespace CayleeEngine
{
class Parser : public Singleton<Parser>
{
public:

  bool Validate(const std::string &block);

private:

};

}