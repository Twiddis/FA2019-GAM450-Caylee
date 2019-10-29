#pragma once
#include "Objects/Object.hpp"


namespace CayleeEngine::obj
{

class ScriptField : public ObjectBase<ScriptField>
{
public:
  ScriptField();
  ~ScriptField();

  void AddCharacter(char c) { mText.insert(mCursorIndex++, 1, c); }
  void DeleteCharacter() { if (mCursorIndex) mText.erase(--mCursorIndex, 1); }
  void SetCursorIndex(int i) { mCursorIndex = i; }

  void SetFocus(bool b = true) { mIsInFocus = b; }

  const std::string& GetText() const { return mText; }

private:
  bool mIsInFocus;
  int mCursorIndex;

  std::string mText;
};

}