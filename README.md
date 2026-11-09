# Mini C Preprocessor

A mini C preprocessor implemented in C. This project demonstrates basic preprocessing operations such as comment removal, header inclusion, and macro replacement.

## Features

- Removes single-line (`//`) and multi-line (`/* ... */`) comments.
- Handles standard header inclusion from `/usr/include/`.
- Handles user-defined header inclusion.
- Supports object-like macro replacement.
- Supports function-like macro replacement.
- Generates a preprocessed output file with the `.i` extension.

## Project Files

| File | Description |
|---|---|
| `main.c` | Main program and preprocessing flow |
| `header.h` | Function declarations and argument structure |
| `remove_comments.c` | Removes comments from source code |
| `header_inclusion.c` | Handles standard and user-defined header inclusion |
| `replace_macro.c` | Performs macro replacement |
| `Makefile` | Builds the project |

## Requirements

- GCC
- GNU Make
- Linux environment

## Compilation

Run the following command in the project directory:

```bash
make
```

This creates the executable:

```bash
my_preprocessor
```

## Usage

Run the preprocessor with a C source file:

```bash
./my_preprocessor inputfile.c
```

The preprocessed output will be generated as:

```text
inputfile.i
```

## Example

```bash
./my_preprocessor test.c
```

Output:

```text
File preprocessed successfully
```

## Clean Build Files

To remove object files and the executable:

```bash
make clean
```

## Limitations

This is an educational mini preprocessor. It supports basic preprocessing operations and is not a complete replacement for the standard C preprocessor (`cpp`).

## Author

Ramya Natakarani
