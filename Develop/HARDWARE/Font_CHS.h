#ifndef __Font_CHS_H
#define __Font_CHS_H

#include "SYS.h"
#include "Font_CHS.h"
#define USE_CHS_F16X16 ENABLE
#if USE_CHS_F16X16 == ENABLE
// CHS_F16X16[X][64]
// 单(0) 片(1) 机(2) 开(3) 发(4)
extern uc8 CHS_F16X16[5][64];
#endif
#endif
