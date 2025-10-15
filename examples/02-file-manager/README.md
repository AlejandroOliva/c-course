# Example 2: File Manager

A command-line file manager with advanced features for file and directory operations.

## Features

- Directory navigation and listing
- File operations (copy, move, delete, rename)
- File search and filtering
- File permissions management
- File information display
- Batch operations
- File compression/decompression
- Directory tree view

## Files

- `file_manager.c` - Main file manager implementation
- `file_operations.c` - File operation functions
- `directory_utils.c` - Directory utility functions
- `file_info.c` - File information display
- `search.c` - File search functionality
- `permissions.c` - File permissions management
- `Makefile` - Build configuration
- `README.md` - This file

## Building

```bash
make
```

## Usage

```bash
./file_manager [directory]
```

### Commands

- `ls` - List directory contents
- `cd <dir>` - Change directory
- `pwd` - Print working directory
- `mkdir <dir>` - Create directory
- `rmdir <dir>` - Remove directory
- `cp <src> <dest>` - Copy file/directory
- `mv <src> <dest>` - Move/rename file/directory
- `rm <file>` - Delete file
- `cat <file>` - Display file contents
- `find <pattern>` - Search for files
- `tree` - Display directory tree
- `info <file>` - Show file information
- `chmod <mode> <file>` - Change file permissions
- `help` - Show help information
- `quit` - Exit file manager

### Examples

```
fm> ls
Documents/  Downloads/  Pictures/  file.txt

fm> cd Documents
fm> mkdir Projects
fm> cp ../file.txt Projects/

fm> find *.txt
./Projects/file.txt

fm> info file.txt
Name: file.txt
Size: 1024 bytes
Permissions: -rw-r--r--
Modified: 2024-01-15 10:30:45

fm> tree
.
├── Documents/
│   └── Projects/
│       └── file.txt
└── Downloads/
```

## Implementation Details

### File Operations
Implements safe file operations with error checking and progress indication.

### Directory Navigation
Provides intuitive directory navigation with path completion.

### Search Functionality
Supports pattern matching and recursive directory searching.

### Permissions Management
Handles Unix file permissions with symbolic and octal notation.

### Tree View
Displays hierarchical directory structure with Unicode characters.

