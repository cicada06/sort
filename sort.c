/*
 * 
 *按平均时间将排序分为四类：
 *
 *（1）平方阶(O(n2))排序
 *    　一般称为简单排序，例如直接插入、直接选择和冒泡排序；
 *
 *（2）线性对数阶(O(nlgn))排序
 *    　如快速、堆和归并排序；
 *
 *（3）O(n**(1+￡))阶排序
 *    　￡是介于0和1之间的常数，即0<￡<1，如希尔排序；
 *
 *（4）线性阶(O(n))排序
 *    　如桶、箱和基数排序。
 *
 *各种排序方法比较
 *
 *     简单排序中直接插入最好，快速排序最快，当文件为正序时，直接插入和冒泡均最佳。
 *
 *影响排序效果的因素
 *
 *    　因为不同的排序方法适应不同的应用环境和要求，所以选择合适的排序方法应综合考虑下列因素：
 *　　①待排序的记录数目n；
 *　　②记录的大小(规模)；
 *　　③关键字的结构及其初始状态；
 *　　④对稳定性的要求；
 *　　⑤语言工具的条件；
 *　　⑥存储结构；
 *　　⑦时间和辅助空间复杂度等。
 *
 *不同条件下，排序方法的选择
 *
 *(1)若n较小(如n≤50)，可采用直接插入或直接选择排序。
 *    　当记录规模较小时，直接插入排序较好；否则因为直接选择移动的记录数少于直接插人，应选直接选择排序为宜。
 *(2)若文件初始状态基本有序(指正序)，则应选用直接插人、冒泡或随机的快速排序为宜；
 *(3)若n较大，则应采用时间复杂度为O(nlgn)的排序方法：快速排序、堆排序或归并排序。
 *    　快速排序是目前基于比较的内部排序中被认为是最好的方法，当待排序的关键字是随机分布时，快速排序的平均时间最短；
 *    　堆排序所需的辅助空间少于快速排序，并且不会出现快速排序可能出现的最坏情况。这两种排序都是不稳定的。
 *    　若要求排序稳定，则可选用归并排序。但本章介绍的从单个记录起进行两两归并的  排序算法并不值得提倡，通常可以将它和直接插入排序结合在一起使用。先利用直接插入排序求得较长的有序子文件，然后再两两归并之。因为直接插入排序是稳定 的，所以改进后的归并排序仍是稳定的。
 *
 * 
 *
 *排序算法的稳定性
 *
 * 1） 稳定的：如果存在多个具有相同排序码的记录，经过排序后，
 *    这些记录的相对次序仍然保持不变，则这种排序算法称为稳定的。
 *    插入排序、冒泡排序、归并排序、分配排序（桶式、基数）都是稳定的排序算法。
 * 2）不稳定的：否则称为不稳定的。
 *    直接选择排序、堆排序、shell排序、快速排序都是不稳定的排序算法。
 *
 */


#include <stdlib.h>
#include <string.h>

static inline void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/*
 * 常规冒泡排序
 */
void bubble_sort(int *d, int n)
{
    int i, j;
    int flag = 0;

    if(!d || (n<=1)) {
        return;
    }

    for(i = n-1; i > 0; i--) { 
        flag = 0;
        for(j = 0; j < i; j++) { // 右端左移
            if(d[j] > d[j+1]) {
                swap(d+j, d+j+1);
                flag = 1;
            }
        }
        // 一旦遍历后顺序不再改变，就可以跳出比较判断了
        if(!flag) {
            break;
        }
    }
}

/* 鸡尾酒排序
 * 右端左移，从左往右排序
 * 左端右移，从右往左排序
 * 旗标
 *
 * 鸡尾酒排序等于是冒泡排序的轻微变形。
 * 不同的地方在于从低到高然后从高到低，
 * 而冒泡排序则仅从低到高去比较序列里的每个元素。
 * 他可以得到比冒泡排序稍微好一点的效能，
 * 原因是冒泡排序只从一个方向进行比对（由低到高），每次循环只移动一个项目。
 * 以序列(2,3,4,5,1)为例，鸡尾酒排序只需要访问一次序列就可以完成排序，
 * 但如果使用冒泡排序则需要四次。
 * 但是在乱数序列的状态下，鸡尾酒排序与冒泡排序的效率都很差劲。
 */
