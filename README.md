# 🔧 Pipex

A C program that recreates the behavior of shell pipes, allowing you to chain two commands together just like in bash.

## 📝 Description

Pipex is a system programming project that implements the functionality of shell pipes using low-level Unix system calls. It takes an input file, processes it through two commands connected by a pipe, and writes the result to an output file.

**What it does:** `./pipex file1 cmd1 cmd2 file2` behaves exactly like `< file1 cmd1 | cmd2 > file2` in bash.

## ✨ Features

- 🔄 **Pipe Implementation**: Creates actual Unix pipes between processes
- 🚀 **Process Management**: Uses `fork()` and `execve()` for command execution
- 📁 **File Handling**: Reads from input files and writes to output files
- 🛣️ **PATH Resolution**: Automatically finds commands in your system PATH
- ⚡ **Error Handling**: Comprehensive error checking and reporting
- 🧹 **Memory Management**: Clean memory allocation and deallocation

## 🛠️ Installation

### Prerequisites
- Clang or any C compiler
- Make
- Unix-like operating system (Linux, macOS)

### Build Steps

1. **Clone the repository:**
   ```bash
   git clone <your-repo-url>
   cd Pipex
   ```

2. **Compile the project:**
   ```bash
   make
   ```

3. **Verify installation:**
   ```bash
   ./pipex
   ```
   You should see the usage message.

### 🧽 Cleanup Commands
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild everything from scratch
```

## 🚀 Usage

### Basic Syntax
```bash
./pipex <input_file> <command1> <command2> <output_file>
```

### 📚 Examples

**Example 1: Basic text processing**
```bash
# Create a test file
echo -e "hello world\ngoodbye world\nhello universe" > input.txt

# Count lines containing "hello" and sort them
./pipex input.txt "grep hello" "wc -l" output.txt

# Check the result
cat output.txt  # Should output: 2
```

**Example 2: File manipulation**
```bash
# List files and filter for .c files
./pipex /dev/null "ls -la" "grep .c" c_files.txt
```

**Example 3: Text transformation**
```bash
# Convert text to uppercase and sort
echo -e "banana\napple\ncherry" > fruits.txt
./pipex fruits.txt "tr a-z A-Z" "sort" sorted_fruits.txt
```

**Example 4: Complex pipeline**
```bash
# Process log files
./pipex access.log "grep ERROR" "head -10" errors.txt
```

### 🔍 Understanding the Flow

```
Input File → Command 1 → Pipe → Command 2 → Output File
    ↓           ↓                    ↓          ↓
 input.txt → grep hello → | → wc -l → output.txt
```

## ⚙️ How It Works

### Core Components

1. **🔧 Pipe Creation**: Creates a pipe using `pipe()` system call
2. **🚀 Process Forking**: Creates child processes with `fork()`
3. **🔄 File Descriptor Management**: Redirects stdin/stdout using `dup2()`
4. **⚡ Command Execution**: Executes commands using `execve()`
5. **⏳ Process Synchronization**: Waits for child processes with `waitpid()`

### File Structure
```
├── main.c          # Entry point and argument parsing
├── exec_utils.c    # Process creation and command execution
├── path_utils.c    # PATH resolution for commands
├── str_utils.c     # String manipulation utilities
├── ft_split.c      # String splitting functionality
├── pipex.h         # Header file with function declarations
└── Makefile        # Build configuration
```

## 🎯 Command Line Arguments

| Argument | Description | Example |
|----------|-------------|---------|
| `file1` | Input file to read from | `input.txt` |
| `cmd1` | First command to execute | `"grep hello"` |
| `cmd2` | Second command to execute | `"wc -l"` |
| `file2` | Output file to write to | `output.txt` |

### 💡 Pro Tips

- **Quote commands with spaces**: Use `"grep hello"` instead of `grep hello`
- **File permissions**: Input file must be readable, output file will be created/overwritten
- **Command availability**: Commands must be in your PATH or use absolute paths
- **Error handling**: Check the output file even if commands fail

## 🚨 Error Handling

The program handles various error scenarios:

- ❌ **Wrong number of arguments**: Shows usage message
- 📁 **File not found**: Creates empty output file and exits
- 🚫 **Permission denied**: Shows appropriate error message
- 🔍 **Command not found**: Reports command resolution failure
- 💥 **System call failures**: Handles pipe, fork, and exec errors

## 🧪 Testing

### Quick Test Suite
```bash
# Test 1: Basic functionality
echo "hello world" > test_input.txt
./pipex test_input.txt "cat" "wc -w" test_output.txt
cat test_output.txt  # Should show: 2

# Test 2: Error handling
./pipex nonexistent.txt "cat" "wc -l" error_test.txt

# Test 3: Complex commands
echo -e "apple\nbanana\ncherry" > fruits.txt
./pipex fruits.txt "sort" "tail -1" last_fruit.txt
cat last_fruit.txt  # Should show: cherry

# Cleanup
rm -f test_* fruits.txt last_fruit.txt
```

### 🔄 Compare with Bash
```bash
# Test equivalence
echo "test data" > comparison.txt

# Using pipex
./pipex comparison.txt "cat" "wc -c" pipex_result.txt

# Using bash
< comparison.txt cat | wc -c > bash_result.txt

# Compare results
diff pipex_result.txt bash_result.txt  # Should be identical
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **42 School** for the project inspiration
- **Unix System Programming** concepts and documentation
- **The C Programming Language** reference materials

## 📚 Further Reading

- [Unix Pipes Tutorial](https://www.tutorialspoint.com/unix/unix-pipes-filters.htm)
- [System Programming in C](https://www.gnu.org/software/libc/manual/)
- [Process Management in Unix](https://www.tutorialspoint.com/unix/unix-processes.htm)

---

**Made with ❤️ by a solo indie developer**

*Happy piping! 🚀*
