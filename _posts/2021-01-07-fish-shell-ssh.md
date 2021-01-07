---
layout: post
title: "fish shell и ssh"
tags: misc
published: true
---

Понадобилось настроить доступ к github по ssh используя fish shell. Так как синтаксис fish shell'а несовместим с bash, то и команды нужно изменить :(  

Решение:
```bash
$eval (ssh-agent -c)
> Agent pid XXXX

$ssh-add /path/to/your/ssh/file
```  
