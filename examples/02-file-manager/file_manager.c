#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define MAX_PATH 1024
#define MAX_FILENAME 256
#define MAX_COMMAND 512

void show_help() {
    printf("\nFile Manager Commands:\n");
    printf("=====================\n");
    printf("ls [dir]           - List directory contents\n");
    printf("cd <dir>           - Change directory\n");
    printf("pwd                - Print working directory\n");
    printf("mkdir <dir>        - Create directory\n");
    printf("rmdir <dir>        - Remove directory\n");
    printf("cp <src> <dest>    - Copy file/directory\n");
    printf("mv <src> <dest>    - Move/rename file/directory\n");
    printf("rm <file>          - Delete file\n");
    printf("cat <file>         - Display file contents\n");
    printf("find <pattern>     - Search for files\n");
    printf("tree [dir]         - Display directory tree\n");
    printf("info <file>        - Show file information\n");
    printf("chmod <mode> <file> - Change file permissions\n");
    printf("help               - Show this help\n");
    printf("quit               - Exit file manager\n");
    printf("\n");
}

void list_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[MAX_PATH];
    
    if (path == NULL) {
        path = ".";
    }
    
    dir = opendir(path);
    if (dir == NULL) {
        printf("Error: Cannot open directory '%s'\n", path);
        return;
    }
    
    printf("\nContents of %s:\n", path);
    printf("%-15s %-10s %-15s %-20s %s\n", "Permissions", "Size", "Owner", "Modified", "Name");
    printf("%-15s %-10s %-15s %-20s %s\n", "-----------", "----", "-----", "--------", "----");
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        if (stat(full_path, &file_stat) == 0) {
            char permissions[16];
            char time_str[32];
            struct passwd *pwd = getpwuid(file_stat.st_uid);
            
            // Format permissions
            snprintf(permissions, sizeof(permissions), "%c%c%c%c%c%c%c%c%c%c",
                S_ISDIR(file_stat.st_mode) ? 'd' : '-',
                file_stat.st_mode & S_IRUSR ? 'r' : '-',
                file_stat.st_mode & S_IWUSR ? 'w' : '-',
                file_stat.st_mode & S_IXUSR ? 'x' : '-',
                file_stat.st_mode & S_IRGRP ? 'r' : '-',
                file_stat.st_mode & S_IWGRP ? 'w' : '-',
                file_stat.st_mode & S_IXGRP ? 'x' : '-',
                file_stat.st_mode & S_IROTH ? 'r' : '-',
                file_stat.st_mode & S_IWOTH ? 'w' : '-',
                file_stat.st_mode & S_IXOTH ? 'x' : '-'
            );
            
            // Format time
            struct tm *tm_info = localtime(&file_stat.st_mtime);
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
            
            printf("%-15s %-10ld %-15s %-20s %s\n",
                permissions,
                file_stat.st_size,
                pwd ? pwd->pw_name : "unknown",
                time_str,
                entry->d_name
            );
        }
    }
    
    closedir(dir);
    printf("\n");
}

void change_directory(const char *path) {
    if (chdir(path) == 0) {
        char current_path[MAX_PATH];
        if (getcwd(current_path, sizeof(current_path)) != NULL) {
            printf("Changed to directory: %s\n", current_path);
        }
    } else {
        printf("Error: Cannot change to directory '%s'\n", path);
    }
}

void print_working_directory() {
    char current_path[MAX_PATH];
    if (getcwd(current_path, sizeof(current_path)) != NULL) {
        printf("Current directory: %s\n", current_path);
    } else {
        printf("Error: Cannot get current directory\n");
    }
}

void create_directory(const char *path) {
    if (mkdir(path, 0755) == 0) {
        printf("Directory '%s' created successfully\n", path);
    } else {
        printf("Error: Cannot create directory '%s'\n", path);
    }
}

void remove_directory(const char *path) {
    if (rmdir(path) == 0) {
        printf("Directory '%s' removed successfully\n", path);
    } else {
        printf("Error: Cannot remove directory '%s'\n", path);
    }
}

void copy_file(const char *src, const char *dest) {
    FILE *source = fopen(src, "rb");
    if (source == NULL) {
        printf("Error: Cannot open source file '%s'\n", src);
        return;
    }
    
    FILE *destination = fopen(dest, "wb");
    if (destination == NULL) {
        printf("Error: Cannot create destination file '%s'\n", dest);
        fclose(source);
        return;
    }
    
    char buffer[4096];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }
    
    fclose(source);
    fclose(destination);
    printf("File copied from '%s' to '%s'\n", src, dest);
}

