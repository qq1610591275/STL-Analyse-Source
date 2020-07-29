#ifndef _MYALGORITHM
#define _MYALGORITHM
template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value)
{
  while(first != last && *first!= value)  {
      ++first;
      return first;
  }
}

template <class InputIterator, class Function>
InputIterator for_each(InputIterator first,InputIterator last,Function f){
    for(;first != last; first++)
        f(*first);
    return first;
}

#endif