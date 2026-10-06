/* ============================================================================
 * C10 · 结构体 struct（自定义类型 / 成员访问 / typedef）
 *                                          （对应 Python day13_class）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c10_hello.c -o c10_hello.exe
 * 运行：c10_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 *
 * ⚠️ 这是「用 C 做工程」的转折点：从这一刻起你能给真实设备建模了。
 * ==========================================================================*/

/* ---------------- 模范示例 1：定义一个结构体类型 --------------------------
 * Python 里你写 class Sensor: ... ，C 里用 struct 把几个字段捆成一包。
 *
 *     struct Sensor {
 *         char  shed;      // 棚号
 *         int   temp;      // 温度
 *         float humi;      // 湿度
 *     };                   // ← 这个分号别忘了，新手最常漏
 *
 * 它只是一个「类型图纸」，本身不占内存；用它声明变量才占。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：声明变量、赋值、访问成员 --------------------
#include <stdio.h>
#include <string.h>

struct Sensor {
    char  shed;
    int   temp;
    float humi;
};

int main(void) {
    struct Sensor s1 = {'A', 28, 62.5f};     // 按成员顺序初始化

    printf("棚号：%c\n", s1.shed);           // 用 . 访问成员
    printf("温度：%d\n", s1.temp);
    printf("湿度：%.1f\n", s1.humi);

    s1.temp = 31;                            // 改成员
    printf("改后温度：%d\n", s1.temp);

    struct Sensor s2;                        // 先声明后赋值
    s2.shed = 'B';
    s2.temp = 25;
    s2.humi = 70.0f;

    struct Sensor s3 = s1;                   // 整体赋值：成员逐个拷贝
    printf("s3 拷贝自 s1：%c %d %.1f\n", s3.shed, s3.temp, s3.humi);
    return 0;
}
 *
 * 注意：结构体可以整体赋值（这跟数组不同，数组不能整体赋值）。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：typedef 起个短名字 --------------------------
 * 每次写 struct Sensor 太啰嗦，用 typedef 起了别名就清爽了：
 *
 *     typedef struct {
 *         char  shed;
 *         int   temp;
 *         float humi;
 *     } Sensor;                             // 别名叫 Sensor
 *
 *     Sensor s = {'A', 28, 62.5f};          // 不用再写 struct
 *
 * 工程代码里几乎都是这么写的，早点习惯。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：结构体大小与内存对齐 ------------------------
 * printf("%zu", sizeof(Sensor));   // 可能是 12，不是 1+4+4=9
 *
 * 因为 CPU 读内存喜欢「对齐」，编译器会在成员之间塞空位。
 * 初学阶段知道有这回事就行，别手算大小，用 sizeof 拿。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 5：结构体指针与 -> 操作符 ----------------------
 * 结构体指针访问成员时，(*p).temp 太难看，C 给了专用箭头：
 *
 *     Sensor s = {'A', 28, 62.5f};
 *     Sensor *p = &s;
 *     printf("%d", p->temp);        // 等价于 (*p).temp
 *
 * ->  专门用于「结构体指针访问成员」
 * .   用于「结构体变量访问成员」
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>

typedef struct {
    char  shed;
    int   temp;
    float humi;
} Sensor;

void print_sensor(const Sensor *ps);
int  need_irrigation(const Sensor *ps);

int main(void) {
    Sensor a = {'A', 28, 62.5f};
    Sensor b = {'B', 31, 35.0f};
    Sensor c = {'C', 19, 88.0f};

    printf("Sensor 类型占 %zu 字节\n\n", sizeof(Sensor));

    printf("---- 巡检明细 ----\n");
    print_sensor(&a);
    print_sensor(&b);
    print_sensor(&c);

    printf("\n---- 灌溉判定 ----\n");
    Sensor list[] = {a, b, c};
    for (int i = 0; i < 3; i++) {
        if (need_irrigation(&list[i])) {
            printf("%c 棚需要灌溉\n", list[i].shed);
        } else {
            printf("%c 棚暂不需要\n", list[i].shed);
        }
    }

    return 0;
}

// 打印单个传感器的信息（用指针 + -> 访问）
void print_sensor(const Sensor *ps) {
    printf("%c棚  温度 %2d 度  湿度 %.1f%%\n", ps->shed, ps->temp, ps->humi);
}

// 又热又干才灌溉
int need_irrigation(const Sensor *ps) {
    return ps->temp > 25 && ps->humi < 40.0f;
}
