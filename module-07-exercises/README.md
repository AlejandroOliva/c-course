# Module 7: Practical Exercises

Welcome to Module 7! This final module provides comprehensive exercises and projects that will help you apply all the C programming concepts you've learned. These exercises range from beginner to advanced levels and cover real-world scenarios.

## 🎯 Learning Objectives

By the end of this module, you will be able to:
- Apply all C programming concepts in practical projects
- Build complete applications from scratch
- Implement advanced algorithms and data structures
- Write clean, maintainable, and efficient code
- Debug complex programs effectively
- Design and architect C applications

## 📚 Topics Covered

1. [Progressive Exercises](#progressive-exercises)
2. [Real-World Projects](#real-world-projects)
3. [Advanced Challenges](#advanced-challenges)
4. [Code Review and Best Practices](#code-review-and-best-practices)
5. [Testing and Debugging](#testing-and-debugging)
6. [Performance Optimization](#performance-optimization)

---

## Progressive Exercises

### Beginner Level

#### Exercise 1: Simple Calculator
Build a calculator that supports basic arithmetic operations.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculate(double a, double b, char operation) {
    switch (operation) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b != 0) {
                return a / b;
            } else {
                printf("Error: Division by zero!\n");
                return 0;
            }
        default:
            printf("Error: Invalid operation!\n");
            return 0;
    }
}

int main() {
    double num1, num2, result;
    char operation;
    
    printf("Simple Calculator\n");
    printf("Enter operation (num1 operator num2): ");
    
    if (scanf("%lf %c %lf", &num1, &operation, &num2) == 3) {
        result = calculate(num1, num2, operation);
        printf("Result: %.2f\n", result);
    } else {
        printf("Invalid input format!\n");
    }
    
    return 0;
}
```

#### Exercise 2: Student Grade Manager
Manage student grades with basic statistics.

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int id;
    float grade;
} Student;

void add_student(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Maximum number of students reached!\n");
        return;
    }
    
    printf("Enter student name: ");
    scanf("%s", students[*count].name);
    printf("Enter student ID: ");
    scanf("%d", &students[*count].id);
    printf("Enter student grade: ");
    scanf("%f", &students[*count].grade);
    
    (*count)++;
    printf("Student added successfully!\n");
}

void display_students(Student students[], int count) {
    if (count == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    printf("\nStudent List:\n");
    printf("%-20s %-10s %-10s\n", "Name", "ID", "Grade");
    printf("%-20s %-10s %-10s\n", "----", "--", "-----");
    
    for (int i = 0; i < count; i++) {
        printf("%-20s %-10d %-10.2f\n", 
               students[i].name, students[i].id, students[i].grade);
    }
}

void calculate_statistics(Student students[], int count) {
    if (count == 0) {
        printf("No students to calculate statistics.\n");
        return;
    }
    
    float sum = 0;
    float min = students[0].grade;
    float max = students[0].grade;
    
    for (int i = 0; i < count; i++) {
        sum += students[i].grade;
        if (students[i].grade < min) min = students[i].grade;
        if (students[i].grade > max) max = students[i].grade;
    }
    
    float average = sum / count;
    
    printf("\nGrade Statistics:\n");
    printf("Average: %.2f\n", average);
    printf("Minimum: %.2f\n", min);
    printf("Maximum: %.2f\n", max);
}

int main() {
    Student students[MAX_STUDENTS];
    int student_count = 0;
    int choice;
    
    while (1) {
        printf("\nStudent Grade Manager\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Calculate Statistics\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_student(students, &student_count);
                break;
            case 2:
                display_students(students, student_count);
                break;
            case 3:
                calculate_statistics(students, student_count);
                break;
            case 4:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
```

### Intermediate Level

#### Exercise 3: File Encryption/Decryption Tool
Create a simple file encryption tool using Caesar cipher.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt_file(const char *input_file, const char *output_file, int shift) {
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error: Cannot open input file '%s'\n", input_file);
        return;
    }
    
    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Error: Cannot create output file '%s'\n", output_file);
        fclose(input);
        return;
    }
    
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ch >= 'A' && ch <= 'Z') {
            ch = ((ch - 'A' + shift) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            ch = ((ch - 'a' + shift) % 26) + 'a';
        }
        fputc(ch, output);
    }
    
    fclose(input);
    fclose(output);
    printf("File encrypted successfully!\n");
}

void decrypt_file(const char *input_file, const char *output_file, int shift) {
    encrypt_file(input_file, output_file, 26 - shift);  // Reverse the shift
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <encrypt|decrypt> <input_file> <output_file> <shift>\n", argv[0]);
        return 1;
    }
    
    int shift = atoi(argv[4]);
    if (shift < 1 || shift > 25) {
        printf("Shift must be between 1 and 25\n");
        return 1;
    }
    
    if (strcmp(argv[1], "encrypt") == 0) {
        encrypt_file(argv[2], argv[3], shift);
    } else if (strcmp(argv[1], "decrypt") == 0) {
        decrypt_file(argv[2], argv[3], shift);
    } else {
        printf("Invalid operation. Use 'encrypt' or 'decrypt'\n");
        return 1;
    }
    
    return 0;
}
```

#### Exercise 4: Contact Management System
Build a contact management system with file persistence.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 1000
#define FILENAME "contacts.dat"

typedef struct {
    char name[100];
    char phone[20];
    char email[100];
    int id;
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int count;
    int next_id;
} ContactManager;

ContactManager* create_contact_manager() {
    ContactManager *manager = malloc(sizeof(ContactManager));
    manager->count = 0;
    manager->next_id = 1;
    return manager;
}

void add_contact(ContactManager *manager) {
    if (manager->count >= MAX_CONTACTS) {
        printf("Maximum contacts reached!\n");
        return;
    }
    
    Contact *contact = &manager->contacts[manager->count];
    contact->id = manager->next_id++;
    
    printf("Enter name: ");
    fgets(contact->name, sizeof(contact->name), stdin);
    contact->name[strcspn(contact->name, "\n")] = 0;  // Remove newline
    
    printf("Enter phone: ");
    fgets(contact->phone, sizeof(contact->phone), stdin);
    contact->phone[strcspn(contact->phone, "\n")] = 0;
    
    printf("Enter email: ");
    fgets(contact->email, sizeof(contact->email), stdin);
    contact->email[strcspn(contact->email, "\n")] = 0;
    
    manager->count++;
    printf("Contact added successfully with ID: %d\n", contact->id);
}

void search_contact(ContactManager *manager) {
    char search_name[100];
    printf("Enter name to search: ");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0;
    
    int found = 0;
    for (int i = 0; i < manager->count; i++) {
        if (strstr(manager->contacts[i].name, search_name) != NULL) {
            Contact *contact = &manager->contacts[i];
            printf("ID: %d, Name: %s, Phone: %s, Email: %s\n",
                   contact->id, contact->name, contact->phone, contact->email);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No contacts found matching '%s'\n", search_name);
    }
}

void delete_contact(ContactManager *manager) {
    int id;
    printf("Enter contact ID to delete: ");
    scanf("%d", &id);
    getchar();  // Consume newline
    
    for (int i = 0; i < manager->count; i++) {
        if (manager->contacts[i].id == id) {
            // Shift remaining contacts
            for (int j = i; j < manager->count - 1; j++) {
                manager->contacts[j] = manager->contacts[j + 1];
            }
            manager->count--;
            printf("Contact deleted successfully!\n");
            return;
        }
    }
    
    printf("Contact with ID %d not found!\n", id);
}

void save_contacts(ContactManager *manager) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error saving contacts!\n");
        return;
    }
    
    fwrite(&manager->count, sizeof(int), 1, file);
    fwrite(&manager->next_id, sizeof(int), 1, file);
    fwrite(manager->contacts, sizeof(Contact), manager->count, file);
    
    fclose(file);
    printf("Contacts saved successfully!\n");
}

void load_contacts(ContactManager *manager) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("No existing contacts file found.\n");
        return;
    }
    
    fread(&manager->count, sizeof(int), 1, file);
    fread(&manager->next_id, sizeof(int), 1, file);
    fread(manager->contacts, sizeof(Contact), manager->count, file);
    
    fclose(file);
    printf("Loaded %d contacts.\n", manager->count);
}

void display_all_contacts(ContactManager *manager) {
    if (manager->count == 0) {
        printf("No contacts in the system.\n");
        return;
    }
    
    printf("\nAll Contacts:\n");
    printf("%-5s %-20s %-15s %-30s\n", "ID", "Name", "Phone", "Email");
    printf("%-5s %-20s %-15s %-30s\n", "---", "----", "-----", "-----");
    
    for (int i = 0; i < manager->count; i++) {
        Contact *contact = &manager->contacts[i];
        printf("%-5d %-20s %-15s %-30s\n",
               contact->id, contact->name, contact->phone, contact->email);
    }
}

int main() {
    ContactManager *manager = create_contact_manager();
    load_contacts(manager);
    
    int choice;
    
    while (1) {
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Save Contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        getchar();  // Consume newline
        
        switch (choice) {
            case 1:
                add_contact(manager);
                break;
            case 2:
                search_contact(manager);
                break;
            case 3:
                delete_contact(manager);
                break;
            case 4:
                display_all_contacts(manager);
                break;
            case 5:
                save_contacts(manager);
                break;
            case 6:
                save_contacts(manager);  // Auto-save on exit
                free(manager);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
```

