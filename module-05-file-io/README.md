# Module 5: File I/O and System Programming

Welcome to Module 5! This module covers file operations, command line arguments, error handling, and basic system programming concepts. These skills are essential for building practical C applications that can interact with the file system and handle user input effectively.

## 🎯 Learning Objectives

By the end of this module, you will be able to:
- Perform file operations (read, write, append)
- Handle command line arguments
- Implement proper error handling
- Use basic system calls
- Build command-line utilities
- Work with different file formats

## 📚 Topics Covered

1. [File Operations](#file-operations)
2. [Text vs Binary Files](#text-vs-binary-files)
3. [Error Handling](#error-handling)
4. [Command Line Arguments](#command-line-arguments)
5. [Basic System Calls](#basic-system-calls)
6. [Building CLI Utilities](#building-cli-utilities)
7. [Exercises](#exercises)

---

## File Operations

### Basic File I/O

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char content[] = "Hello, File I/O!";
    char buffer[100];
    
    // Writing to a file
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    
    fprintf(file, "%s\n", content);
    fprintf(file, "This is line 2\n");
    fprintf(file, "This is line 3\n");
    
    fclose(file);
    printf("File written successfully!\n");
    
    // Reading from a file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    
    printf("\nFile contents:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(file);
    
    return 0;
}
```

### File Modes

| Mode | Description |
|------|-------------|
| `"r"` | Read (file must exist) |
| `"w"` | Write (creates new file, overwrites existing) |
| `"a"` | Append (creates new file, appends to existing) |
| `"r+"` | Read and write (file must exist) |
| `"w+"` | Write and read (creates new file, overwrites existing) |
| `"a+"` | Append and read (creates new file, appends to existing) |
| `"rb"` | Read binary |
| `"wb"` | Write binary |
| `"ab"` | Append binary |

### Character and Line I/O

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("char_example.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // Character I/O
    char ch = 'A';
    fputc(ch, file);        // Write single character
    fputc('\n', file);
    
    // Line I/O
    fputs("This is a line\n", file);
    fputs("Another line\n", file);
    
    fclose(file);
    
    // Reading characters
    file = fopen("char_example.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    
    printf("File contents:\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    
    fclose(file);
    
    return 0;
}
```

### Formatted I/O

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("formatted.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // Write formatted data
    int age = 25;
    float height = 5.9f;
    char name[] = "John";
    
    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Age: %d\n", age);
    fprintf(file, "Height: %.1f feet\n", height);
    
    fclose(file);
    
    // Read formatted data
    file = fopen("formatted.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    
    char read_name[50];
    int read_age;
    float read_height;
    
    fscanf(file, "Name: %s\n", read_name);
    fscanf(file, "Age: %d\n", &read_age);
    fscanf(file, "Height: %f feet\n", &read_height);
    
    printf("Read data:\n");
    printf("Name: %s\n", read_name);
    printf("Age: %d\n", read_age);
    printf("Height: %.1f feet\n", read_height);
    
    fclose(file);
    
    return 0;
}
```

## Text vs Binary Files

### Text File Operations

```c
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return 1;
    }
    
    // Write student records as text
    fprintf(file, "John Doe,25,3.8\n");
    fprintf(file, "Jane Smith,22,3.9\n");
    fprintf(file, "Bob Johnson,24,3.5\n");
    
    fclose(file);
    
    // Read student records
    file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    
    char line[100];
    printf("Student records:\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        printf("Record: %s\n", line);
    }
    
    fclose(file);
    
    return 0;
}
```

### Binary File Operations

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

int main() {
    Student students[] = {
        {"John Doe", 25, 3.8f},
        {"Jane Smith", 22, 3.9f},
        {"Bob Johnson", 24, 3.5f}
    };
    
    int num_students = sizeof(students) / sizeof(students[0]);
    
    // Write to binary file
    FILE *file = fopen("students.bin", "wb");
    if (file == NULL) {
        printf("Error creating binary file!\n");
        return 1;
    }
    
    // Write number of students first
    fwrite(&num_students, sizeof(int), 1, file);
    
    // Write student data
    fwrite(students, sizeof(Student), num_students, file);
    
    fclose(file);
    printf("Binary file written successfully!\n");
    
    // Read from binary file
    file = fopen("students.bin", "rb");
    if (file == NULL) {
        printf("Error opening binary file for reading!\n");
        return 1;
    }
    
    int read_num_students;
    fread(&read_num_students, sizeof(int), 1, file);
    
    Student *read_students = malloc(read_num_students * sizeof(Student));
    fread(read_students, sizeof(Student), read_num_students, file);
    
    printf("\nRead student records:\n");
    for (int i = 0; i < read_num_students; i++) {
        printf("Name: %s, Age: %d, GPA: %.1f\n",
               read_students[i].name,
               read_students[i].age,
               read_students[i].gpa);
    }
    
    free(read_students);
    fclose(file);
    
    return 0;
}
```

## Error Handling

### File Error Handling

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void handle_file_error(const char *filename, const char *operation) {
    fprintf(stderr, "Error %s file '%s': %s\n", 
            operation, filename, strerror(errno));
}

int main() {
    FILE *file;
    char filename[] = "nonexistent.txt";
    
    // Try to open non-existent file
    file = fopen(filename, "r");
    if (file == NULL) {
        handle_file_error(filename, "opening");
        return 1;
    }
    
    fclose(file);
    
    // Demonstrate perror usage
    file = fopen("readonly_file.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    fclose(file);
    
    return 0;
}
```

### Robust File Operations

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Safe file copy function
int copy_file(const char *source, const char *destination) {
    FILE *src, *dst;
    char buffer[1024];
    size_t bytes_read;
    
    // Open source file
    src = fopen(source, "rb");
    if (src == NULL) {
        printf("Error: Cannot open source file '%s'\n", source);
        return 1;
    }
    
    // Open destination file
    dst = fopen(destination, "wb");
    if (dst == NULL) {
        printf("Error: Cannot create destination file '%s'\n", destination);
        fclose(src);
        return 1;
    }
    
    // Copy file contents
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dst) != bytes_read) {
            printf("Error: Write operation failed\n");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }
    
    // Check for read error
    if (ferror(src)) {
        printf("Error: Read operation failed\n");
        fclose(src);
        fclose(dst);
        return 1;
    }
    
    fclose(src);
    fclose(dst);
    
    printf("File copied successfully from '%s' to '%s'\n", source, destination);
    return 0;
}

int main() {
    return copy_file("source.txt", "destination.txt");
}
```

## Command Line Arguments

### Basic Command Line Arguments

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Program name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc - 1);
    
    printf("Arguments:\n");
    for (int i = 1; i < argc; i++) {
        printf("  %d: %s\n", i, argv[i]);
    }
    
    return 0;
}
```

### Advanced Argument Processing

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *program_name) {
    printf("Usage: %s [OPTIONS] [FILE]\n", program_name);
    printf("Options:\n");
    printf("  -h, --help     Show this help message\n");
    printf("  -v, --verbose  Enable verbose output\n");
    printf("  -o FILE        Output file name\n");
    printf("  -n NUMBER      Process NUMBER items\n");
}

int main(int argc, char *argv[]) {
    int verbose = 0;
    char *output_file = NULL;
    int number = 0;
    char *input_file = NULL;
    
    // Process command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        }
        else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                printf("Error: -o requires a filename\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                number = atoi(argv[++i]);
                if (number <= 0) {
                    printf("Error: -n requires a positive number\n");
                    return 1;
                }
            } else {
                printf("Error: -n requires a number\n");
                return 1;
            }
        }
        else if (argv[i][0] != '-') {
            // Not an option, treat as input file
            if (input_file == NULL) {
                input_file = argv[i];
            } else {
                printf("Error: Multiple input files specified\n");
                return 1;
            }
        }
        else {
            printf("Error: Unknown option '%s'\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }
    
    // Display parsed arguments
    if (verbose) {
        printf("Verbose mode enabled\n");
    }
    
    if (output_file) {
        printf("Output file: %s\n", output_file);
    }
    
    if (number > 0) {
        printf("Number: %d\n", number);
    }
    
    if (input_file) {
        printf("Input file: %s\n", input_file);
    } else {
        printf("No input file specified\n");
        print_usage(argv[0]);
        return 1;
    }
    
    return 0;
}
```

## Basic System Calls

### File System Operations

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "test_file.txt";
    
    // Create a file
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "This is a test file.\n");
        fclose(file);
        printf("File created: %s\n", filename);
    }
    
    // Check if file exists
    struct stat file_stat;
    if (stat(filename, &file_stat) == 0) {
        printf("File exists\n");
        printf("File size: %ld bytes\n", file_stat.st_size);
        printf("Permissions: %o\n", file_stat.st_mode & 0777);
    } else {
        printf("File does not exist\n");
    }
    
    // Remove file
    if (unlink(filename) == 0) {
        printf("File deleted: %s\n", filename);
    } else {
        printf("Error deleting file\n");
    }
    
    return 0;
}
```

### Directory Operations

```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void list_directory(const char *dirname) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char path[1024];
    
    dir = opendir(dirname);
    if (dir == NULL) {
        printf("Cannot open directory: %s\n", dirname);
        return;
    }
    
    printf("Contents of directory: %s\n", dirname);
    printf("%-20s %-10s %-15s\n", "Name", "Type", "Size");
    printf("%-20s %-10s %-15s\n", "----", "----", "----");
    
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);
        
        if (stat(path, &file_stat) == 0) {
            const char *type = S_ISDIR(file_stat.st_mode) ? "Directory" : "File";
            printf("%-20s %-10s %-15ld\n", 
                   entry->d_name, type, file_stat.st_size);
        }
    }
    
    closedir(dir);
}

