---
layout: post
title: "Draft: Bi-Direction pipe with socketpair"
tags: misc
published: true
---
## Intro
Hello fr13nd,  
In this post I want to share with how to debug the Linux Kernel with GDB.  

Steps:  
* Linux Kernel Compilation
* QEMU Running
* GDB Running

## Linux Kernel Compilation
The Linux Kernel source can be obtain in official site [kernel.org](https://www.kernel.org/). Download latest release.  
In order to let to the user to debug the kernel, you need to setup coresponding settings. Let's do it :)  

In linux kernel's folder, do:
```bash
$make menuconfig
```

In pseudo-GUI, enable :  
`Kernel hacking`-> `Compile the kernel with debug info`  
`Kernel hacking`-> `Provide GDB scripts for kernel debugging`  
Exit and save it.  

Compile the kernel: `make -j $nproc`