### Advanced Level

#### Exercise 5: Text Editor with Syntax Highlighting
Create a simple text editor with basic features.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1000

typedef struct {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int line_count;
    int current_line;
    int current_col;
    int modified;
} TextEditor;

TextEditor* create_editor() {
    TextEditor *editor = malloc(sizeof(TextEditor));
    editor->line_count = 1;
    editor->current_line = 0;
    editor->current_col = 0;
    editor->modified = 0;
    memset(editor->lines[0], 0, MAX_LINE_LENGTH);
    return editor;
}

void insert_char(TextEditor *editor, char ch) {
    if (editor->current_col >= MAX_LINE_LENGTH - 1) {
        return;  // Line too long
    }
    
    char *line = editor->lines[editor->current_line];
    int len = strlen(line);
    
    // Shift characters to the right
    for (int i = len; i > editor->current_col; i--) {
        line[i] = line[i - 1];
    }
    
    line[editor->current_col] = ch;
    editor->current_col++;
    editor->modified = 1;
}

void delete_char(TextEditor *editor) {
    char *line = editor->lines[editor->current_line];
    int len = strlen(line);
    
    if (editor->current_col > 0) {
        // Shift characters to the left
        for (int i = editor->current_col - 1; i < len; i++) {
            line[i] = line[i + 1];
        }
        editor->current_col--;
        editor->modified = 1;
    }
}

