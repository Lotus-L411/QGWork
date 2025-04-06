#include <stdio.h>
#include <stdlib.h>
#include "sort_algorithms.h"
#include "test_utils.h"
#include "application.h"

void display_menu() {
    printf("\n========== �����㷨����ϵͳ ==========\n");
    printf("1. ���Դ���������������\n");
    printf("2. ����С��������������\n");
    printf("3. ���ɲ������ݲ����浽�ļ�\n");
    printf("4. ���ļ���ȡ���ݲ�����\n");
    printf("5. �������Ӧ����\n");
    printf("0. �˳�\n");
    printf("=====================================\n");
    printf("��ѡ�����: ");
}

void test_large_data_performance() {
    printf("\n=== ���Դ��������������� ===\n");
    
    int sizes[] = {10000, 50000, 200000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < num_sizes; i++) {
        printf("\n����������: %d\n", sizes[i]);
        test_sort_performance(InsertSort, "��������", sizes[i]);
        test_sort_performance(MergeSort, "�鲢����", sizes[i]);
        test_sort_performance(QuickSort, "��������", sizes[i]);
        test_sort_performance(CountSort, "��������", sizes[i]);
        test_sort_performance(RadixCountSort, "������������", sizes[i]);
    }
}

void test_small_data_performance_wrapper() {
    printf("\n=== ����С�������������� ===\n");
    
    int data_size = 100;
    int repeat_times = 100000;
    
    test_small_data_performance(InsertSort, "��������", data_size, repeat_times);
    test_small_data_performance(MergeSort, "�鲢����", data_size, repeat_times);
    test_small_data_performance(QuickSort, "��������", data_size, repeat_times);
    test_small_data_performance(CountSort, "��������", data_size, repeat_times);
    test_small_data_performance(RadixCountSort, "������������", data_size, repeat_times);
}

void generate_and_save_data() {
    printf("\n=== ���ɲ������ݲ����浽�ļ� ===\n");
    
    int n;
    printf("������Ҫ���ɵ�������: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("�ڴ����ʧ��\n");
        return;
    }
    
    generate_random_data(arr, n, n * 10);
    save_data_to_file("data/input_data.txt", arr, n);
    printf("�����ѱ��浽 data/input_data.txt\n");
    
    free(arr);
}

void load_and_sort_data() {
    printf("\n=== ���ļ���ȡ���ݲ����� ===\n");
    
    int n;
    printf("������Ҫ��ȡ��������: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("�ڴ����ʧ��\n");
        return;
    }
    
    int x = load_data_from_file("data/input_data.txt", arr, n);
    
    if(x==0) return;
    
    int choice;
    do{
        printf("\nѡ�������㷨:\n");
   		printf("1. ��������\n");
   		printf("2. �鲢����\n");
  		printf("3. ��������\n");
  		printf("4. ��������\n");
   		printf("5. ������������\n");
   		printf("6. �˳�\n");
  		printf("ѡ��: ");
    
    	scanf("%d", &choice);
    	
    	clock_t start = clock();
    		switch (choice) {
    	    case 1: InsertSort(arr, n); break;
    	    case 2: MergeSort(arr, n); break;
    	    case 3: QuickSort(arr, n); break;
    	    case 4: CountSort(arr, n); break;
    	    case 5: RadixCountSort(arr, n); break;
    	    case 6: return;
    	    default: printf("��Чѡ��\n");continue;
		}
    
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("������ɣ���ʱ: %.6f ��\n", time_spent);
    
    save_data_to_file("data/output_data.txt", arr, n);
    printf("�������ѱ��浽 data/output_data.txt\n");
	} while (choice != 6);
    
    free(arr);
}

void solve_application_problems() {
	int choice;
	do{
		printf("\n=== �������Ӧ���� ===\n");
    	printf("\n1. ���ҵ�k���Ԫ��\n");
    	printf("2. ������������\n");
    	printf("3. �˳�\n");
    	printf("ѡ��: ");
    	
    	scanf("%d", &choice);
    	
    	switch (choice) {
    	    case 1:
    	    	findKthLargest();
    	        break;
    	    case 2:
    	        sortColors();
    	        break;
    	    case 3:printf("�˳��ɹ�~~");return;
    	    default:
    	        printf("��Чѡ��\n");
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
            case 0: printf("��лʹ�ã��ټ�!\n"); break;
            default: printf("��Чѡ������������!\n");
        }
    } while(choice !=0 );
    
    return 0;
}
