#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#define MAX_EXPRESSION 1000
#define MAX_HISTORY 100

typedef struct HistoryEntry {
    char expression[MAX_EXPRESSION];
    double result;
    struct HistoryEntry *next;
} HistoryEntry;

typedef struct {
    HistoryEntry *head;
    int count;
} HistoryManager;

HistoryManager* create_history_manager() {
    HistoryManager *manager = malloc(sizeof(HistoryManager));
    manager->head = NULL;
    manager->count = 0;
    return manager;
}

void add_to_history(HistoryManager *manager, const char *expression, double result) {
    HistoryEntry *entry = malloc(sizeof(HistoryEntry));
    strcpy(entry->expression, expression);
    entry->result = result;
    entry->next = manager->head;
    manager->head = entry;
    
    manager->count++;
    if (manager->count > MAX_HISTORY) {
        // Remove oldest entry
        HistoryEntry *current = manager->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
        manager->count--;
    }
}

void show_history(HistoryManager *manager) {
    if (manager->count == 0) {
        printf("No history available.\n");
        return;
    }
    
    printf("\nCalculation History:\n");
    printf("%-3s %-30s %-15s\n", "#", "Expression", "Result");
    printf("%-3s %-30s %-15s\n", "---", "----------", "------");
    
    HistoryEntry *current = manager->head;
    int index = 1;
    while (current != NULL) {
        printf("%-3d %-30s %-15.6f\n", index, current->expression, current->result);
        current = current->next;
        index++;
    }
    printf("\n");
}

double memory_value = 0.0;

void show_memory() {
    printf("Memory: %.6f\n", memory_value);
}

void memory_clear() {
    memory_value = 0.0;
    printf("Memory cleared.\n");
}

void memory_add(double value) {
    memory_value += value;
    printf("Memory: %.6f\n", memory_value);
}

void memory_subtract(double value) {
    memory_value -= value;
    printf("Memory: %.6f\n", memory_value);
}

void memory_recall() {
    printf("Memory recall: %.6f\n", memory_value);
}

// Simple expression evaluator using recursive descent
double parse_expression(const char **expr);
double parse_term(const char **expr);
double parse_factor(const char **expr);

double parse_factor(const char **expr) {
    while (isspace(**expr)) (*expr)++;
    
    if (**expr == '(') {
        (*expr)++; // skip '('
        double result = parse_expression(expr);
        if (**expr == ')') {
            (*expr)++; // skip ')'
        }
        return result;
    }
    
    if (strncmp(*expr, "sin(", 4) == 0) {
        *expr += 4;
        double result = parse_expression(expr);
        if (**expr == ')') (*expr)++;
        return sin(result);
    }
    
    if (strncmp(*expr, "cos(", 4) == 0) {
        *expr += 4;
        double result = parse_expression(expr);
        if (**expr == ')') (*expr)++;
        return cos(result);
    }
    
    if (strncmp(*expr, "tan(", 4) == 0) {
        *expr += 4;
        double result = parse_expression(expr);
        if (**expr == ')') (*expr)++;
        return tan(result);
    }
    
    if (strncmp(*expr, "log(", 4) == 0) {
        *expr += 4;
        double result = parse_expression(expr);
        if (**expr == ')') (*expr)++;
        return log10(result);
    }
    
    if (strncmp(*expr, "ln(", 3) == 0) {
        *expr += 3;
        double result = parse_expression(expr);
        if (**expr == ')') (*expr)++;
        return log(result);
    }
    
    if (strncmp(*expr, "sqrt(", 5) == 0) {
        *expr += 5;
        double result = parse_expression(expr);
        if (**expr == ')') (*expr)++;
        return sqrt(result);
    }
    
    if (strncmp(*expr, "pow(", 4) == 0) {
        *expr += 4;
        double base = parse_expression(expr);
        if (**expr == ',') (*expr)++;
        double exp = parse_expression(expr);
        if (**expr == ')') (*expr)++;
        return pow(base, exp);
    }
    
    if (strncmp(*expr, "MR", 2) == 0) {
        *expr += 2;
        return memory_value;
    }
    
    if (strncmp(*expr, "pi", 2) == 0) {
        *expr += 2;
        return M_PI;
    }
    
    if (strncmp(*expr, "e", 1) == 0) {
        *expr += 1;
        return M_E;
    }
    
    // Parse number
    double result = 0.0;
    int sign = 1;
    
    if (**expr == '-') {
        sign = -1;
        (*expr)++;
    }
    
    while (isdigit(**expr)) {
        result = result * 10.0 + (**expr - '0');
        (*expr)++;
    }
    
    if (**expr == '.') {
        (*expr)++;
        double factor = 0.1;
        while (isdigit(**expr)) {
            result += (**expr - '0') * factor;
            factor *= 0.1;
            (*expr)++;
        }
    }
    
    return sign * result;
}