void new_line(TextEditor *editor) {
    if (editor->line_count >= MAX_LINES - 1) {
        return;  // Too many lines
    }
    
    // Move current line content after cursor to new line
    char *current_line = editor->lines[editor->current_line];
    char *next_line = editor->lines[editor->current_line + 1];
    
    // Copy content after cursor to next line
    strcpy(next_line, current_line + editor->current_col);
    
    // Truncate current line at cursor
    current_line[editor->current_col] = '\0';
    
    // Shift all lines down
    for (int i = editor->line_count; i > editor->current_line + 1; i--) {
        strcpy(editor->lines[i], editor->lines[i - 1]);
    }
    
    editor->line_count++;
    editor->current_line++;
    editor->current_col = 0;
    editor->modified = 1;
}

void move_cursor(TextEditor *editor, int direction) {
    switch (direction) {
        case 0:  // Up
            if (editor->current_line > 0) {
                editor->current_line--;
                int line_len = strlen(editor->lines[editor->current_line]);
                if (editor->current_col > line_len) {
                    editor->current_col = line_len;
                }
            }
            break;
        case 1:  // Down
            if (editor->current_line < editor->line_count - 1) {
                editor->current_line++;
                int line_len = strlen(editor->lines[editor->current_line]);
                if (editor->current_col > line_len) {
                    editor->current_col = line_len;
                }
            }
            break;
        case 2:  // Left
            if (editor->current_col > 0) {
                editor->current_col--;
            }
            break;
        case 3:  // Right
            {
                int line_len = strlen(editor->lines[editor->current_line]);
                if (editor->current_col < line_len) {
                    editor->current_col++;
                }
            }
            break;
    }
}

void display_editor(TextEditor *editor) {
    system("clear");  // Clear screen (Unix/Linux)
    
    printf("Simple Text Editor (Ctrl+Q to quit)\n");
    printf("Lines: %d, Modified: %s\n\n", editor->line_count, 
           editor->modified ? "Yes" : "No");
    
    for (int i = 0; i < editor->line_count; i++) {
        if (i == editor->current_line) {
            printf("> %s", editor->lines[i]);
            printf("\033[%dC", editor->current_col + 2);  // Move cursor
            printf("_");  // Cursor indicator
            printf("\n");
        } else {
            printf("  %s\n", editor->lines[i]);
        }
    }
}