void shaker_sort(int *d, int n)
{
    int l = 0;
    int r = n-1;
    int i, flag;

    if(!d) {
        return;
    }

    while(l < r) {
        flag = 0;
        for(i = l; i < r; i++) {
            if(d[i] > d[i+1]) {
                swap(d+i, d+i+1);
                flag = 1;
            }
        }
        r--;
        if(!flag) {
            break;
        }

        flag = 0;
        for(i = r; i > l; i--) {
            if(d[i] < d[i-1]) {
                swap(d+i, d+i-1);
                flag = 1;
            }
        }
        l++;
        if(!flag) {
            break;
        }
    }
}

/* 选择排序（Selection sort）
 * 是一种简单直观的排序算法。
 * 它的工作原理如下:
 * 首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，
 * 然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
 * 以此类推，直到所有元素均排序完毕。
 * 选择排序的主要优点与数据移动有关。
 * 如果某个元素位于正确的最终位置上，则它不会被移动。
 * 选择排序每次交换一对元素，它们当中至少有一个将被移到其最终位置上，
 * 因此对n个元素的表进行排序总共进行至多n-1次交换。
 * 在所有的完全依靠交换去移动元素的排序方法中，选择排序属于非常好的一种。
 */
void select_sort(int *d, int n)
{
    int i, j, min;
 
    if(!d || (n < 2)) {
        return;
    }
    
    for(i = 0; i < n-1; i++) {
        min = i;
        for(j = i+1; j <= n-1; j++) {
            if(d[min] > d[j]) {
                min = j;
            }
        }
        if(min != i) {
            swap(d+i, d+min);
        }
    }
}

/*
 * 插入排序（英语：Insertion Sort）是一种简单直观的排序算法。
 * 它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
 * 插入排序在实现上，通常采用in-place排序（即只需用到O(1)的额外空间的排序），
 * 因而在从后向前扫描过程中，需要反复把已排序元素逐步向后挪位，为最新元素提供插入空间。
 */
void insertion_sort(int *d, int n)
{
    int i, j, t;

    if(!d || (n < 2)) {
        return;
    }

    for(i = 1; i < n; i++) {
        t = d[i];        
        for(j = i-1; j >= 0; j--) {
            if(d[j] > t) {
                d[j+1]=d[j];
            } else {
                break;
            }
        }
        d[j+1] = t;
    }
}

/* 加快排序的基本原则之一，是让后一次的排序尽量利用前次的排序结果
 * shell排序法即是基于这一概念来改良插入排序法
 * 分组插入，缩小增量排序
 *
 * 希尔排序通过将比较的全部元素分为几个区域来提升插入排序的性能。
 * 这样可以让一个元素可以一次性地朝最终位置前进一大步。
 * 然后算法再取越来越小的步长进行排序，算法的最后一步就是普通的插入排序，
 * 但是到了这步，需排序的数据几乎是已排好的了（此时插入排序较快）。
 * 假设有一个很小的数据在一个已按升序排好序的数组的末端。如果用复杂度为O(n2)的排序（冒泡排序或插入排序），
 * 可能会进行n次的比较和交换才能将该数据移至正确位置。
 * 而希尔排序会用较大的步长移动数据，所以小数据只需进行少数比较和交换即可到正确位置。
 */
void shell_sort(int *d, int n)
{
    int i, j, k, gap, t;

    if(!d || (n < 2)) {
        return; 
    }

    gap = n/2;

    while(gap > 0) {
        for(i = 0; i < gap; i++) { // 分组
            // 以下仍然为插入排序
            for(j = i+gap; j < n; j+=gap) {
                t = d[j];                 
                for(k=j-gap; k >= 0; k-=gap) {
                    if(d[k] > t) {
                        d[k+gap] = d[k];
                    } else {
                        break;
                    }
                }
                d[k+gap] = t;
            } 
        }
        gap = gap/2;
    }
}

