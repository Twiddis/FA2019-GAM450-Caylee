#include "Object.hpp"

namespace CayleeEngine::obj
{
template <typename T> std::vector<std::unique_ptr<T>>
  ObjectBase<T>::sObjects = std::vector<std::unique_ptr<T>>();

template <typename T>
inline ObjectBase<T>::ObjectBase() { }
template <typename T>
inline ObjectBase<T>::~ObjectBase() { }


template <typename T>
template <typename... Args>
inline ObjectBase<T>* ObjectBase<T>::Create(Args&&... args)
{
  sObjects.push_back(std::make_unique<T>(args...));
  return sObjects.back().get();
}

template <typename T>
inline T* ObjectBase<T>::Get(int index)
{
  return sObjects[index].get();
}
}