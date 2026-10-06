/* ============================================================================
 * C11 · 结构体数组 + 结构体指针（数据处理的主力）
 *                                          （对应 Python day14_oop_collab）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c11_hello.c -o c11_hello.exe
 * 运行：c11_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 * ==========================================================================*/

/* ---------------- 模范示例 1：结构体数组 ----------------------------------
#include <stdio.h>

typedef struct {
    char  shed;
    int   temp;
    float humi;
} Sensor;

int main(void) {
    Sensor list[3] = {
        {'A', 28, 62.5f},
        {'B', 31, 35.0f},
        {'C', 19, 88.0f}
    };

    for (int i = 0; i < 3; i++) {
        printf("%c棚 %2d度 %.1f%%\n", list[i].shed, list[i].temp, list[i].humi);
    }
    return 0;
}
 *
 * 二维数组 vs 结构体数组：
 *     int data[3][3]        只能存清一色的数字
 *     Sensor list[3]       每个元素能带多个不同类型的字段，还能按名字访问
 * 后者才是工程里处理「一批记录」的常规做法。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：遍历用指针，别传整个数组 --------------------
 * void print_all(const Sensor *arr, int len) {
 *     for (int i = 0; i < len; i++) {
 *         printf("%c", (arr + i)->shed);       // 指针偏移写法
 *         // 或者 printf("%c", arr[i].shed);   // 下标写法，等价
 *     }
 * }
 *
 * 结构体比 int 大得多（可能 12 字节以上），传指针能省掉整份拷贝。
 * 这就是为什么 C 代码里到处是 const XXX *arr。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：按某个成员排序（冒泡的通用版）---------------
#include <stdio.h>

typedef struct { char shed; int temp; } Sensor;

void sort_by_temp(Sensor arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j].temp < arr[j + 1].temp) {     // 从高到低
                Sensor t = arr[j];                   // 整体交换（结构体可以直接赋值）
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

int main(void) {
    Sensor list[3] = { {'A',28}, {'B',31}, {'C',19} };
    sort_by_temp(list, 3);
    for (int i = 0; i < 3; i++) { printf("%c %d\n", list[i].shed, list[i].temp); }
    return 0;
}
 * 输出：B 31 / A 28 / C 19
 *
 * 注意：排序会打乱原始顺序。想保留就得在结构体里多存一个「原始序号」字段，
 * 或者像 c04 任务 7 那样回原数组找下标。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：查找返回指针 --------------------------------
 * const Sensor *find_by_shed(const Sensor arr[], int len, char shed) {
 *     for (int i = 0; i < len; i++) {
 *         if (arr[i].shed == shed) { return &arr[i]; }
 *     }
 *     return NULL;                 // 没找到，用 NULL 表示
 * }
 *
 * 调用方必须判 NULL：
 *     const Sensor *p = find_by_shed(list, 3, 'B');
 *     if (p != NULL) { printf("%d", p->temp); }
 *
 * 这是 C 里「找不到怎么办」的标准答案 —— 返回空指针，而不是返回 -1 之类的魔法值。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>

typedef struct {
    char   shed;
    int    temp;
    float  humi;
} Sensor;

void print_all(const Sensor *arr, int len);
void sort_by_temp(Sensor arr[], int len);
const Sensor *find_by_shed(const Sensor arr[], int len, char shed);
Sensor hottest(const Sensor arr[], int len);

int main(void) {
    Sensor list[5] = {
        {'A', 28, 62.5f},
        {'B', 31, 35.0f},
        {'C', 19, 88.0f},
        {'D', 36, 30.0f},
        {'E', 24, 55.0f}
    };
    int len = sizeof(list) / sizeof(list[0]);

    printf("---- 原始台账 ----\n");
    print_all(list, len);

    printf("\n---- 按温度排序（高到低）----\n");
    sort_by_temp(list, len);
    print_all(list, len);

    printf("\n---- 按棚号查找 ----\n");
    const Sensor *p = find_by_shed(list, len, 'C');
    if (p != NULL) {
        printf("找到 C 棚：%d 度，湿度 %.1f%%\n", p->temp, p->humi);
    } else {
        printf("没有 C 棚\n");
    }

    printf("\n---- 最热的一棚 ----\n");
    Sensor h = hottest(list, len);
    printf("最热：%c 棚，%d 度\n", h.shed, h.temp);

    return 0;
}

void print_all(const Sensor *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%c棚  温度 %2d 度  湿度 %5.1f%%\n", arr[i].shed, arr[i].temp, arr[i].humi);
    }
}

void sort_by_temp(Sensor arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j].temp < arr[j + 1].temp) {
                Sensor t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

const Sensor *find_by_shed(const Sensor arr[], int len, char shed) {
    for (int i = 0; i < len; i++) {
        if (arr[i].shed == shed) { return &arr[i]; }
    }
    return NULL;
}

Sensor hottest(const Sensor arr[], int len) {
    int idx = 0;
    for (int i = 1; i < len; i++) {
        if (arr[i].temp > arr[idx].temp) { idx = i; }
    }
    return arr[idx];        // 返回一份拷贝，够用且安全
}
