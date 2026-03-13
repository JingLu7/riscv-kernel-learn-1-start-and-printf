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

# 5 Makefile

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
