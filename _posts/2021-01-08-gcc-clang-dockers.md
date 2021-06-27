---
layout: post
title: "Использование GCC/Clang Docker в разработке"
tags: misc
published: true
---
При разработке полезно иметь возможность компилировать программу разными компиляторами под разными санитайзерами. Автоматизировать это можно при помощи CI Github Actions или Gitlab или чего-то другого.([Пример](https://github.com/ivaleryz/rpc-in-c/tree/main/.github/workflows) одного из моих проектов с использованием Github Action).  

В данной заметке опишу использование Gcc/Clang контейнеров для этой цели.

Дано: Проект который собирается cmake и имеет следующие флаги:
* ENABLE_SANITIZER_ADDRESS            - addres sanitizer
* ENABLE_SANITIZER_MEMORY             - memory sanitizer
* ENABLE_SANITIZER_UNDEFINED_BEHAVIOR - undefined behavior sanitizer
* ENABLE_SANITIZER_THREAD             - thread sanitizer

Так как у разных компиляторов разные санитайзеры, то будем использовать следующие docker контейнеры:
* [GCC 10](https://hub.docker.com/r/conanio/gcc10)
* [CLANG 11](https://hub.docker.com/r/conanio/clang11)

Далее запускаем контейнеры с опцией общей директории:
```bash

# Запускаем контейнер с GCC 10
docker run -it -v $(pwd):/home/conan/project --rm conanio/gcc10 /bin/bash

# Запускаем контейнер с Clang 10
docker run -it -v $(pwd):/home/conan/project --rm conanio/gcc11 /bin/bash

```  
* $(pwd) - каталог с проектом который нужно запустить.

Всё что нам осталось это выполнить команду в одном из контейнеров, например в GCC 10:
```bash
# Собираем проект с включеным addres sanitizer
cmake -B build -DENABLE_SANITIZER_ADDRESS=TRUE
```  

#### Полезные ссылки:
[How to use Docker to create and cross-build C and C++ Conan packages](https://docs.conan.io/en/latest/howtos/run_conan_in_docker.html?highlight=docker)  

