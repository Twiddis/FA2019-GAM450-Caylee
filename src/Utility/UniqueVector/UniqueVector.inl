namespace uti
{
template<typename T>
inline void unique_vector<T>::push_back(const T & data)
{
  vec.push_back(std::make_unique<T>(data));
}

template<typename T>
inline void unique_vector<T>::pop_back()
{
  vec.pop_back();
}
}