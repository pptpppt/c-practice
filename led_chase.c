/*====================================================================
 * led_chase.c  ——  8 路 LED 跑灯（花样版）
 *
 * 这一版和常见那种 "for 里 HAL_Delay(200) 左移一位" 的写法，换了三个东西：
 *
 *   1) 不用死等延时。改成【节拍 + 状态机】：
 *      每次循环先看"到点没有"，到点才翻灯。
 *      这样 CPU 空出来的时间可以顺手做按键扫描、串口收包。
 *      ——这是写嵌入式最重要的一个习惯，早养成早受益。
 *
 *   2) 不只一种动作。改成【花样表】：一个二维数组装 6 套动作，
 *      每套播 2 轮自动切下一套。想加花样 = 往数组里加一行，不用改逻辑。
 *
 *   3) 硬件被关进 led_write() 这一个函数里。
 *      换板子 / 换 IO 口，只改下面第 30 行开始的硬件段落，主循环一个字不用动。
 *
 * -------------------------------------------------------------------
 * 怎么编译：
 *   A. 先在电脑上跑一遍看效果（推荐先看这个）
 *        gcc led_chase.c -o led_chase.exe
 *        led_chase.exe
 *
 *   B. 烧到 STM32 上（STM32F103 为例）
 *        gcc ... -DEMBEDDED_BUILD
 *      也就是编译时加上宏 EMBEDDED_BUILD，代码就会切到硬件那一分支。
 *      前提：用 CubeMX 生成工程，把 PC0~PC7 配成 GPIO_Output，
 *      并把 "stm32f1xx_hal.h" 的头文件路径给到编译器。
 *      更省事的做法：把下面 #if 里的硬件段落抄进 CubeMX 生成的 main.c。
 *
 * -------------------------------------------------------------------
 * LED 位置约定： mask 的 bit0 = 最右边那颗灯
 *   bit:  7  6  5  4  3  2  1  0
 *   灯:   ① ② ③ ④ ⑤ ⑥ ⑦ ⑧        ← ⑧ 是最右
 *====================================================================*/

#include <stdio.h>
#include <stdint.h>

/*=====================================================================
 * 第一部分：硬件层  ——  只有这一段和具体板子有关
 *=====================================================================*/
#if defined(EMBEDDED_BUILD)

    #include "stm32f1xx_hal.h"          /* 用 F4/F0 就换成对应的头文件 */

    /* 8 颗 LED 接在同一个 GPIO 口的【连续 8 个脚】上，这样一条语句就能全写出去 */
    #define LED_GPIO_PORT   GPIOC
    #define LED_GPIO_SHIFT  0           /* 接 PC0~PC7 就是 0；接 PC8~PC15 改成 8 */
    #define LED_ACTIVE_LOW  0           /* 如果是"共阳接法"（IO 输出 0 才亮），改成 1 */

    static void led_write(uint8_t mask)
    {
        if (LED_ACTIVE_LOW) {
            mask = (uint8_t)(~mask);    /* 共阳：亮/灭的电平反过来 */
        }
        /* 先把这 8 个脚清零，再把新花样写进去。
         * 用 ODR 一次性写 8 位，比调 HAL_GPIO_WritePin 八次快得多也干净得多。 */
        LED_GPIO_PORT->ODR = (LED_GPIO_PORT->ODR & ~(0xFFu << LED_GPIO_SHIFT))
                           | ((uint32_t)mask   << LED_GPIO_SHIFT);
    }

#else
    /* 电脑上不能在终端里打印中文序言之外的内容（GBK / UTF-8 编码会打架），
     * 所以屏幕版统一用 ASCII 字符显示： # = 亮， . = 灭 */
    #include <time.h>
    #ifdef _WIN32
        #include <windows.h>            /* Sleep() */
    #else
        #include <unistd.h>             /* usleep() */
    #endif

    static void led_write(uint8_t mask)
    {
        int i;
        for (i = 7; i >= 0; i--) {      /* 从高位往低位打，屏幕上左边对应 bit7 */
            putchar((mask & (1u << i)) ? '#' : '.');
        }
        putchar('\r');                  /* 回车不换行 —— 同一行原地刷新，像真在跑 */
        fflush(stdout);
    }
#endif


/*=====================================================================
 * 第二部分：时间源  ——  状态机就靠它判断"到点没有"
 *=====================================================================*/
