#pragma once
namespace CayleeEngine::obj
{
class ObjectInterface
{
public:
  ObjectInterface() : mPositionX(0), mPositionY(0), mSizeX(0), mSizeY(0) {};
  virtual ~ObjectInterface() {};

  int mPositionX, mPositionY;
  int mSizeX, mSizeY;
};

template <typename T>
class ObjectBase : public ObjectInterface
{
public:
  ObjectBase();
  virtual ~ObjectBase();

  template <typename... Args>
  inline static ObjectBase* Create(Args&&...args);

  static std::vector<std::unique_ptr<T>>&
    GetObjects() { return sObjects; }

protected:
  inline static T* Get(int index);
  static std::vector<std::unique_ptr<T>> sObjects;

private:
};

} // CayleeEngine::obj

#include "Object.inl"