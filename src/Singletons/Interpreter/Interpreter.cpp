#include "precompiled.hpp"
#include "Interpreter.hpp"

#include "Singletons/Parser/SyntaxNodes.hpp"

namespace CayleeEngine
{
Interpreter::Interpreter() { }
Interpreter::~Interpreter() { }

void Interpreter::SetInstructions(const std::vector<std::unique_ptr<SyntaxNode>>&  )
{
}

void Interpreter::ExecuteNext()
{
}




}