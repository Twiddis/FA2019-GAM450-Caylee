#include "precompiled.hpp"
#include "Register.hpp"

namespace CayleeEngine::obj
{
Register::Register(std::string name) : mName(name), mValue(0)
{
}

Register::~Register()
{
}

}