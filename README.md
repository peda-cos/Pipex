# Pipex

![Norminette](https://github.com/peda-cos/Pipex/workflows/norminette/badge.svg)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A 42 School project that recreates the behavior of shell pipe (`|`) mechanism in C, allowing the execution of two commands in a pipeline, redirecting input and output through files.

## 📋 Description

Pipex is a system programming project that mimics the shell pipeline functionality. It executes two commands sequentially, where the output of the first command serves as input to the second command, with file-based input and output redirection.

The program replicates this shell behavior:
```bash
< file1 cmd1 | cmd2 > file2
```

## 🚀 Technology Stack

- **Language**: C
- **Compiler**: cc (GCC/Clang compatible)
- **Build System**: Make
- **Coding Standard**: Norminette (42 School norm)
- **System APIs**:
  - Process management: `fork()`, `execve()`, `waitpid()`
  - File descriptors: `open()`, `close()`, `dup2()`
  - Inter-process communication: `pipe()`
  - File access: `access()`

## 🏗️ Project Architecture

The project follows a modular architecture with clear separation of concerns:

```
┌─────────────┐
│   main.c    │  ← Entry point & argument validation
└──────┬──────┘
       │
       ├──────→ ┌──────────────┐
       │        │  exec_utils  │  ← Process creation & execution
       │        └──────────────┘
       │
       ├──────→ ┌──────────────┐
       │        │  path_utils  │  ← Command path resolution
       │        └──────────────┘
       │
       └──────→ ┌──────────────┐
                │  str_utils   │  ← String manipulation utilities
                │  ft_split    │
                └──────────────┘
```

### Core Components:

1. **Main Module** (`main.c`): Handles argument parsing, file opening, and orchestrates the pipeline creation
2. **Execution Module** (`exec_utils.c`): Manages process forking, command execution, and pipe creation
3. **Path Resolution** (`path_utils.c`): Locates executable commands in the system PATH
4. **String Utilities** (`str_utils.c`, `ft_split.c`): Provides helper functions for string operations and command parsing

## 📁 Project Structure

```
Pipex/
├── main.c              # Entry point and file handling
├── exec_utils.c        # Process execution and pipe management
├── path_utils.c        # Command path resolution
├── str_utils.c         # String utility functions
├── ft_split.c          # String splitting implementation
├── pipex.h             # Header file with function prototypes
├── Makefile            # Build configuration
├── LICENSE             # MIT License
└── .github/
    ├── workflows/
       └── main.yml    # CI/CD for Norminette validation
```

## 🎯 Key Features

- **Pipeline Execution**: Implements shell-like pipe mechanism between two commands
- **File Redirection**: Reads input from a file and writes output to another file
- **Command Path Resolution**: Automatically locates executables using the system PATH
- **Robust Error Handling**: Comprehensive error checking for file operations, process creation, and command execution
- **Memory Management**: Proper cleanup and memory deallocation
- **42 Norm Compliance**: Strictly follows 42 School coding standards

## 🛠️ Getting Started

### Prerequisites

- GCC or Clang compiler
- Make build system
- Unix-like operating system (Linux, macOS)

### Installation

1. Clone the repository:
```bash
git clone https://github.com/peda-cos/Pipex.git
cd Pipex
```

2. Compile the project:
```bash
make
```

This will generate the `pipex` executable.

### Usage

```bash
./pipex file1 cmd1 cmd2 file2
```

**Parameters:**
- `file1`: Input file to read from
- `cmd1`: First command to execute
- `cmd2`: Second command to execute
- `file2`: Output file to write to

**Example:**

```bash
./pipex infile "ls -l" "wc -l" outfile
```

This is equivalent to:
```bash
< infile ls -l | wc -l > outfile
```

### Example Use Cases

1. **Count lines in a file after grep:**
```bash
./pipex input.txt "grep pattern" "wc -l" output.txt
```

2. **Sort and get unique entries:**
```bash
./pipex data.txt "sort" "uniq" result.txt
```

3. **Search and format output:**
```bash
./pipex file.txt "cat" "tr 'a-z' 'A-Z'" uppercase.txt
```

## 🧪 Development Workflow

### Building

- `make` or `make all`: Compile the project
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Recompile the entire project

### Coding Standards

The project strictly adheres to the **42 School Norminette** standards:

- **Functions**: Maximum 25 lines per function
- **Line Length**: Maximum 80 characters per line
- **Function Parameters**: Maximum 4 parameters per function
- **Variables**: Declaration at the beginning of functions
- **Naming Conventions**:
  - Functions: `snake_case`
  - Variables: `snake_case`
  - Constants: No specific requirement
- **Header Protection**: All header files use include guards
- **Forbidden**: `for` loops, ternary operators in certain contexts, and other norm-specific restrictions

### Code Style

- Consistent indentation using tabs
- Proper function and variable naming
- Comprehensive error handling
- Clear separation of concerns
- Memory leak prevention with proper cleanup

## 🧪 Testing

The project uses automated Norminette validation through GitHub Actions to ensure code compliance with 42 School standards.

### Manual Testing

Test the program with various scenarios:

1. **Valid input:**
```bash
./pipex infile "cat" "wc -l" outfile
```

2. **Non-existent input file:**
```bash
./pipex nonexistent "cat" "wc -l" outfile
```

3. **Invalid commands:**
```bash
./pipex infile "invalidcmd" "wc -l" outfile
```

4. **Permission errors:**
```bash
./pipex /etc/shadow "cat" "wc -l" outfile
```

### Continuous Integration

The project includes a GitHub Actions workflow that automatically runs Norminette on every push and pull request:

- Validates all `.c` and `.h` files
- Ensures compliance with 42 coding standards
- Provides immediate feedback on norm violations

## 🤝 Contributing

Contributions are welcome! To contribute to this project:

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/your-feature-name`
3. **Follow the coding standards**: Ensure your code passes Norminette validation
4. **Test thoroughly**: Verify your changes work as expected
5. **Commit your changes**: `git commit -m 'Add some feature'`
6. **Push to the branch**: `git push origin feature/your-feature-name`
7. **Open a Pull Request**

### Code Quality Guidelines

- All code must pass Norminette validation
- Functions should be concise and single-purpose
- Include proper error handling
- Avoid memory leaks
- Use meaningful variable and function names
- Comment complex logic where necessary

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2025 Pedro Monteiro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```

## 👨‍💻 Author

**Pedro Monteiro** (peda-cos)
- 42 Intra: peda-cos
- GitHub: [@peda-cos](https://github.com/peda-cos)
- School: 42 São Paulo

## 🙏 Acknowledgments

- [42 School](https://www.42sp.org.br/) for the project subject and learning methodology
- The 42 community for support and code reviews
- Contributors and testers who helped improve this project

---

*This project is part of the 42 School curriculum, focusing on Unix system programming, process management, and inter-process communication.*
