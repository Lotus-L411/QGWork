#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// ����ջ�ṹ
typedef struct {
    double *data;
    int top;
    int size;
} Stack;

// ջ��������
Stack* createStack(int size);
void freeStack(Stack *stack);
void push(Stack *stack, double value);
double pop(Stack *stack);
double peek(Stack *stack);
int isEmpty(Stack *stack);

// ���㺯��
int getPriority(char op);
double calculate(double a, double b, char op);
double evaluateExpression(const char *expression);
void processUserInput();

int main() {
    printf("��ӭʹ�����������������\n");
    printf("֧�ּӼ��˳�(+ - * /)������()����\n");
    printf("����'exit'�˳�����\n\n");
    
    processUserInput();
    
    return 0;
}

// ����ջ
Stack* createStack(int size) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (double*)malloc(size * sizeof(double));
    stack->top = -1;
    stack->size = size;
    return stack;
}

// �ͷ�ջ
void freeStack(Stack *stack) {
    free(stack->data);
    free(stack);
}

// ѹջ
void push(Stack *stack, double value) {
    if (stack->top == stack->size - 1) {
        stack->size *= 2;
        stack->data = (double*)realloc(stack->data, stack->size * sizeof(double));
    }
    stack->data[++stack->top] = value;
}

// ��ջ
double pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("����ջ����\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// �鿴ջ��Ԫ��
double peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("����ջΪ��\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// �ж�ջ�Ƿ�Ϊ��
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// ��ȡ��������ȼ�
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// ִ�м���
double calculate(double a, double b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("���󣺳�������Ϊ��\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        default: 
            printf("����δ֪����� %c\n", op);
            exit(EXIT_FAILURE);
    }
}

// ������ʽ
double evaluateExpression(const char *expression) {
    Stack *values = createStack(100);
    Stack *ops = createStack(100);
    
    int i = 0;
    int len = strlen(expression);
    
    while (i < len) {
        // �����ո�
        if (expression[i] == ' ') {
            i++;
            continue;
        }
        
        // ����������
        if (expression[i] == '(') {
            push(ops, expression[i]);
            i++;
        }
        // ��������
        else if (isdigit(expression[i]) || expression[i] == '.') {
            double val = 0;
            int decimal = 0;
            double fraction = 1.0;
            
            // ������������
            while (i < len && isdigit(expression[i])) {
                val = val * 10 + (expression[i] - '0');
                i++;
            }
            
            // ����С������
            if (i < len && expression[i] == '.') {
                decimal = 1;
                i++;
                while (i < len && isdigit(expression[i])) {
                    fraction *= 0.1;
                    val += (expression[i] - '0') * fraction;
                    i++;
                }
            }
            
            push(values, val);
        }
        // ����������
        else if (expression[i] == ')') {
            while (!isEmpty(ops) && peek(ops) != '(') {
                double val2 = pop(values);
                double val1 = pop(values);
                char op = pop(ops);
                push(values, calculate(val1, val2, op));
            }
            
            if (!isEmpty(ops)) {
                pop(ops); // ����������
            } else {
                printf("�������Ų�ƥ��\n");
                exit(EXIT_FAILURE);
            }
            i++;
        }
        // ���������
        else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/') {
            while (!isEmpty(ops) && getPriority(peek(ops)) >= getPriority(expression[i])) {
                double val2 = pop(values);
                double val1 = pop(values);
                char op = pop(ops);
                push(values, calculate(val1, val2, op));
            }
            push(ops, expression[i]);
            i++;
        }
        else {
            printf("������Ч�ַ� '%c'\n", expression[i]);
            exit(EXIT_FAILURE);
        }
    }
    
    // ����ʣ�������
    while (!isEmpty(ops)) {
        double val2 = pop(values);
        double val1 = pop(values);
        char op = pop(ops);
        push(values, calculate(val1, val2, op));
    }
    
    double result = pop(values);
    
    freeStack(values);
    freeStack(ops);
    
    return result;
}

// �����û�����
void processUserInput() {
    char input[256];
    
    while (1) {
        printf("��������ʽ: ");
        fgets(input, sizeof(input), stdin);
        
        // ȥ�����з�
        input[strcspn(input, "\n")] = 0;
        
        // ����˳�����
        if (strcmp(input, "exit") == 0) {
            break;
        }
        
        // ��������
        if (strlen(input) == 0) {
            continue;
        }
        
        // ������ʽ
        double result;
        try {
            result = evaluateExpression(input);
            printf("���: %.2f\n\n", result);
        } catch (...) {
            printf("�������������ʽ\n\n");
        }
    }
    
    printf("\n��лʹ�ã��ټ���\n");
}