void move_file(const char *src, const char *dest) {
    if (rename(src, dest) == 0) {
        printf("File moved from '%s' to '%s'\n", src, dest);
    } else {
        printf("Error: Cannot move file from '%s' to '%s'\n", src, dest);
    }
}

void delete_file(const char *path) {
    if (unlink(path) == 0) {
        printf("File '%s' deleted successfully\n", path);
    } else {
        printf("Error: Cannot delete file '%s'\n", path);
    }
}

void display_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", path);
        return;
    }
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(file);
}

void find_files(const char *pattern) {
    // Simple implementation - searches in current directory only
    DIR *dir;
    struct dirent *entry;
    
    dir = opendir(".");
    if (dir == NULL) {
        printf("Error: Cannot open current directory\n");
        return;
    }
    
    printf("Searching for pattern: %s\n", pattern);
    
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, pattern) != NULL) {
            printf("%s\n", entry->d_name);
        }
    }
    
    closedir(dir);
}

void show_file_info(const char *path) {
    struct stat file_stat;
    
    if (stat(path, &file_stat) == -1) {
        printf("Error: Cannot get information for '%s'\n", path);
        return;
    }
    
    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group *grp = getgrgid(file_stat.st_gid);
    
    printf("\nFile Information: %s\n", path);
    printf("====================\n");
    printf("Type: %s\n", S_ISDIR(file_stat.st_mode) ? "Directory" : 
                         S_ISREG(file_stat.st_mode) ? "Regular File" : "Other");
    printf("Size: %ld bytes\n", file_stat.st_size);
    printf("Permissions: %c%c%c%c%c%c%c%c%c%c\n",
        S_ISDIR(file_stat.st_mode) ? 'd' : '-',
        file_stat.st_mode & S_IRUSR ? 'r' : '-',
        file_stat.st_mode & S_IWUSR ? 'w' : '-',
        file_stat.st_mode & S_IXUSR ? 'x' : '-',
        file_stat.st_mode & S_IRGRP ? 'r' : '-',
        file_stat.st_mode & S_IWGRP ? 'w' : '-',
        file_stat.st_mode & S_IXGRP ? 'x' : '-',
        file_stat.st_mode & S_IROTH ? 'r' : '-',
        file_stat.st_mode & S_IWOTH ? 'w' : '-',
        file_stat.st_mode & S_IXOTH ? 'x' : '-'
    );
    printf("Owner: %s\n", pwd ? pwd->pw_name : "unknown");
    printf("Group: %s\n", grp ? grp->gr_name : "unknown");
    
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Modified: %s\n", time_str);
    printf("\n");
}

void change_permissions(const char *mode_str, const char *path) {
    mode_t mode = 0;
    
    // Parse octal mode
    if (strlen(mode_str) == 3 && 
        mode_str[0] >= '0' && mode_str[0] <= '7' &&
        mode_str[1] >= '0' && mode_str[1] <= '7' &&
        mode_str[2] >= '0' && mode_str[2] <= '7') {
        
        mode = (mode_str[0] - '0') << 6 | 
               (mode_str[1] - '0') << 3 | 
               (mode_str[2] - '0');
        
        if (chmod(path, mode) == 0) {
            printf("Permissions changed for '%s' to %s\n", path, mode_str);
        } else {
            printf("Error: Cannot change permissions for '%s'\n", path);
        }
    } else {
        printf("Error: Invalid permission mode '%s'. Use 3-digit octal (e.g., 755)\n", mode_str);
    }
}

void show_tree(const char *path, int depth, int max_depth) {
    if (depth > max_depth) {
        return;
    }
    
    DIR *dir;
    struct dirent *entry;
    char full_path[MAX_PATH];
    
    if (path == NULL) {
        path = ".";
    }
    
    dir = opendir(path);
    if (dir == NULL) {
        return;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Print indentation
        for (int i = 0; i < depth; i++) {
            printf("│   ");
        }
        
        // Print entry
        struct stat entry_stat;
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &entry_stat) == 0 && S_ISDIR(entry_stat.st_mode)) {
            printf("├── %s/\n", entry->d_name);
            show_tree(full_path, depth + 1, max_depth);
        } else {
            printf("├── %s\n", entry->d_name);
        }
    }
    
    closedir(dir);
}