// 轴取最左端元素
// 其余从两端往中间走
void quick_sort(int *d, int n)
{
    int l, r, flag;

    if(!d || (n<2)) {
        return;
    }

    flag = d[0];
    l = 1;
    r = n-1;
    while(1) {
        // 从右侧找出大于flag的元素
        while(d[r]>flag) {  // flag 是一道屏障，保证r>0
            r--;
        }

        // 从左侧找出小于flag的元素
        while((l < r) && (d[l]<=flag)) {
            l++;
        }

        // 调换找出的两元素
        if(l < r) {
            swap(d+l, d+r);
        } else {
            break;
        }
    }
    swap(d, d+r);

    // flag定位后，不需再参与排序
    //quick_sort(d, r+1);   // 两个相同数排序，当flag再次参与排序会陷入死循环
    quick_sort(d, r);       // 得保证待排序数比上次少，否则会陷入死循环
    quick_sort(d+l, n-l);
}

// 快速排序法的加速在于轴的选择
// 轴取中间，往中间走
void quick_sort2(int *d, int n)
{
    int l, r;
    int i, j, s;

    if((!d) || (n < 2)) {
        return;
    }

    s = d[(0+n-1)/2]; // 轴取中间, 并置换到最后
    swap(d+n-1, d+(n-1)/2);
    l = 0;
    r = n-2;

    while(1) {
        while(d[l] < s) {
            l++;    // 必然止步于n-1
        }
        while((r>=0) && (d[r] >= s)) {
            r--;    // 第一次最差止步于s, 后续止步于换到前面的j值
        }

        if(l < r) {
            swap(d+l, d+r);
        } else {
            break;
        }
    }
    swap(d+n-1, d+l);

    // flag定位后，不需再参与排序
    // 保证下次排序数少一,以免陷入死循环
    quick_sort2(d, l);
    quick_sort2(d+l+1, n-1-l);
}

// 轴取最右端, 可选中间的置换到最后
// 均从左端往右走
void quick_sort3(int *d, int n)
{
    int i, j, s;

    if((!d) || (n < 2)) {
        return;
    }

    // i, j逐渐增大，但最大只能到r
    i = -1;
    j = 0;
    s = d[n-1];
    while(j <= n-1) {
        while(d[j] > s) {
            j++;
        }
        swap(d+j, d+i+1);
        i++;
        j++;
    }

    quick_sort3(d, i);
    quick_sort3(d+i+1, n-1-i);
}

/*
 * 堆排序
 *
 */
void heap_sort(int *d, int n)
{

}

/*
 * 归并排序
 *
 */
void merge_sort(int *d, int n)
{

}

/*
 * 计数排序 - 排非负整数
 * 创建一个长度相同的辅助数组，先存个数，后存续数
 * 基数排序应用到计数排序
 */
void counting_sort(int *d, int n)
{
    int i, max;
    int *sorted_arr;
    int *count_arr;

    if(!d || (n<2)) {
        return;
    }

    max = d[0];
    for(i = 1; i < n; i++) {
        if(d[i] > max) {
            max = d[i];
        }
    } 

    count_arr = (int *)malloc((max+1)*sizeof(int));
    if(count_arr == NULL) {
        return;
    }
    sorted_arr = (int *)malloc(n*sizeof(int)); 
    if(sorted_arr == NULL) {
        free(count_arr);
        return;
    }

    memset(count_arr, 0, max*sizeof(int));
    for(i = 0; i < n; i++) {
        count_arr[d[i]]++;    
    }
    for(i = 1; i <= max; i++) {
        count_arr[i] += count_arr[i-1]; 
    }

    for(i=n-1; i>=0; i--) {
        sorted_arr[--count_arr[d[i]]] = d[i];                
    }
    for(i = 0; i < n; i++) {
        d[i] = sorted_arr[i];
    }

    free(count_arr);
    free(sorted_arr);
}

