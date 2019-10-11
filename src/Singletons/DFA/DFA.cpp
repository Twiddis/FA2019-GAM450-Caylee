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

      // Symbols 
    for (size_t i = TokenType::_SymbolStart + 1; i < TokenType::_KeywordStart; ++i) {
      State *symbol_state = AddState(static_cast<TokenType::Enum>(i));
      AddEdge(mRootState, symbol_state, *Token::gTokenNames[i]);
    }

      // Initialize Keyword Map
    for (size_t i = TokenType::_KeywordStart + 1; i < TokenType::_End; ++i) {
      mKeywordMap.emplace(Token::gTokenNames[i], 
                          Token(Token::gTokenNames[i], 
                                std::strlen(Token::gTokenNames[i]), 
                                static_cast<TokenType::Enum>(i)));
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
      const char *start = block;
      const char *end = block;

      const State *state = mRootState;
      const State *last_accepted = state;

      while (*block != '\0') {
        auto pair = state->mEdges.find(*block);
        
          // Found Edge
        if (pair != state->mEdges.end())
          state = pair->second;

          // If Default Edge Exists
        else if (state->mDefaultEdge)
          state = state->mDefaultEdge;

          // No Edge
        else break;

          // Save if state is accepted
        if (state->mAcceptingToken != TokenType::Invalid) {
          last_accepted = state;
          end = block;
        }

        ++block;
      }

        // No accepting state was found
      if (last_accepted == mRootState)
        return false;

        // If name, it might be a keyword
      if (last_accepted->mAcceptingToken == TokenType::RegisterName) {
        std::string find(start, end - start + 1);
        auto keyword_pair = mKeywordMap.find(find);

          // If it is, add the keyword token, otherwise, just add the token as a name
        if (keyword_pair != mKeywordMap.end())
          token_stream.push_back(keyword_pair->second);
        else
          token_stream.push_back(Token(start, end - start + 1, last_accepted->mAcceptingToken));
      }

        // If it is a return carriage, get it the fuck outta here (dont do anything)
      else if (last_accepted->mAcceptingToken == TokenType::ReturnCarriage)
        (void) 0;
        // If it is a whitespace, get it the fuck outta here (dont do anything)
      else if (last_accepted->mAcceptingToken == TokenType::Whitespace)
        (void) 0;

        // If not a name, just add it as whatever it is.
      else
        token_stream.push_back(Token(start, end - start + 1, last_accepted->mAcceptingToken));

      block = end + 1;
    }

      // Special end of file token
    token_stream.push_back(Token(block, 0, TokenType::EndOfFile));

    return true;
  }

  DFA::State* DFA::AddState(TokenType::Enum accepting_token)
  {
    State *new_state = new State;

    new_state->mDefaultEdge = nullptr;
    new_state->mAcceptingToken = accepting_token;

    return new_state;
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

  void DFA::DestroyNodes(State *)
  {

  }

  Token DFA::TokenizeKeyword(const char *start, size_t length)
  {
    return mKeywordMap.find(std::string(start, length))->second;
  }

}