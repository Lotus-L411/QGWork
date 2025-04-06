#include <stdio.h>
#include <stdlib.h>
#include "sort_algorithms.h"
#include "test_utils.h"
#include "application.h"

void display_menu() {
    printf("\n========== 排序算法测试系统 ==========\n");
    printf("1. 测试大数据量排序性能\n");
    printf("2. 测试小数据量排序性能\n");
    printf("3. 生成测试数据并保存到文件\n");
    printf("4. 从文件读取数据并排序\n");
    printf("5. 解决排序应用题\n");
    printf("0. 退出\n");
    printf("=====================================\n");
    printf("请选择操作: ");
}

void test_large_data_performance() {
    printf("\n=== 测试大数据量排序性能 ===\n");
    
    int sizes[] = {10000, 50000, 200000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < num_sizes; i++) {
        printf("\n测试数据量: %d\n", sizes[i]);
        test_sort_performance(InsertSort, "插入排序", sizes[i]);
        test_sort_performance(MergeSort, "归并排序", sizes[i]);
        test_sort_performance(QuickSort, "快速排序", sizes[i]);
        test_sort_performance(CountSort, "计数排序", sizes[i]);
        test_sort_performance(RadixCountSort, "基数计数排序", sizes[i]);
    }
}

void test_small_data_performance_wrapper() {
    printf("\n=== 测试小数据量排序性能 ===\n");
    
    int data_size = 100;
    int repeat_times = 100000;
    
    test_small_data_performance(InsertSort, "插入排序", data_size, repeat_times);
    test_small_data_performance(MergeSort, "归并排序", data_size, repeat_times);
    test_small_data_performance(QuickSort, "快速排序", data_size, repeat_times);
    test_small_data_performance(CountSort, "计数排序", data_size, repeat_times);
    test_small_data_performance(RadixCountSort, "基数计数排序", data_size, repeat_times);
}

void generate_and_save_data() {
    printf("\n=== 生成测试数据并保存到文件 ===\n");
    
    int n;
    printf("请输入要生成的数据量: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败\n");
        return;
    }
    
    generate_random_data(arr, n, n * 10);
    save_data_to_file("data/input_data.txt", arr, n);
    printf("数据已保存到 data/input_data.txt\n");
    
    free(arr);
}

void load_and_sort_data() {
    printf("\n=== 从文件读取数据并排序 ===\n");
    
    int n;
    printf("请输入要读取的数据量: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败\n");
        return;
    }
    
    int x = load_data_from_file("data/input_data.txt", arr, n);
    
    if(x==0) return;
    
    int choice;
    do{
        printf("\n选择排序算法:\n");
   		printf("1. 插入排序\n");
   		printf("2. 归并排序\n");
  		printf("3. 快速排序\n");
  		printf("4. 计数排序\n");
   		printf("5. 基数计数排序\n");
   		printf("6. 退出\n");
  		printf("选择: ");
    
    	scanf("%d", &choice);
    	
    	clock_t start = clock();
    		switch (choice) {
    	    case 1: InsertSort(arr, n); break;
    	    case 2: MergeSort(arr, n); break;
    	    case 3: QuickSort(arr, n); break;
    	    case 4: CountSort(arr, n); break;
    	    case 5: RadixCountSort(arr, n); break;
    	    case 6: return;
    	    default: printf("无效选择\n");continue;
		}
    
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("排序完成，耗时: %.6f 秒\n", time_spent);
    
    save_data_to_file("data/output_data.txt", arr, n);
    printf("排序结果已保存到 data/output_data.txt\n");
	} while (choice != 6);
    
    free(arr);
}

void solve_application_problems() {
	int choice;
	do{
		printf("\n=== 解决排序应用题 ===\n");
    	printf("\n1. 查找第k大的元素\n");
    	printf("2. 重新排列数组\n");
    	printf("3. 退出\n");
    	printf("选择: ");
    	
    	scanf("%d", &choice);
    	
    	switch (choice) {
    	    case 1:
    	    	findKthLargest();
    	        break;
    	    case 2:
    	        sortColors();
    	        break;
    	    case 3:printf("退出成功~~");return;
    	    default:
    	        printf("无效选择\n");
    	}
	} while(choice !=3 );
    
      
}

int main() {
    int choice;
    
    do {
        display_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: test_large_data_performance(); break;
            case 2: test_small_data_performance_wrapper(); break;
            case 3: generate_and_save_data(); break;
            case 4: load_and_sort_data(); break;
            case 5: solve_application_problems(); break;
            case 0: printf("感谢使用，再见!\n"); break;
            default: printf("无效选择，请重新输入!\n");
        }
    } while(choice !=0 );
    
    return 0;
}