int main() {
    list_directory(".");
    return 0;
}
```

## Building CLI Utilities

### Simple Text Processor

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void process_file(const char *input_file, const char *output_file, int to_upper) {
    FILE *in, *out;
    int ch;
    
    in = fopen(input_file, "r");
    if (in == NULL) {
        printf("Error: Cannot open input file '%s'\n", input_file);
        return;
    }
    
    out = fopen(output_file, "w");
    if (out == NULL) {
        printf("Error: Cannot create output file '%s'\n", output_file);
        fclose(in);
        return;
    }
    
    while ((ch = fgetc(in)) != EOF) {
        if (to_upper) {
            ch = toupper(ch);
        } else {
            ch = tolower(ch);
        }
        fputc(ch, out);
    }
    
    fclose(in);
    fclose(out);
    printf("File processed successfully!\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file> [--upper|--lower]\n", argv[0]);
        printf("  --upper: Convert to uppercase (default)\n");
        printf("  --lower: Convert to lowercase\n");
        return 1;
    }
    
    int to_upper = 1;  // Default to uppercase
    
    if (argc > 3) {
        if (strcmp(argv[3], "--lower") == 0) {
            to_upper = 0;
        } else if (strcmp(argv[3], "--upper") == 0) {
            to_upper = 1;
        } else {
            printf("Error: Unknown option '%s'\n", argv[3]);
            return 1;
        }
    }
    
    process_file(argv[1], argv[2], to_upper);
    return 0;
}
```

