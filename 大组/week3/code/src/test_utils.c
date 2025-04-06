#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test_utils.h"
#include "sort_algorithms.h"

// �����������
void generate_random_data(int arr[], int n, int max_val) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max_val;
    }
}

// ���ɽ������������
void generate_nearly_sorted_data(int arr[], int n, int swap_times) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    
    srand(time(NULL));
    for (int i = 0; i < swap_times; i++) {
        int pos1 = rand() % n;
        int pos2 = rand() % n;
        int temp = arr[pos1];
        arr[pos1] = arr[pos2];
        arr[pos2] = temp;
    }
}

// �������ݵ��ļ�
void save_data_to_file(const char* filename, int arr[], int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("�޷����ļ� %s\n", filename);
        return;
    }
    
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    
    fclose(file);
}

// ���ļ���������
int load_data_from_file(const char* filename, int arr[], int n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ� %s\n", filename);
        return 0;
    }
    
    int file_n;
    fscanf(file, "%d", &file_n);
    if (file_n != n) {
        printf("����: �ļ��е�������(%d)�������������(%d)��ƥ��\n", file_n, n);
        fclose(file);
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    
    fclose(file);
    return 1;
}

// ������������
void test_sort_performance(void (*sort_func)(int[], int), const char* sort_name, int data_size) {
    int* arr = (int*)malloc(data_size * sizeof(int));
    if (arr == NULL) {
        printf("�ڴ����ʧ��\n");
        return;
    }
    
    generate_random_data(arr, data_size, data_size * 10);
    
    clock_t start = clock();
    sort_func(arr, data_size);
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s ���� %d �����ݺ�ʱ: %.6f ��\n", sort_name, data_size, time_spent);
    
    free(arr);
}

// ����С��������������
void test_small_data_performance(void (*sort_func)(int[], int), const char* sort_name, int data_size, int repeat_times) {
    int* arr = (int*)malloc(data_size * sizeof(int));
    if (arr == NULL) {
        printf("�ڴ����ʧ��\n");
        return;
    }
    
    clock_t total_time = 0;
    
    for (int i = 0; i < repeat_times; i++) {
        generate_random_data(arr, data_size, 1000);
        
        clock_t start = clock();
        sort_func(arr, data_size);
        clock_t end = clock();
        
        total_time += (end - start);
    }
    
    double avg_time = ((double)total_time / CLOCKS_PER_SEC) / repeat_times;
    printf("%s ���� %d ������ %d �ε�ƽ����ʱ: %.6f ��\n", 
           sort_name, data_size, repeat_times, avg_time);
    
    free(arr);
}
