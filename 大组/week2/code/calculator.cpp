#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// 定义栈结构
typedef struct {
    double *data;
    int top;
    int size;
} Stack;

// 栈操作函数
Stack* createStack(int size);
void freeStack(Stack *stack);
void push(Stack *stack, double value);
double pop(Stack *stack);
double peek(Stack *stack);
int isEmpty(Stack *stack);

// 计算函数
int getPriority(char op);
double calculate(double a, double b, char op);
double evaluateExpression(const char *expression);
void processUserInput();

int main() {
    printf("欢迎使用四则运算计算器！\n");
    printf("支持加减乘除(+ - * /)和括号()运算\n");
    printf("输入'exit'退出程序\n\n");
    
    processUserInput();
    
    return 0;
}

// 创建栈
Stack* createStack(int size) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (double*)malloc(size * sizeof(double));
    stack->top = -1;
    stack->size = size;
    return stack;
}

// 释放栈
void freeStack(Stack *stack) {
    free(stack->data);
    free(stack);
}

// 压栈
void push(Stack *stack, double value) {
    if (stack->top == stack->size - 1) {
        stack->size *= 2;
        stack->data = (double*)realloc(stack->data, stack->size * sizeof(double));
    }
    stack->data[++stack->top] = value;
}

// 弹栈
double pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("错误：栈下溢\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// 查看栈顶元素
double peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("错误：栈为空\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// 判断栈是否为空
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// 获取运算符优先级
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 执行计算
double calculate(double a, double b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("错误：除数不能为零\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        default: 
            printf("错误：未知运算符 %c\n", op);
            exit(EXIT_FAILURE);
    }
}

// 计算表达式
double evaluateExpression(const char *expression) {
    Stack *values = createStack(100);
    Stack *ops = createStack(100);
    
    int i = 0;
    int len = strlen(expression);
    
    while (i < len) {
        // 跳过空格
        if (expression[i] == ' ') {
            i++;
            continue;
        }
        
        // 处理左括号
        if (expression[i] == '(') {
            push(ops, expression[i]);
            i++;
        }
        // 处理数字
        else if (isdigit(expression[i]) || expression[i] == '.') {
            double val = 0;
            int decimal = 0;
            double fraction = 1.0;
            
            // 处理整数部分
            while (i < len && isdigit(expression[i])) {
                val = val * 10 + (expression[i] - '0');
                i++;
            }
            
            // 处理小数部分
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
        // 处理右括号
        else if (expression[i] == ')') {
            while (!isEmpty(ops) && peek(ops) != '(') {
                double val2 = pop(values);
                double val1 = pop(values);
                char op = pop(ops);
                push(values, calculate(val1, val2, op));
            }
            
            if (!isEmpty(ops)) {
                pop(ops); // 弹出左括号
            } else {
                printf("错误：括号不匹配\n");
                exit(EXIT_FAILURE);
            }
            i++;
        }
        // 处理运算符
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
            printf("错误：无效字符 '%c'\n", expression[i]);
            exit(EXIT_FAILURE);
        }
    }
    
    // 处理剩余运算符
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

// 处理用户输入
void processUserInput() {
    char input[256];
    
    while (1) {
        printf("请输入表达式: ");
        fgets(input, sizeof(input), stdin);
        
        // 去除换行符
        input[strcspn(input, "\n")] = 0;
        
        // 检查退出命令
        if (strcmp(input, "exit") == 0) {
            break;
        }
        
        // 检查空输入
        if (strlen(input) == 0) {
            continue;
        }
        
        // 计算表达式
        double result;
        try {
            result = evaluateExpression(input);
            printf("结果: %.2f\n\n", result);
        } catch (...) {
            printf("计算错误，请检查表达式\n\n");
        }
    }
    
    printf("\n感谢使用，再见！\n");
}
