---
layout: post
title: "Lazy value initialization in C++"
tags: cpp
published: true
---
## The Problem
Sometimes in practice, there are objects that their creation is expensive. In this case, the logical solution is to do the "lazy" initialization. It means, to do the initialization when it needed.  
For example, there is an object that connecting to DB. Assume that connection is an expensive operation. So, We want to connect to DB only when We needed that and not when the program started.

## How to do it?
### Interface:
```cpp
// LazyInit.h
1. template <typename T> class LazyInit {
2. public:
3.   explicit LazyInit(function<T()> init);
4.
5.   bool HasValue() const;
6.   const T& Get() const;
7. private:
8.   function<T()> init_;
9.   mutable optional<T> value_;
10.};
```
Line 3: Constructor gets the initialization function which will be invoked in first call of `Get` method.  
Line 5: Method `HasValue` returns `true` if the object was initialized, which means method `Get` was invoked a minimum of one time.  
Line 6: Method `Get` responsible to initialize the object. 
Line 8: Private member to store the initialized function.  
Line 9: Private member to store the value. Make it `optional` allow us to verify if the value was initialized or not. (nice option :) ) `Mutable` allow us to set this variable in `const` method.
### Implementation:
{  
Using of benefits of `optional` type. With `optional`'s `has_value()` method verify if the value was initialized.
```cpp
// LazyInit.h
template <typename T> 
bool LazyInit<T>::HasValue() const {
  return value_.has_value();
}
```
}  
{  
This snippet is more interesting. The method `Get` defined as `const`, but, since the `value_` defined as `mutable` We can change this variable in `const` method.  
Remove `const` is BAD idea. `const` protecting us from random changes. When We set variable as `mutable` We know what We are doing (I hope :) ), We have control on changes, so, should use `mutable` instead of removing `const`.
```cpp
// LazyInit.h
template <typename T>
const T& LazyInit<T>::Get() const{
  if(!value_){
    value_ = init_();
  }
  return *value_;
}
```
}
---
## References:
* [Code + Tests](https://github.com/ivalery111/ivaleryz.github.io/tree/master/code/2021/02/27/LazyInit)