void parse_command(const char *command) {
    char cmd_copy[MAX_COMMAND];
    strcpy(cmd_copy, command);
    
    char *token = strtok(cmd_copy, " \t\n");
    if (token == NULL) {
        return;
    }
    
    if (strcmp(token, "help") == 0) {
        show_help();
    }
    else if (strcmp(token, "ls") == 0) {
        token = strtok(NULL, " \t\n");
        list_directory(token);
    }
    else if (strcmp(token, "cd") == 0) {
        token = strtok(NULL, " \t\n");
        if (token == NULL) {
            change_directory(getenv("HOME"));
        } else {
            change_directory(token);
        }
    }
    else if (strcmp(token, "pwd") == 0) {
        print_working_directory();
    }
    else if (strcmp(token, "mkdir") == 0) {
        token = strtok(NULL, " \t\n");
        if (token != NULL) {
            create_directory(token);
        } else {
            printf("Error: Directory name required\n");
        }
    }
    else if (strcmp(token, "rmdir") == 0) {
        token = strtok(NULL, " \t\n");
        if (token != NULL) {
            remove_directory(token);
        } else {
            printf("Error: Directory name required\n");
        }
    }
    else if (strcmp(token, "cp") == 0) {
        char *src = strtok(NULL, " \t\n");
        char *dest = strtok(NULL, " \t\n");
        if (src != NULL && dest != NULL) {
            copy_file(src, dest);
        } else {
            printf("Error: Source and destination required\n");
        }
    }
    else if (strcmp(token, "mv") == 0) {
        char *src = strtok(NULL, " \t\n");
        char *dest = strtok(NULL, " \t\n");
        if (src != NULL && dest != NULL) {
            move_file(src, dest);
        } else {
            printf("Error: Source and destination required\n");
        }
    }
    else if (strcmp(token, "rm") == 0) {
        token = strtok(NULL, " \t\n");
        if (token != NULL) {
            delete_file(token);
        } else {
            printf("Error: File name required\n");
        }
    }
    else if (strcmp(token, "cat") == 0) {
        token = strtok(NULL, " \t\n");
        if (token != NULL) {
            display_file(token);
        } else {
            printf("Error: File name required\n");
        }
    }
    else if (strcmp(token, "find") == 0) {
        token = strtok(NULL, " \t\n");
        if (token != NULL) {
            find_files(token);
        } else {
            printf("Error: Search pattern required\n");
        }
    }
    else if (strcmp(token, "tree") == 0) {
        token = strtok(NULL, " \t\n");
        printf("Directory tree:\n");
        show_tree(token, 0, 3);  // Limit depth to 3 levels
    }
    else if (strcmp(token, "info") == 0) {
        token = strtok(NULL, " \t\n");
        if (token != NULL) {
            show_file_info(token);
        } else {
            printf("Error: File name required\n");
        }
    }
    else if (strcmp(token, "chmod") == 0) {
        char *mode = strtok(NULL, " \t\n");
        char *file = strtok(NULL, " \t\n");
        if (mode != NULL && file != NULL) {
            change_permissions(mode, file);
        } else {
            printf("Error: Mode and file name required\n");
        }
    }
    else {
        printf("Unknown command: %s\n", token);
        printf("Type 'help' for available commands\n");
    }
}

int main(int argc, char *argv[]) {
    char command[MAX_COMMAND];
    char initial_dir[MAX_PATH];
    
    // Set initial directory
    if (argc > 1) {
        if (chdir(argv[1]) == 0) {
            strcpy(initial_dir, argv[1]);
        } else {
            printf("Error: Cannot access directory '%s', using current directory\n", argv[1]);
            getcwd(initial_dir, sizeof(initial_dir));
        }
    } else {
        getcwd(initial_dir, sizeof(initial_dir));
    }
    
    printf("File Manager\n");
    printf("============\n");
    printf("Initial directory: %s\n", initial_dir);
    printf("Type 'help' for commands, 'quit' to exit\n\n");
    
    while (1) {
        printf("fm> ");
        
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        
        // Remove newline
        command[strcspn(command, "\n")] = 0;
        
        if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
            break;
        }
        
        if (strlen(command) > 0) {
            parse_command(command);
        }
    }
    
    printf("Goodbye!\n");
    return 0;
}
