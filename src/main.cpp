#include "precompiled.hpp"

#include "Singletons/DFA/DFA.hpp"
#include "Singletons/Parser/Parser.hpp"

using namespace CayleeEngine;
int main(int argc, char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  AllocConsole();
  freopen("CONOUT$", "w", stdout);

  DFA::Initialize();
  Parser::Initialize();

  // TEMPORARY
  ///////////////////////////////////////
  if (argc != 2)
    return 0;

  std::ifstream file(argv[1], std::ios::binary);

  file.seekg(0, file.end);
  size_t len = static_cast<size_t>(file.tellg());
  file.seekg(0, file.beg);
  
  char *block = new char[len + 1];
  file.read(block, len);
  file.close();
  block[len] = '\0';

  std::vector<Token> token_stream;
  DFA::GetInstance()->Tokenize(block, token_stream);
	
  for (auto &token : token_stream)
    std::cout << token << std::endl;

  delete[] block;
  system("pause");
  ////////////////////////////


  return 0;
}
