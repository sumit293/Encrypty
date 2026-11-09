# Encrypty

A modular **C++ file encryption and decryption system** designed to demonstrate secure file processing, serialization/deserialization, modular architecture, and modern C++ memory-management practices.

## Overview

**Encrypty** takes an input file, processes it through the file I/O and configuration layers, and performs encryption or decryption before producing the resulting output.

The project focuses not only on encryption/decryption, but also on writing a clean C++ system with:

- Modular separation of responsibilities
- File handling using C++ streams
- Serialization and deserialization
- Efficient data passing using references
- Resource management using smart pointers such as `std::unique_ptr`
- Makefile-based compilation
- GDB debugging through VS Code

## Project Flow

```text
                   ┌─────────────────┐
                   │      User       │
                   │     Input       │
                   └────────┬────────┘
                            │
                            ▼
                   ┌─────────────────┐
                   │    Input File   │
                   │    File Data    │
                   └────────┬────────┘
                            │
                            ▼
                   ┌─────────────────┐
                   │     File I/O    │
                   │   Read / Write   │
                   └────────┬────────┘
                            │
                            ▼
                   ┌─────────────────┐
                   │ Configuration /  │
                   │   Environment   │
                   └────────┬────────┘
                            │
                            ▼
                    ┌────────────────┐
                    │ Encrypt or      │
                    │ Decrypt ?       │
                    └───────┬────────┘
                         │         │
                  Encrypt│         │Decrypt
                         ▼         ▼
                 ┌────────────┐ ┌────────────┐
                 │ Encryption │ │ Decryption │
                 │    Core    │ │    Core    │
                 └──────┬─────┘ └──────┬─────┘
                        │               │
                        └───────┬───────┘
                                ▼
                     ┌─────────────────────┐
                     │ Serialization /     │
                     │ Deserialization     │
                     └──────────┬──────────┘
                                │
                                ▼
                     ┌─────────────────────┐
                     │     Output File     │
                     └─────────────────────┘
```

## Architecture

The project is organized into separate components so that file handling, encryption/decryption, configuration, and application logic remain independent.

```text
Encrypty/
│
├── .vscode/
│   ├── launch.json
│   └── tasks.json
│
├── src/
│   └── app/
│       ├── processes/
│       ├── fileHandling/
│       └── encryptDecrypt/
│
├── test/
│
├── main.cpp
├── Makefile
└── README.md
```

### Main Components

**File Handling**

Responsible for opening, reading, writing, and managing file streams.

**Encryption / Decryption**

Contains the core processing logic responsible for transforming the input data and reversing the transformation during decryption.

**Process Management**

Coordinates different application-level operations and connects the individual modules.

**Configuration / Environment**

Handles configuration values required by the application.

**Serialization / Deserialization**

Provides a structured way to convert data into a form suitable for processing/storage and reconstruct it when required.

## Memory Management

One of the goals of the project is to use modern C++ memory-management techniques.

The project makes use of:

- References (`&`) to avoid unnecessary copying
- Smart pointers such as `std::unique_ptr`
- RAII-oriented resource management
- Efficient object ownership

This helps reduce unnecessary memory allocations and makes ownership of dynamically allocated resources explicit.

## Technologies

| Technology | Purpose |
|---|---|
| C++ | Core application |
| STL | Data structures and utilities |
| Make | Build automation |
| GDB | Debugging |
| VS Code | Development environment |


<img width="1894" height="1322" alt="image" src="https://github.com/user-attachments/assets/baa74123-3a3e-44de-ad09-e0934c1ed176" />


## Project Architecture

![Encrypty Project Flow](docs/encrypty-flow.png)

## Build

### Prerequisites

Make sure you have:

- A C++ compiler such as GCC/G++
- GNU Make
- GDB
- VS Code (optional)

Check the installations:

```bash
g++ --version
make --version
gdb --version
```

### Build the project

From the project root:

```bash
make
```

### Clean the build

```bash
make clean
```

## Running

After compilation, the generated executable can be run from the project directory.

For example:

```bash
./encrypt_decrypt
```

On Windows:

```powershell
.\encrypt_decrypt.exe
```

The exact arguments depend on the application's current command-line interface.

## Debugging

The repository contains VS Code debugging configuration under:

```text
.vscode/
├── launch.json
└── tasks.json
```

The build task uses:

```text
make
```

and the debugger is configured to use **GDB**.

This allows the project to be compiled and debugged directly from VS Code.

## Learning Goals

This project was built to explore practical C++ concepts including:

- Object-oriented programming
- File handling
- Memory management
- References
- Smart pointers
- Serialization
- Modular architecture
- Build systems
- Debugging with GDB
- Separation of responsibilities

## Security Note

This project is intended as a learning and systems-programming project.

Do **not** use it for protecting sensitive or production data without independently verifying the cryptographic algorithm, key management, randomness, authentication, and implementation security.

## Future Improvements

Possible improvements include:

- Add a documented cryptographic algorithm
- Improve command-line argument handling
- Add automated unit tests
- Add error-handling and validation
- Add benchmarks for large files
- Improve cross-platform build support
- Add CI/CD using GitHub Actions
- Add password/key management
- Add authenticated encryption and integrity verification

## Author

**Sumit Wani**

GitHub: [sumit293](https://github.com/sumit293)

---

### Project Repository

[Encrypty on GitHub](https://github.com/sumit293/Encrypty)