double parse_term(const char **expr) {
    double left = parse_factor(expr);
    
    while (1) {
        while (isspace(**expr)) (*expr)++;
        
        if (**expr == '*') {
            (*expr)++;
            left *= parse_factor(expr);
        } else if (**expr == '/') {
            (*expr)++;
            double right = parse_factor(expr);
            if (right == 0) {
                printf("Error: Division by zero!\n");
                return 0;
            }
            left /= right;
        } else {
            break;
        }
    }
    
    return left;
}

double parse_expression(const char **expr) {
    double left = parse_term(expr);
    
    while (1) {
        while (isspace(**expr)) (*expr)++;
        
        if (**expr == '+') {
            (*expr)++;
            left += parse_term(expr);
        } else if (**expr == '-') {
            (*expr)++;
            left -= parse_term(expr);
        } else {
            break;
        }
    }
    
    return left;
}

double evaluate_expression(const char *expression) {
    const char *expr = expression;
    return parse_expression(&expr);
}

void show_help() {
    printf("\nCalculator Help:\n");
    printf("===============\n");
    printf("Basic operations: +, -, *, /\n");
    printf("Scientific functions: sin(), cos(), tan(), log(), ln(), sqrt(), pow()\n");
    printf("Constants: pi, e\n");
    printf("Memory operations: MR (memory recall)\n");
    printf("Commands:\n");
    printf("  help          - Show this help\n");
    printf("  history       - Show calculation history\n");
    printf("  clear         - Clear screen\n");
    printf("  memory        - Show memory value\n");
    printf("  memory_clear  - Clear memory\n");
    printf("  quit          - Exit calculator\n");
    printf("\nExamples:\n");
    printf("  2 + 3 * 4\n");
    printf("  sqrt(16) + pow(2, 3)\n");
    printf("  sin(pi/2)\n");
    printf("  (10 + 5) / 3\n");
    printf("\n");
}

void clear_screen() {
    system("clear");  // Unix/Linux
    // system("cls");  // Windows
}

int main() {
    HistoryManager *history = create_history_manager();
    char input[MAX_EXPRESSION];
    
    printf("Advanced Calculator\n");
    printf("Type 'help' for commands, 'quit' to exit\n");
    printf("==========================================\n\n");
    
    while (1) {
        printf("calc> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }
        
        // Handle commands
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
            break;
        }
        else if (strcmp(input, "help") == 0) {
            show_help();
        }
        else if (strcmp(input, "history") == 0) {
            show_history(history);
        }
        else if (strcmp(input, "clear") == 0) {
            clear_screen();
            printf("Advanced Calculator\n");
            printf("Type 'help' for commands, 'quit' to exit\n");
            printf("==========================================\n\n");
        }
        else if (strcmp(input, "memory") == 0) {
            show_memory();
        }
        else if (strcmp(input, "memory_clear") == 0) {
            memory_clear();
        }
        else if (strncmp(input, "memory + ", 9) == 0) {
            double value = atof(input + 9);
            memory_add(value);
        }
        else if (strncmp(input, "memory - ", 9) == 0) {
            double value = atof(input + 9);
            memory_subtract(value);
        }
        else {
            // Try to evaluate as expression
            double result = evaluate_expression(input);
            
            // Check if we reached the end of the expression
            const char *remaining = input;
            parse_expression(&remaining);
            while (isspace(*remaining)) remaining++;
            
            if (*remaining == '\0') {
                printf("%.6f\n", result);
                add_to_history(history, input, result);
            } else {
                printf("Error: Invalid expression\n");
            }
        }
    }
    
    printf("Goodbye!\n");
    
    // Clean up history
    HistoryEntry *current = history->head;
    while (current != NULL) {
        HistoryEntry *next = current->next;
        free(current);
        current = next;
    }
    free(history);
    
    return 0;
}
