---
layout: post
title: "Lazy value initialization in C++"
tags: cpp
published: true
---

## The Problem
Sometimes in practice, there are objects that their creation is expensive. In this case, the logical solution is to do the "lazy" initialization. It means, to do the initialization when it needed.  
For example, there is an object that connecting to DB. Assume that connection is an expensive operation. So, We want to connect to DB only when We needed that and not when the program started.
