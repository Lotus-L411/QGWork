#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "sort_algorithms.h"

// 找到第k大的元素
void findKthLargest() {
	int n, k,f;
    printf("请输入数组大小: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败\n");
        return;
    }
    
    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("请输入k值: ");
    scanf("%d", &k);
    
    if (k < 1 || k > n)  f=1;
	
    
    QuickSort(arr, n);
    if(f == -1) printf("无该元素。");
    f = arr[n - k];
    printf("第%d大的元素是: %d\n", k,f);
    free(arr);

}

// 重新排列数组
void sortColors() {
	
	int n;
    printf("请输入数组大小: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败\n");
        return;
    }
    
    printf("请输入 %d 个整数(从[0,1,2]中选择): ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int *nums=arr;
    int p0 = 0, p2 = n - 1;
    for (int p1 = 0; p1 <= p2; ) {
        if (nums[p1] == 0) {
            // 交换0到左侧
            int temp = nums[p0];
            nums[p0] = nums[p1];
            nums[p1] = temp;
            p0++;
            p1++;
        } else if (nums[p1] == 2) {
            // 交换2到右侧
            int temp = nums[p2];
            nums[p2] = nums[p1];
            nums[p1] = temp;
            p2--;
            // 这里不移动p1，因为交换后的nums[p1]可能是0或1，需要再次检查
        } else {
            // 遇到1直接跳过
            p1++;
        }
    }
    printf("重新排列后的数组:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}