void save_file(TextEditor *editor, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error saving file!\n");
        return;
    }
    
    for (int i = 0; i < editor->line_count; i++) {
        fprintf(file, "%s\n", editor->lines[i]);
    }
    
    fclose(file);
    editor->modified = 0;
    printf("File saved successfully!\n");
}

void load_file(TextEditor *editor, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error loading file!\n");
        return;
    }
    
    editor->line_count = 0;
    char buffer[MAX_LINE_LENGTH];
    
    while (fgets(buffer, sizeof(buffer), file) != NULL && editor->line_count < MAX_LINES) {
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline
        strcpy(editor->lines[editor->line_count], buffer);
        editor->line_count++;
    }
    
    fclose(file);
    editor->current_line = 0;
    editor->current_col = 0;
    editor->modified = 0;
    printf("File loaded successfully!\n");
}

int main(int argc, char *argv[]) {
    TextEditor *editor = create_editor();
    
    if (argc > 1) {
        load_file(editor, argv[1]);
    }
    
    printf("Simple Text Editor\n");
    printf("Use arrow keys to navigate, type to insert text\n");
    printf("Enter to create new line, Backspace to delete\n");
    printf("Ctrl+S to save, Ctrl+Q to quit\n\n");
    
    // Note: This is a simplified version
    // Real implementation would require terminal control libraries
    
    char ch;
    while ((ch = getchar()) != EOF) {
        if (ch == 3) {  // Ctrl+C
            break;
        }
        
        switch (ch) {
            case '\n':
                new_line(editor);
                break;
            case '\b':
            case 127:  // Backspace
                delete_char(editor);
                break;
            case '\033':  // Arrow keys (simplified)
                getchar();  // Skip '['
                ch = getchar();
                move_cursor(editor, ch - 'A');
                break;
            default:
                if (ch >= 32 && ch <= 126) {  // Printable characters
                    insert_char(editor, ch);
                }
                break;
        }
        
        display_editor(editor);
    }
    
    if (editor->modified) {
        printf("File has been modified. Save before quitting? (y/n): ");
        char save_choice = getchar();
        if (save_choice == 'y' || save_choice == 'Y') {
            printf("Enter filename: ");
            char filename[256];
            scanf("%s", filename);
            save_file(editor, filename);
        }
    }
    
    free(editor);
    return 0;
}
```

## Real-World Projects

### Project 1: Mini Database System
Build a simple database system with SQL-like commands.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COLUMNS 10
#define MAX_ROWS 1000
#define MAX_COLUMN_NAME 50
#define MAX_VALUE_LENGTH 100

typedef enum {
    COLUMN_INT,
    COLUMN_STRING
} ColumnType;

typedef struct {
    char name[MAX_COLUMN_NAME];
    ColumnType type;
} Column;

typedef struct {
    char values[MAX_COLUMNS][MAX_VALUE_LENGTH];
} Row;

typedef struct {
    char table_name[100];
    Column columns[MAX_COLUMNS];
    int column_count;
    Row rows[MAX_ROWS];
    int row_count;
} Table;

typedef struct {
    Table tables[100];
    int table_count;
} Database;

Database* create_database() {
    Database *db = malloc(sizeof(Database));
    db->table_count = 0;
    return db;
}

Table* find_table(Database *db, const char *table_name) {
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].table_name, table_name) == 0) {
            return &db->tables[i];
        }
    }
    return NULL;
}

void create_table(Database *db, const char *table_name, const char *columns[], 
                  const ColumnType types[], int column_count) {
    if (db->table_count >= 100) {
        printf("Error: Maximum number of tables reached\n");
        return;
    }
    
    Table *table = &db->tables[db->table_count];
    strcpy(table->table_name, table_name);
    table->column_count = column_count;
    table->row_count = 0;
    
    for (int i = 0; i < column_count; i++) {
        strcpy(table->columns[i].name, columns[i]);
        table->columns[i].type = types[i];
    }
    
    db->table_count++;
    printf("Table '%s' created successfully\n", table_name);
}

void insert_into(Database *db, const char *table_name, const char *values[], int value_count) {
    Table *table = find_table(db, table_name);
    if (table == NULL) {
        printf("Error: Table '%s' not found\n", table_name);
        return;
    }
    
    if (table->row_count >= MAX_ROWS) {
        printf("Error: Maximum number of rows reached\n");
        return;
    }
    
    if (value_count != table->column_count) {
        printf("Error: Number of values doesn't match number of columns\n");
        return;
    }
    
    Row *row = &table->rows[table->row_count];
    for (int i = 0; i < value_count; i++) {
        strcpy(row->values[i], values[i]);
    }
    
    table->row_count++;
    printf("Row inserted successfully\n");
}

void select_from(Database *db, const char *table_name, const char *columns[], int column_count) {
    Table *table = find_table(db, table_name);
    if (table == NULL) {
        printf("Error: Table '%s' not found\n", table_name);
        return;
    }
    
    // Print header
    printf("\n");
    for (int i = 0; i < column_count; i++) {
        printf("%-15s ", columns[i]);
    }
    printf("\n");
    printf("----------------------------------------\n");
    
    // Print rows
    for (int i = 0; i < table->row_count; i++) {
        for (int j = 0; j < column_count; j++) {
            // Find column index
            int col_index = -1;
            for (int k = 0; k < table->column_count; k++) {
                if (strcmp(table->columns[k].name, columns[j]) == 0) {
                    col_index = k;
                    break;
                }
            }
            
            if (col_index != -1) {
                printf("%-15s ", table->rows[i].values[col_index]);
            } else {
                printf("%-15s ", "NULL");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void show_tables(Database *db) {
    printf("\nTables in database:\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < db->table_count; i++) {
        printf("%s (%d columns, %d rows)\n", 
               db->tables[i].table_name,
               db->tables[i].column_count,
               db->tables[i].row_count);
    }
    printf("\n");
}

void parse_command(Database *db, char *command) {
    char *token = strtok(command, " \t\n");
    
    if (token == NULL) return;
    
    if (strcmp(token, "CREATE") == 0) {
        token = strtok(NULL, " \t\n");
        if (token && strcmp(token, "TABLE") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) {
                char table_name[100];
                strcpy(table_name, token);
                
                // Skip opening parenthesis
                token = strtok(NULL, " \t\n");
                
                char columns[MAX_COLUMNS][MAX_COLUMN_NAME];
                ColumnType types[MAX_COLUMNS];
                int column_count = 0;
                
                while ((token = strtok(NULL, " \t\n,)")) != NULL && column_count < MAX_COLUMNS) {
                    strcpy(columns[column_count], token);
                    types[column_count] = COLUMN_STRING;  // Default to string
                    column_count++;
                }
                
                create_table(db, table_name, (const char**)columns, types, column_count);
            }
        }
    }
    else if (strcmp(token, "INSERT") == 0) {
        token = strtok(NULL, " \t\n");
        if (token && strcmp(token, "INTO") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) {
                char table_name[100];
                strcpy(table_name, token);
                
                // Skip VALUES
                token = strtok(NULL, " \t\n");
                
                char values[MAX_COLUMNS][MAX_VALUE_LENGTH];
                int value_count = 0;
                
                // Skip opening parenthesis
                token = strtok(NULL, " \t\n");
                
                while ((token = strtok(NULL, " \t\n,)")) != NULL && value_count < MAX_COLUMNS) {
                    // Remove quotes if present
                    if (token[0] == '\'' && token[strlen(token)-1] == '\'') {
                        token[strlen(token)-1] = '\0';
                        token++;
                    }
                    strcpy(values[value_count], token);
                    value_count++;
                }
                
                insert_into(db, table_name, (const char**)values, value_count);
            }
        }
    }
    else if (strcmp(token, "SELECT") == 0) {
        token = strtok(NULL, " \t\n");
        char columns[MAX_COLUMNS][MAX_COLUMN_NAME];
        int column_count = 0;
        
        if (token && strcmp(token, "*") == 0) {
            // Handle SELECT * - get all columns from table
            token = strtok(NULL, " \t\n");
            if (token && strcmp(token, "FROM") == 0) {
                token = strtok(NULL, " \t\n");
                if (token) {
                    Table *table = find_table(db, token);
                    if (table) {
                        for (int i = 0; i < table->column_count; i++) {
                            strcpy(columns[column_count], table->columns[i].name);
                            column_count++;
                        }
                        select_from(db, token, (const char**)columns, column_count);
                    }
                }
            }
        } else {
            // Handle specific columns
            while (token && strcmp(token, "FROM") != 0 && column_count < MAX_COLUMNS) {
                // Remove comma if present
                if (token[strlen(token)-1] == ',') {
                    token[strlen(token)-1] = '\0';
                }
                strcpy(columns[column_count], token);
                column_count++;
                token = strtok(NULL, " \t\n");
            }
            
            if (token && strcmp(token, "FROM") == 0) {
                token = strtok(NULL, " \t\n");
                if (token) {
                    select_from(db, token, (const char**)columns, column_count);
                }
            }
        }
    }
    else if (strcmp(token, "SHOW") == 0) {
        token = strtok(NULL, " \t\n");
        if (token && strcmp(token, "TABLES") == 0) {
            show_tables(db);
        }
    }
    else {
        printf("Unknown command: %s\n", token);
    }
}

int main() {
    Database *db = create_database();
    char command[1000];
    
    printf("Mini Database System\n");
    printf("Commands: CREATE TABLE, INSERT INTO, SELECT, SHOW TABLES\n");
    printf("Type 'QUIT' to exit\n\n");
    
    while (1) {
        printf("DB> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        
        // Remove newline
        command[strcspn(command, "\n")] = 0;
        
        if (strcmp(command, "QUIT") == 0) {
            break;
        }
        
        if (strlen(command) > 0) {
            parse_command(db, command);
        }
    }
    
    free(db);
    printf("Goodbye!\n");
    return 0;
}
```

