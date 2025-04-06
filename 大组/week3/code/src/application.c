#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "sort_algorithms.h"

// �ҵ���k���Ԫ��
void findKthLargest() {
	int n, k,f;
    printf("�����������С: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("�ڴ����ʧ��\n");
        return;
    }
    
    printf("������ %d ������: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("������kֵ: ");
    scanf("%d", &k);
    
    if (k < 1 || k > n)  f=1;
	
    
    QuickSort(arr, n);
    if(f == -1) printf("�޸�Ԫ�ء�");
    f = arr[n - k];
    printf("��%d���Ԫ����: %d\n", k,f);
    free(arr);

}

// ������������
void sortColors() {
	
	int n;
    printf("�����������С: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("�ڴ����ʧ��\n");
        return;
    }
    
    printf("������ %d ������(��[0,1,2]��ѡ��): ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int *nums=arr;
    int p0 = 0, p2 = n - 1;
    for (int p1 = 0; p1 <= p2; ) {
        if (nums[p1] == 0) {
            // ����0�����
            int temp = nums[p0];
            nums[p0] = nums[p1];
            nums[p1] = temp;
            p0++;
            p1++;
        } else if (nums[p1] == 2) {
            // ����2���Ҳ�
            int temp = nums[p2];
            nums[p2] = nums[p1];
            nums[p1] = temp;
            p2--;
            // ���ﲻ�ƶ�p1����Ϊ�������nums[p1]������0��1����Ҫ�ٴμ��
        } else {
            // ����1ֱ������
            p1++;
        }
    }
    printf("�������к������:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}
