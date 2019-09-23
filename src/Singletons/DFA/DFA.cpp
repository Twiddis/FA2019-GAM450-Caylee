#include "precompiled.hpp"
#include "DFA.hpp"

namespace CayleeEngine
{
  DFA::DFA()
  {
    // Initialize by creating the state machine
  }
  bool DFA::Tokenize(const std::string &block)
  {

  }

  DFA::State* DFA::AddState(TokenType::Enum accepting_token)
  {
    State *new_state = new State;

    new_state->mDefaultEdge = nullptr;
    new_state->mAcceptingToken = accepting_token;
  }

  void DFA::AddEdge(State *from, State *to, char c)
  {
    from->mEdges.emplace(c, to);
  }

  void DFA::AddDefaultEdge(State *from, State *to)
  {
    from->mDefaultEdge = to;
  }
}