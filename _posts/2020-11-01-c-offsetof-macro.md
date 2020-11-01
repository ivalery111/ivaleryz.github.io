---
layout: post
title: "offsetof C macro"
categories: c
published: true
---

## offsetof macro in C

Assume We have the following structure:
```c
struct human {
  char name[14];
  uinsigned age;
  unsigned id;
};
```

Expected memory footprint of human structure is:

| Field       | Size     | Offset     |
| :------------- | :----------: | -----------: |
| name  | 14 | 0  |
| age   | 4  | 14 |
| id    | 4  | 18 |

But this suggestion is incorrect because of padding. The padding is not a goal of this note, please google it :)  
The correct version of human structure is:

```c
struct human {
  char name[14];
  /* padding 2 bytes */
  uinsigned age;
  unsigned id;
};
```

so let's correct the table:  

| Field       | Size     | Offset     |
| :------------- | :----------: | -----------: |
| name  | 14 + 2 | 0  |
| age   | 4      | 16 |
| id    | 4      | 20 |

The macro of getting the field offset is:

```c
#define offsetof(struct_name, field_name) \
  (size_t) &((struct_name *)0)->field_name
```

### Usage  
```c
printf("offsetof(struct human, name) -> %ld\n", offsetof(struct human, name));
printf("offsetof(struct human, age)  -> %ld\n", offsetof(struct human, age));
printf("offsetof(struct human, id)   -> %ld\n", offsetof(struct human, id));
```

It's all :)
