/* ============================================================================
 * C10 任务区 · 结构体 struct（定义 / typedef / 成员访问 / ->）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c10_tasks.c -o c10_tasks.exe
 * 运行：c10_tasks.exe
 *
 * 模范示例在 c10_hello.c 里，写之前先看一遍。
 *
 * 【今天要记的坑，按踩中频率排序】
 *   1. struct 定义结尾的分号不能漏
 *   2. . 用于结构体变量，-> 用于结构体指针，别混
 *   3. 结构体能整体赋值，数组不能 —— 别把这条搞反
 *   4. 初始化用花括号 { }，按顺序对应成员
 *   5. sizeof(结构体) 可能大于成员之和（内存对齐），别手算
 * ==========================================================================*/

#include <stdio.h>

/* 任务 0：定义你今天要用的类型
 * 用 typedef 定义一个 Motor（电机）结构体，建议成员：
 *     int    rpm;        // 当前转速
 *     int    target_rpm; // 目标转速
 *     float  current;    // 工作电流（安培）
 *     char   status;     // 状态：'R'运行 'S'停止 'F'故障
 * 写在下面答题区的外面（main 上面），这样整个文件都能用它。
 */


int main(void) {

    /* 任务 1：声明并初始化
     * 用 typedef 定义 Sensor 类型（棚号 char / 温度 int / 湿度 float）。
     * 声明两个变量：一个用花括号初始化，一个逐成员赋值。
     * 各打印一遍，确认两种方式效果一样。
     */


    /* 任务 2：typedef 的价值
     * 同一个结构体，写两个版本对比：
     *     struct RawSensor { ... };          → 声明变量必须写 struct RawSensor s;
     *     typedef struct { ... } Sensor;     → 直接写 Sensor s;
     * 体会少了多少字，再也不用纠结。以后默认用 typedef 版本。
     * 顺便打印 sizeof(struct RawSensor) 和 sizeof(Sensor)，应该一样。
     */


    /* 任务 3：结构体整体赋值
     *     Sensor a = {'A', 28, 62.5f};
     *     Sensor b = a;              // 整体拷贝
     * 打印 b 的三个成员，确认复制过来了。
     * 然后改 b.temp = 31，再打印 a 和 b —— a 没被影响（是拷贝不是引用）。
     * 对照实验：int arr1[3] = {1,2,3}; int arr2[3]; arr2 = arr1;  ← 编译报错
     *   记住这条：结构体能整体赋值，数组不能。c11 会解释 why。
     */


    /* 任务 4：用 -> 改写（重点）
     * 把下面这句用两种方式写出来：
     *     Sensor s = {'A', 28, 62.5f};
     *     Sensor *p = &s;
     *     printf("%d", (*p).temp);    // 啰嗦写法
     *     printf("%d", p->temp);      // 箭头写法
     * 两种都要打出来验证。-> 就是 (*p). 的简写，只是写着顺手。
     * 再写一个函数 void show(const Sensor *ps)，里面用 ps->xxx 打印，在 main 调用。
     */


    /* 任务 5：给真实设备建模（今天的重点）
     * 用任务 0 定义的 Motor 结构体：
     *     声明一台电机，初始化为 {1500, 1500, 3.2f, 'R'}
     *     写函数 void print_motor(const Motor *m) 打印一行状态
     *     写函数 int is_overload(const Motor *m)，电流 > 5.0 或状态=='F' 返回 1
     *     写函数 void set_target(Motor *m, int target)，注意这里不能用 const！
     *           （因为要改结构体内容）
     * 在 main 里：打印 → 改目标转速为 2000 → 再打印 → 判过载。
     * 想一想：为什么有的参数要加 const 有的不要？——看你打不打算改它。
     */


    /* 任务 6（★）：故意写错，认识三种报错
     * 一次只试一处：
     *     struct Sensor { int a; }          // 漏了结尾分号，下一行全崩
     *     Sensor s = {'A', 28};             // 初始化项不够，缺的补 0（其实合法，但要看懂）
     *     Sensor *p = &s;  printf("%d", p.temp);    // 指针用了 . ，应该编译不过
     *     Sensor s;  printf("%d", s->temp);         // 变量用了 -> ，同样应该编译不过
     * 后两条 -Wall 会明确告诉你「写法反了」，编译器在这里其实挺贴心的。
     */


    /* 任务 7（★★）：三棚巡检台账
     * 定义 Sensor 类型，用数组存三个棚的数据：
     *     Sensor sheds[3] = { {'A',28,62.5f}, {'B',31,35.0f}, {'C',19,88.0f} };
     * 写三个函数：
     *     void print_all(const Sensor arr[], int len);       // 打印表格
     *     const Sensor* find_hottest(const Sensor arr[], int len);  // 返回温度最高的那个的地址
     *     int  count_abnormal(const Sensor arr[], int len);  // 统计温度>=35或<10的个数
     * main 里调用它们，最后打印：
     *     最热的是 X 棚，YY 度
     *     异常棚数：N
     * 门槛：find_hottest 返回的是指针 —— 这是 C 里「返回一个大数据」的标准做法，
     *       不用拷贝整个结构体，只回一个地址。这个套路以后会反复用到。
     */


    return 0;
}