static uint32_t tick_ms(void)
{
#if defined(EMBEDDED_BUILD)
    return HAL_GetTick();               /* CubeMX 默认配好的 1ms 心跳 */
#else
    return (uint32_t)(clock() * 1000 / CLOCKS_PER_SEC);
#endif
}

static void delay_ms(uint32_t ms)
{
#if defined(EMBEDDED_BUILD)
    HAL_Delay(ms);
#elif defined(_WIN32)
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}


/*=====================================================================
 * 第三部分：花样表  ——  想改效果，只动这里
 *
 * 每一行 = 一套动作的 8 帧，# = 会亮的那颗
 *=====================================================================*/
#define PATTERN_LEN   8                 /* 每套动作几帧（改这里要同步改数组每行长度） */
#define PATTERN_CNT   6                 /* 一共几套动作 */
#define PATTERN_LOOP  2                 /* 每套动作连播几轮再换 */
#define FRAME_MS      100               /* 每一帧停多久 —— 跑得快慢调这个 */

static const uint8_t g_patterns[PATTERN_CNT][PATTERN_LEN] = {

    /* 0. 单灯右跑： ..#..... → .......#        最基础的一个灯挪过去 */
    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 },

    /* 1. 单灯左跑： #....... → # 在最左... 实际是往回跑 */
    { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },

    /* 2. 增长蛇：   一颗变两颗、三颗…最后全亮，然后整套动作重头再来 */
    { 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF },

    /* 3. 两侧对撞： 两边同时往中间跑，撞上（中间两颗亮）之后再散开回去 */
    { 0x81, 0x42, 0x24, 0x18, 0x24, 0x42, 0x81, 0x00 },

    /* 4. 中间开花： 从中间两颗往两边绽开到全亮，再收回中间 */
    { 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18, 0x00 },

    /* 5. 隔位+爆闪：1357 / 2468 交替跳四次，再全亮全灭闪两下 */
    { 0xAA, 0x55, 0xAA, 0x55, 0xFF, 0x00, 0xFF, 0x00 }
};


/*=====================================================================
 * 第四部分：主循环  ——  状态机，和硬件、和花样都无关
 *=====================================================================*/
#if defined(EMBEDDED_BUILD)
int main_led_chase(void)                /* 板子上：由 CubeMX 的 main() 调用它 */
#else
#define RUN_SECONDS 24                  /* 电脑上跑 24 秒自动收工 */
int main(void)
#endif
{
    uint8_t  pat  = 0;                  /* 当前播第几套花样   */
    uint8_t  step = 0;                  /* 当前播到第几帧     */
    uint8_t  loop = 0;                  /* 这套花样已播几轮   */
    uint32_t last = tick_ms();          /* 上一次换帧的时刻   */

#if !defined(EMBEDDED_BUILD)
    printf("8 路 LED 跑灯 —— 花样版\n");
    printf("屏幕上 # = 亮, . = 灭, 从左到右对应 bit7..bit0\n");
    printf("6 套花样轮流播，每套 %d 轮。Ctrl+C 可随时停。\n\n", PATTERN_LOOP);
    delay_ms(1200);                     /* 给人 1.2 秒读上面这三行 */
#endif

    while (1) {
        uint32_t now = tick_ms();

        /* 核心就这一句：时间没到，什么都不做。
         * 换成 delay() 死等的话，这几毫秒 CPU 就白白烧掉了。 */
        if (now - last >= FRAME_MS) {
            last = now;

            led_write(g_patterns[pat][step]);

            /* 推进到下一帧 */
            step++;
            if (step >= PATTERN_LEN) {
                step = 0;
                loop++;
                if (loop >= PATTERN_LOOP) {         /* 这套播够轮数了 */
                    loop = 0;
                    pat = (uint8_t)((pat + 1) % PATTERN_CNT);  /* 换下一套 */
                }
            }
        }

#if !defined(EMBEDDED_BUILD)
        if (now >= (uint32_t)RUN_SECONDS * 1000) {  /* 电脑上别跑成死循环 */
            printf("\n跑完了，一共 %d 套花样，每套 %d 帧。\n", PATTERN_CNT, PATTERN_LEN);
            break;
        }
        delay_ms(5);                    /* 让出 CPU，不然电脑上风扇会转起来 */
#endif
    }
    return 0;
}