/*
 * 桶排序（Bucket sort）或所谓的箱排序，是一个排序算法，
 * 工作的原理是将数组分到有限数量的桶里。
 * 每个桶再个别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序）。
 * 桶排序是鸽巢排序的一种归纳结果。
 * 当要被排序的数组内的数值是均匀分配的时候，桶排序使用线性时间（Θ(n)）。
 * 但桶排序并不是比较排序，他不受到O(n log n)下限的影响。
 * 桶排序以下列程序进行：
 * 1)设置一个定量的数组当作空桶子。
 * 2)寻访序列，并且把项目一个一个放到对应的桶子去。
 * 3)对每个不是空的桶子进行排序。
 * 4)从不是空的桶子里把项目再放回原来的序列中。
 *
 * 桶排序
 * 分类			排序算法
 * 数据结构		数组
 * 时间复杂度		O(n^2)
 * 平均时间复杂度	O(n+k)
 * 空间复杂度		O(n*k)
 *
 */
struct link {
    int v;
    struct link *next;
};
void bucket_sort(int *d, int n)
{
    struct link *t = NULL;
    struct link *prev;
    struct link **bucket = NULL;
    int max;
    int i, j, rc = 0;

    if(!d || (n<2)) {
        return;
    }

    bucket = (struct link **)malloc(sizeof(*bucket) * n); 
    if(!bucket) {
        return;
    }

    // get maximum value
    max = d[0]; 
    for(i = 1; i < n; i++) {
        if(max < d[i]) {
            max = d[i];
        }
    }

    for(i = 0; i < n; i++) {
        j = d[i]*(n-1)/max;

        // allocate a new node
        t = (struct link *)malloc(sizeof(*t));
        if(!t) {
            rc = -1; 
            break;
        }
        t->v = d[i];

        // insert a new node to bucket
        if(bucket[j] == NULL) {
                bucket[j] = t;
                t->next = NULL;
        } else {
            if(t->v < bucket[j]->v) {
                t->next = bucket[j];
                bucket[j] = t;
            } else {
                prev = bucket[j];                        
                while(1) {
                    if(prev->next) {
                        if(t->v < prev->next->v) {
                            t->next = prev->next;
                            prev->next = t;
                            break;
                        } else {
                            prev = prev->next;
                        }
                    } else {
                        prev->next = t;
                        t->next = NULL;
                        break;
                    }
                }
            }
        }
    }

    if(!rc) {
        for(i = 0, j = 0; i < n; i++) {
            t = bucket[i];
            while(t) {
                d[j++] = t->v;

                t = t->next;
            }
        }
    }

    for(i = 0; i < n; i++) {
        t = bucket[i];
        while(t) {
            bucket[i] = t->next;
            free(t);
            t = bucket[i];
        }
    }
    free(bucket);
}

/*
 * 基数排序(Radix Sort)是计数排序的扩展，基本思想是：
 * 将整数按位数切割成不同的数字，然后按每个位数分别比较。
 * 具体做法是：
 * 将所有待比较数值统一为同样的数位长度，数位较短的数前面补零。
 * 然后，从最低位开始，依次进行一次排序。
 * 这样从最低位排序一直到最高位排序完成以后, 数列就变成一个有序序列。
 * 排高位时，低位已排好序。
 * 此时排高位的方法需要是稳定的，否则已排好的低位会被打乱
 */
void radix_sort(int *d, int n)
{
    int max = 0;
    int i;
    int significant_digit = 1;
    int bucket[10];
    int *sorted;
    
    if(!d || (n < 2)) {
        return;
    }

    sorted = (int *)malloc(sizeof(int)*n);
    if(!sorted) {
        return;
    }

    // get max 
    max = d[0];
    for(i = 1; i < n; i++) {
        if(max < d[i]) {
            max = d[i];
        }
    }

    while(max/significant_digit > 0) {
        memset(bucket, 0, sizeof(bucket));
        
        for(i = 0; i < n; i++) {
            bucket[d[i]/significant_digit%10]++; // 个数
        }
        for(i = 1; i < 10; i++) {
            bucket[i] += bucket[i-1]; // 顺序
        }

        // 从后往前放是为了保证稳定性
        // 个位排好的顺序在排十位时仍然保持
        for(i = n-1; i >= 0; i--) {
            sorted[--bucket[d[i]/significant_digit%10]] = d[i];
        }

        for(i = 0; i < n; i++) {
            d[i] = sorted[i];
        }

        significant_digit *= 10;
    }

    free(sorted);
}
