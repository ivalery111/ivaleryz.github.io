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
Line 9: Private member to store the value. Make it `optional` allow us to verify if the value was initialized or not. (nice option :) )
