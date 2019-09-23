#pragma once
#include "Singletons/Singleton.hpp"
#include "Tokens.hpp"

namespace CayleeEngine
{

class Parser : public Singleton<Parser>
{
public:
  Parser();
  bool Validate(const std::string &block);
  
private:

};

}