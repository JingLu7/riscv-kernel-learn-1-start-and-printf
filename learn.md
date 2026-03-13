# 1 启动篇

    目标：启动一个简易的可以打印字符串的内核
    原理：通过entry进入c函数后 调用uart向uart传入字符串 然后进入死循环 其中uart输出的内容会被qemu捕获并返回到终端

## 1 entry篇

    entry的目的很明确 就是在cpu通电后给一个栈地址（在.bss区域）然后跳转到c函数中

## 2 ld篇

    规定编译后的elf文件的排列顺序 分别有.text区域 .rodata区域 .data 区域 .bss区域 存放的内容分别为 可执行代码 常量 变量 未初始化变量 还有就是明确第一行代码 比如 ENTRY(_start)就是把entry中_start下定义的汇编代码放在elf文件的最前面

## 3 c文件篇
    
    这次的学习目标是启动一个最简单的内核并在终端打印字符串 所以涉及到的函数主要为uart的相关交互 
    uart的内存地址为 0x10000000（读写数据的地方）0x10000005为uart的状态地址 因为这个地方存有8bit 而需要检查的地址为第五位 所以用0x20（十六进制 二进制位 0010 0000）去做&运算判断

## 4 makefile篇

    makefile的编写很简单 先把一些可以用到的重复性工具做一个简单的定义 然后去定义一些命令 比如all clean qemu等
    其中的格式为：
    标签：依赖文件
        执行指令
    如果依赖文件没找到就会顺位往下找 去递归


# 1 Boot
## Goal

Boot a minimal RISC-V kernel and print a string to the terminal.

## Principle

The kernel enters a C function through the entry assembly code.
Inside the C function, we use UART to send characters to the serial port.

The output from UART is captured by QEMU and displayed in the host terminal.

# 2 Entry

The purpose of entry is straightforward.

After the CPU starts, it:

1. Initializes a stack pointer (located in the .bss section)

2. Jumps to the C kernel function

This step prepares the runtime environment required by C code.

# 3 Linker Script (ld)

The linker script defines the layout of the final ELF binary.

The sections include:

```
.text    executable code
.rodata  read-only constants
.data    initialized variables
.bss     uninitialized variables
```

It also specifies the program entry point.

For example:

```
ENTRY(_start)
```

This ensures that the _start symbol defined in entry.S becomes the first instruction executed in the ELF file.

# 4 C Code

The goal of this project is to boot a minimal kernel and print a string.

Therefore, the main functionality implemented in C is the interaction with the UART device.

UART memory-mapped addresses:

```
0x10000000  UART data register
0x10000005  UART status register
```

The status register contains 8 bits, and the fifth bit indicates whether the UART is ready.

We check this bit using a bitwise AND operation:

```
0x20  (binary: 0010 0000)
```

If the bit is set, the UART is ready to send data.

#5 Makefile

The Makefile is relatively simple.

First, we define reusable tools and variables.

Then we define targets such as:

```
all
clean
qemu
```

The general structure of a Makefile rule is:

```
target: dependencies
    command
```

If a dependency is missing, make will recursively search for rules to build it.

