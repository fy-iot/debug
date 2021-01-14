#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdarg.h>
#include <stdio.h>
/**
 * @brief 串口打印功能
 * 1. 打印串口可切换
 * 2. 类似printf,打印参数列表可变
 * 3. 支持4种打印级别
 * 4. 支持颜色打印
 * 5. 支持HEX格式打印
 * 
 */


typedef enum 
{
    LOG_LEVEL_ERROR  = 0U,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
}log_info_e;
typedef struct
{   
    log_info_e log_level;  ///< LOG 等级
}log_t;

static log_t  s_logger;
int log_level_set(log_info_e level);
log_info_e log_level_get(void);


void my_printf(const char *fmt, ...);




/************ config  *****************/

#define DEBUG           ///< 打开调试开关
#define DEBUG_COLOR     ///< 打开颜色模式
#define DEBUG_CONTEXT   ///< 输出调试上下文：file, func, linenumber 

#define DEBUG_STDIO

/************ config end ******************/



/******************************** debug color ***********************/
/*
* The color for terminal (foreground)
* BLACK    30
* RED      31
* GREEN    32
* YELLOW   33
* BLUE     34
* PURPLE   35
* CYAN     36
* WHITE    37
*/

#ifdef DEBUG_COLOR
    #define DEBUG_COLOR_HDR(color_n)    \
        my_printf("\033["#color_n"m")
    #define DEBUG_COLOR_HDR_END       \
        my_printf("\033[0m\n")

#else
    #define DEBUG_LOG_HDR(color_n)\
    #define DEBUG_LOG_HDR_END       \
        my_printf("\n")

#endif ///< END DEBUG_COLOR

/********************************debug color**************************************/


#ifdef DEBUG_CONTEXT    
    #define LOG_HEAER " %s  %s:%d ]  \n"
#else  
    #define LOG_HEAER " ]  "
#endif
//my_printf(log_tag LOG_HEAER, fmt, __FILE__,__func__, __LINE__,##__VA_ARGS__);   

#ifdef DEBUG


    #define dbg_log_line(log_tag, color_n, fmt, ...)\
        do{ \
               DEBUG_COLOR_HDR(color_n);    \
               printf(log_tag LOG_HEAER fmt, __FILE__, __func__, __LINE__,##__VA_ARGS__);   \
                DEBUG_COLOR_HDR_END;    \
        }while(0)



    #define LOG_E(fmt, ...) do{\
        if(log_level_get() >= LOG_LEVEL_ERROR)\
        dbg_log_line("[ Error ", 31, fmt, ##__VA_ARGS__);}\
    while(0)
    #define LOG_W(fmt, ...) do{\
        if(log_level_get() >= LOG_LEVEL_WARNING)\
        dbg_log_line("[ Warning ", 33, fmt, ##__VA_ARGS__);}\
    while(0)

    #define LOG_I(fmt, ...) do{\
    if(log_level_get() >= LOG_LEVEL_INFO)\
    dbg_log_line("[ Info ", 32, fmt, ##__VA_ARGS__);}\
    while(0)

    #define LOG_D(fmt, ...) do{\
    if(log_level_get() >= LOG_LEVEL_DEBUG)\
    dbg_log_line("[ Debug ", 0, fmt, ##__VA_ARGS__);}\
    while(0)

#else
    #define LOG(fmt, ...)
#endif

#endif