### Project 2: Network Packet Analyzer
Analyze network packets from a file.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t ethertype;
} EthernetHeader;

typedef struct {
    uint8_t version_ihl;
    uint8_t tos;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_fragment;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dest_ip;
} IPHeader;

typedef struct {
    uint16_t src_port;
    uint16_t dest_port;
    uint16_t length;
    uint16_t checksum;
} UDPHeader;

typedef struct {
    uint16_t src_port;
    uint16_t dest_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t data_offset;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent;
} TCPHeader;
#pragma pack(pop)

typedef struct {
    uint32_t src_ip;
    uint32_t dest_ip;
    uint16_t src_port;
    uint16_t dest_port;
    uint8_t protocol;
    uint16_t packet_size;
    uint64_t timestamp;
} PacketInfo;

void print_mac_address(uint8_t *mac) {
    printf("%02x:%02x:%02x:%02x:%02x:%02x", 
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void print_ip_address(uint32_t ip) {
    printf("%d.%d.%d.%d", 
           (ip >> 0) & 0xFF,
           (ip >> 8) & 0xFF,
           (ip >> 16) & 0xFF,
           (ip >> 24) & 0xFF);
}

void analyze_packet(const uint8_t *packet_data, size_t packet_size, uint64_t packet_num) {
    if (packet_size < sizeof(EthernetHeader)) {
        printf("Packet %lu: Too small for Ethernet header\n", packet_num);
        return;
    }
    
    EthernetHeader *eth = (EthernetHeader*)packet_data;
    
    printf("\n--- Packet %lu ---\n", packet_num);
    printf("Size: %zu bytes\n", packet_size);
    printf("Source MAC: ");
    print_mac_address(eth->src_mac);
    printf("\nDestination MAC: ");
    print_mac_address(eth->dest_mac);
    printf("\nEthertype: 0x%04x\n", ntohs(eth->ethertype));
    
    if (ntohs(eth->ethertype) == 0x0800) {  // IPv4
        if (packet_size < sizeof(EthernetHeader) + sizeof(IPHeader)) {
            printf("Packet too small for IP header\n");
            return;
        }
        
        IPHeader *ip = (IPHeader*)(packet_data + sizeof(EthernetHeader));
        
        printf("IP Version: %d\n", (ip->version_ihl >> 4) & 0xF);
        printf("IP Header Length: %d bytes\n", (ip->version_ihl & 0xF) * 4);
        printf("Protocol: %d\n", ip->protocol);
        printf("Source IP: ");
        print_ip_address(ntohl(ip->src_ip));
        printf("\nDestination IP: ");
        print_ip_address(ntohl(ip->dest_ip));
        printf("\n");
        
        if (ip->protocol == 17) {  // UDP
            if (packet_size < sizeof(EthernetHeader) + sizeof(IPHeader) + sizeof(UDPHeader)) {
                printf("Packet too small for UDP header\n");
                return;
            }
            
            UDPHeader *udp = (UDPHeader*)(packet_data + sizeof(EthernetHeader) + (ip->version_ihl & 0xF) * 4);
            
            printf("UDP Source Port: %d\n", ntohs(udp->src_port));
            printf("UDP Destination Port: %d\n", ntohs(udp->dest_port));
            printf("UDP Length: %d\n", ntohs(udp->length));
        }
        else if (ip->protocol == 6) {  // TCP
            if (packet_size < sizeof(EthernetHeader) + sizeof(IPHeader) + sizeof(TCPHeader)) {
                printf("Packet too small for TCP header\n");
                return;
            }
            
            TCPHeader *tcp = (TCPHeader*)(packet_data + sizeof(EthernetHeader) + (ip->version_ihl & 0xF) * 4);
            
            printf("TCP Source Port: %d\n", ntohs(tcp->src_port));
            printf("TCP Destination Port: %d\n", ntohs(tcp->dest_port));
            printf("TCP Sequence Number: %u\n", ntohl(tcp->seq_num));
            printf("TCP Acknowledgment Number: %u\n", ntohl(tcp->ack_num));
            printf("TCP Flags: 0x%02x\n", tcp->flags);
        }
    }
}

void generate_sample_packet_file(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error creating sample packet file\n");
        return;
    }
    
    // Create a sample packet
    uint8_t packet[100];
    
    // Ethernet header
    EthernetHeader eth = {
        .dest_mac = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // Broadcast
        .src_mac = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55},
        .ethertype = htons(0x0800)  // IPv4
    };
    
    // IP header
    IPHeader ip = {
        .version_ihl = 0x45,  // Version 4, Header length 5
        .tos = 0,
        .total_length = htons(60),
        .identification = htons(1234),
        .flags_fragment = 0,
        .ttl = 64,
        .protocol = 17,  // UDP
        .checksum = 0,
        .src_ip = htonl(0xC0A80101),  // 192.168.1.1
        .dest_ip = htonl(0xC0A80102)   // 192.168.1.2
    };
    
    // UDP header
    UDPHeader udp = {
        .src_port = htons(1234),
        .dest_port = htons(5678),
        .length = htons(28),
        .checksum = 0
    };
    
    // Copy headers to packet
    memcpy(packet, &eth, sizeof(eth));
    memcpy(packet + sizeof(eth), &ip, sizeof(ip));
    memcpy(packet + sizeof(eth) + sizeof(ip), &udp, sizeof(udp));
    
    // Write packet multiple times
    for (int i = 0; i < 10; i++) {
        fwrite(packet, sizeof(packet), 1, file);
    }
    
    fclose(file);
    printf("Sample packet file created: %s\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <packet_file> [--generate-sample]\n", argv[0]);
        printf("  --generate-sample: Create a sample packet file\n");
        return 1;
    }
    
    if (argc == 3 && strcmp(argv[2], "--generate-sample") == 0) {
        generate_sample_packet_file(argv[1]);
        return 0;
    }
    
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Error opening packet file: %s\n", argv[1]);
        return 1;
    }
    
    uint8_t packet_buffer[1500];  // Maximum Ethernet frame size
    uint64_t packet_count = 0;
    size_t bytes_read;
    
    printf("Network Packet Analyzer\n");
    printf("Analyzing packets from: %s\n", argv[1]);
    
    while ((bytes_read = fread(packet_buffer, 1, sizeof(packet_buffer), file)) > 0) {
        analyze_packet(packet_buffer, bytes_read, packet_count);
        packet_count++;
    }
    
    printf("\nTotal packets analyzed: %lu\n", packet_count);
    
    fclose(file);
    return 0;
}
```

## Advanced Challenges

### Challenge 1: Compiler for Simple Language
Create a simple compiler for a basic programming language.

### Challenge 2: Operating System Kernel
Build a minimal operating system kernel.

### Challenge 3: Graphics Engine
Create a simple 2D graphics engine.

### Challenge 4: Web Server
Implement a basic HTTP web server.

### Challenge 5: Game Engine
Build a simple game engine with graphics and physics.

## Code Review and Best Practices

### Code Style Guidelines

1. **Naming Conventions**
   - Use descriptive variable and function names
   - Use camelCase for variables, snake_case for functions
   - Use UPPER_CASE for constants

2. **Function Design**
   - Keep functions small and focused
   - Use meaningful return values
   - Handle errors gracefully

3. **Memory Management**
   - Always check malloc return values
   - Free allocated memory
   - Set pointers to NULL after freeing

4. **Documentation**
   - Comment complex algorithms
   - Document function parameters and return values
   - Use meaningful commit messages

### Testing Strategies

1. **Unit Testing**
   - Test individual functions
   - Use assert statements
   - Test edge cases

2. **Integration Testing**
   - Test complete workflows
   - Verify data flow
   - Test error conditions

3. **Performance Testing**
   - Measure execution time
   - Profile memory usage
   - Test with large datasets

## Performance Optimization

### Profiling Tools

1. **gprof** - Function-level profiling
2. **Valgrind** - Memory and performance profiling
3. **perf** - Linux performance analysis

### Optimization Techniques

1. **Algorithm Optimization**
   - Choose appropriate data structures
   - Optimize loops and conditionals
   - Use efficient algorithms

2. **Memory Optimization**
   - Reduce memory allocations
   - Use stack when possible
   - Minimize cache misses

3. **Compiler Optimization**
   - Use appropriate compiler flags
   - Enable optimizations (-O2, -O3)
   - Use profile-guided optimization

## Exercises

### Exercise 1: Complete the Calculator
Extend the simple calculator with:
- History of calculations
- Memory functions
- Scientific operations
- Expression parsing

### Exercise 2: Enhance the Text Editor
Add features to the text editor:
- File operations (open, save, save as)
- Find and replace
- Line numbers
- Syntax highlighting for C

### Exercise 3: Improve the Database
Add features to the database:
- WHERE clauses
- UPDATE and DELETE operations
- Data types (INT, VARCHAR, DATE)
- Indexing

### Exercise 4: Build a Chat Server
Create a multi-client chat server with:
- TCP socket programming
- Client management
- Message broadcasting
- Command handling

### Exercise 5: Create a File Manager
Build a command-line file manager with:
- Directory navigation
- File operations (copy, move, delete)
- File permissions
- Search functionality

### Exercise 6: Implement a Web Scraper
Create a web scraper that:
- Parses HTML
- Extracts data
- Handles different formats
- Stores results

## 🎯 Module Summary

In this module, you learned:
- ✅ How to apply C programming concepts in real projects
- ✅ Building complete applications from scratch
- ✅ Advanced programming techniques
- ✅ Code organization and best practices
- ✅ Testing and debugging strategies
- ✅ Performance optimization techniques

## 🚀 What's Next?

Congratulations! You've completed the Complete C Programming Course! You now have:
- ✅ Solid understanding of C programming fundamentals
- ✅ Experience with advanced C concepts
- ✅ Practical skills in building real applications
- ✅ Knowledge of best practices and optimization

### Continue Your Journey

1. **Explore Advanced Topics**
   - Systems programming
   - Embedded development
   - Game development
   - Compiler design

2. **Learn Related Technologies**
   - C++ programming
   - Assembly language
   - Operating systems
   - Computer networks

3. **Build More Projects**
   - Contribute to open source
   - Create your own libraries
   - Build commercial applications
   - Share your knowledge

4. **Join the Community**
   - Participate in forums
   - Attend conferences
   - Mentor others
   - Never stop learning

## 📚 Final Resources

- [Advanced C Programming](https://www.oreilly.com/library/view/advanced-c-programming/9781787121036/) - Advanced techniques
- [The Art of Computer Programming](https://www-cs-faculty.stanford.edu/~knuth/taocp.html) - Donald Knuth
- [Code Complete](https://www.oreilly.com/library/view/code-complete-second/0735619670/) - Steve McConnell

---

**🎉 Congratulations on completing the Complete C Programming Course! 🎉**

You've mastered one of the most powerful and fundamental programming languages. Use your knowledge wisely and continue to grow as a programmer!

*Remember: The best way to learn programming is by programming. Keep coding, keep learning, and keep building amazing things!*

