# VM Translator

## Overview

This project is a Virtual Machine (VM) translator that converts stack machine bytecode into Hack assembly language. It is created as part of the "Nand to Tetris" course, specifically for the second part of the course.

## Author

Eloi Dieme

## Features

- Translates VM commands into Hack assembly language.
- Supports arithmetic operations, push/pop commands, function calls, and more.
- Writes the corresponding Hack assembly code to an output file.

## Usage

### Compilation

To compile the project, ensure you have a C compiler installed. Use the following command to compile the source code:

```sh
make
```

### Running the translator

To run the VM translator, run the following command:

```sh
./bin/prog ./vms/input.vm ./asms/output.asm
```

### Example

```sh
./bin/prog ./vms/BasicTest.vm ./asms/BasicTest.asm
```