### File Statistics Utility

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int lines;
    int words;
    int characters;
    int bytes;
} FileStats;

FileStats analyze_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    FileStats stats = {0, 0, 0, 0};
    
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        return stats;
    }
    
    int ch, prev_ch = ' ';
    int in_word = 0;
    
    while ((ch = fgetc(file)) != EOF) {
        stats.characters++;
        
        if (ch == '\n') {
            stats.lines++;
        }
        
        // Word counting logic
        if (isspace(ch)) {
            if (in_word) {
                stats.words++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
        
        prev_ch = ch;
    }
    
    // Count last word if file doesn't end with whitespace
    if (in_word) {
        stats.words++;
    }
    
    // Count bytes (same as characters for text files)
    stats.bytes = stats.characters;
    
    fclose(file);
    return stats;
}

void print_stats(const char *filename, FileStats stats) {
    printf("%8d %8d %8d %s\n", 
           stats.lines, stats.words, stats.characters, filename);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> [file2] ...\n", argv[0]);
        printf("Display line, word, and character counts for files\n");
        return 1;
    }
    
    printf("%8s %8s %8s %s\n", "Lines", "Words", "Chars", "File");
    printf("%8s %8s %8s %s\n", "-----", "-----", "-----", "----");
    
    FileStats total = {0, 0, 0, 0};
    
    for (int i = 1; i < argc; i++) {
        FileStats stats = analyze_file(argv[i]);
        print_stats(argv[i], stats);
        
        total.lines += stats.lines;
        total.words += stats.words;
        total.characters += stats.characters;
        total.bytes += stats.bytes;
    }
    
    if (argc > 2) {
        print_stats("total", total);
    }
    
    return 0;
}
```

## Exercises

### Exercise 1: File Copy Utility
Create a program that:
1. Takes source and destination file names as arguments
2. Copies the source file to the destination
3. Handles errors gracefully
4. Shows progress for large files
5. Supports binary files

### Exercise 2: Text Search Utility
Build a program that:
1. Searches for a pattern in text files
2. Shows line numbers where matches are found
3. Supports case-sensitive and case-insensitive search
4. Can search multiple files
5. Shows context around matches

### Exercise 3: Log File Analyzer
Create a utility that:
1. Reads log files
2. Counts different types of log entries
3. Filters by date range
4. Generates summary reports
5. Exports results to different formats

### Exercise 4: Configuration File Parser
Implement a program that:
1. Reads key-value configuration files
2. Allows command-line overrides
3. Validates configuration values
4. Exports configuration to different formats
5. Supports comments and empty lines

### Exercise 5: Backup Utility
Build a backup program that:
1. Creates backups of files and directories
2. Supports compression
3. Maintains backup history
4. Can restore from backups
5. Includes command-line interface

### Exercise 6: System Monitor
Create a system monitoring tool that:
1. Monitors file system usage
2. Tracks file changes
3. Logs system events
4. Generates reports
5. Runs as a daemon

## 🎯 Module Summary

In this module, you learned:
- ✅ File operations (read, write, append)
- ✅ Text vs binary file handling
- ✅ Error handling and robust programming
- ✅ Command line argument processing
- ✅ Basic system calls and directory operations
- ✅ Building practical CLI utilities

## 🚀 What's Next?

You're ready to move on to **Module 6: Data Structures and Algorithms**, where you'll learn about:
- Linked lists and dynamic data structures
- Stacks, queues, and trees
- Sorting and searching algorithms
- Algorithm complexity analysis
- Building reusable data structure libraries

## 📚 Additional Reading

- [C File I/O](https://en.cppreference.com/w/c/io) - File operations reference
- [POSIX System Calls](https://pubs.opengroup.org/onlinepubs/9699919799/) - System programming
- [Command Line Interface Guidelines](https://clig.dev/) - CLI design principles

---

**Fantastic work completing Module 5! 🎉**

*Next: [Module 6: Data Structures and Algorithms](../module-06-data-structures/README.md)*

