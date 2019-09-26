#include "precompiled.hpp"
#include "DFA.hpp"

namespace CayleeEngine
{
  DFA::DFA()
  {
      // Initialize by creating the state machine
      // Create root node
    mRootState = new State;
    
      // Identifiers (Names)
    {
      State *label_state = AddState(TokenType::LabelName);
      State *register_state = AddState(TokenType::RegisterName);

        // Identifiers start with an alphabetic character or underscore [A-z], _
      for (char c = 'A'; c <= 'Z'; ++c)
        AddEdge(mRootState, register_state, c);
      for (char c = 'a'; c <= 'z'; ++c)
        AddEdge(mRootState, register_state, c);

      AddEdge(mRootState, register_state, '_');

        // Identifiers are alphanumeric or underscore. [A-z], [0-9], _
      for (char c = 'A'; c <= 'Z'; ++c)
        AddEdge(register_state, register_state, c);
      for (char c = 'a'; c <= 'z'; ++c)
        AddEdge(register_state, register_state, c);
      for (char c = '0'; c <= '9'; ++c)
        AddEdge(register_state, register_state, c);

      AddEdge(register_state, register_state, '_');
      
        // If there's a colon at the end, it's a label
      AddEdge(register_state, label_state, ':');
     }

      // Literal (The only literal possible in our instruction set is an int)
    {
      State *literal_state = AddState(TokenType::Literal);

      for (char c = '0'; c <= '9'; ++c)
        AddEdge(mRootState, literal_state, c);

      for (char c = '0'; c <= '9'; ++c)
        AddEdge(literal_state, literal_state, c);
    }

      // Whitespace includes tabs and spaces
    {
      State *whitespace_state = AddState(TokenType::Whitespace);

      AddEdge(mRootState, whitespace_state, ' ');
      AddEdge(mRootState, whitespace_state, 9); // Tab
      AddEdge(whitespace_state, whitespace_state, ' ');
      AddEdge(whitespace_state, whitespace_state, 9); // Tab
    }

      // Comments start with a #, and end with a newline
    {
      State *comment_state = AddState(TokenType::Comment);

      const char start = ' ';
      const char end = '~';

      AddEdge(mRootState, comment_state, '#');

      for (char c = start; c <= end; ++c)
        AddEdge(comment_state, comment_state, c);
    }


  }

  DFA::~DFA()
  {
    // Destruct the state machine nodes
  }

  bool DFA::Tokenize(const char *block, std::vector<Token> &token_stream)
  {
    while (*block != '\0')
    {
      
    }
  }

  DFA::State* DFA::AddState(TokenType::Enum accepting_token)
  {
    State *new_state = new State;

    new_state->mDefaultEdge = nullptr;
    new_state->mAcceptingToken = accepting_token;
  }

  void DFA::AddEdge(State *from, State *to, char c)
  {
    #ifdef _DEBUG
    if (from->mEdges.find(c) != from->mEdges.end())
      std::cout << "DFA Error! Duplicate Edge!" << std::endl;
    #endif

    from->mEdges.emplace(c, to);
  }

  void DFA::AddDefaultEdge(State *from, State *to)
  {
    from->mDefaultEdge = to;
  }

}