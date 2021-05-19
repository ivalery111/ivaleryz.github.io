---
layout: post
title: "Draft: Bi-Direction pipe with socketpair"
tags: misc
published: true
---

If you need bi-directional pipe, you can use `socketpair` system call.

Let's see the example.  
There is the application that reading the string from a `stdin`, add `hello` word to the beggining and writing in to the `stdout`.
```c
/* say_hello.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char buffer[128];
  char result[256];
  ssize_t bytes = 0;

  if (read(STDIN_FILENO, buffer, 128) == (-1)) {
    perror("read: ");
    exit(EXIT_FAILURE);
  }
  snprintf(result, 256, "%s %s\n", "hello", buffer);

  if (write(STDOUT_FILENO, result, strlen(result)) == (-1)) {
    perror("write: ");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

```  

Now, there is another application that would to use the `say_hello` application. We will use `socketpair` for creaing bidirectional communication.
```c
/* main.c */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  int socks[2]; /* The pair of sockets */
  char buffer[512];

  if (socketpair(AF_UNIX, SOCK_STREAM, 0, socks) == (-1)) {
    perror("socketpair: ");
    exit(EXIT_FAILURE);
  }

  if (!fork()) { /* Child */
    /* Redirect the child's stdin/stdout to socket */
    dup2(socks[1], STDIN_FILENO);
    dup2(socks[1], STDOUT_FILENO);

    execve("./hello", NULL, NULL);
    exit(0);
  } else {
    write(socks[0], "zzz", 3);
    read(socks[0], buffer, 512);

    printf("buffer -> %s\n", buffer);
  }
}

```
