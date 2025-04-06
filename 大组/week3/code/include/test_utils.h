#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <time.h>

void generate_random_data(int arr[], int n, int max_val);
void generate_nearly_sorted_data(int arr[], int n, int swap_times);
void save_data_to_file(const char* filename, int arr[], int n);
int load_data_from_file(const char* filename, int arr[], int n);
void test_sort_performance(void (*sort_func)(int[], int), const char* sort_name, int data_size);
void test_small_data_performance(void (*sort_func)(int[], int), const char* sort_name, int data_size, int repeat_times);

#endif
