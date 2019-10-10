#pragma once

namespace uti
{
template <typename T>
class unique_vector
{
public:
  unique_vector() = default;
  ~unique_vector() = default;

  void push_back(const T &data);
  void pop_back();

  std::vector<std::unique_ptr<T>> vec;
};
}
#include "UniqueVector.inl"