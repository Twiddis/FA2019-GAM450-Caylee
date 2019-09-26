#include "precompiled.hpp"

#include "Singletons/DFA/DFA.hpp"

using namespace CayleeEngine;
int main(int , char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  DFA::Initialize();


    // TEMP
  std::ifstream file(argv[1]);

  file.seekg(0, file.end);
  size_t len = static_cast<size_t>(file.tellg());
  file.seekg(0, file.beg);
  
  char *block = new char[len];
  file.read(block, len);
  file.close();
  block[len - 1] = '\0';

  std::vector<Token> token_stream;
  DFA::GetInstance()->Tokenize(block, token_stream);
	
  for (auto &token : token_stream)
    std::cout << token << std::endl;
  ////////////////////////////
  
  system("pause");

  return 0;
}
