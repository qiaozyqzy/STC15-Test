#ifndef __OLEDFONT_H
#define __OLEDFONT_H

#include "SYS.h"
uc8 Hzk[][32] = {
    {0x00, 0x00, 0xF0, 0x10, 0x10, 0x10, 0x10, 0xFF, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x0F, 0x04, 0x04, 0x04, 0x04, 0xFF, 0x04, 0x04, 0x04, 0x04, 0x0F, 0x00, 0x00, 0x00}, /*"��",0*/
    {0x40, 0x40, 0x40, 0x5F, 0x55, 0x55, 0x55, 0x75, 0x55, 0x55, 0x55, 0x5F, 0x40, 0x40, 0x40, 0x00},
    {0x00, 0x40, 0x20, 0x0F, 0x09, 0x49, 0x89, 0x79, 0x09, 0x09, 0x09, 0x0F, 0x20, 0x40, 0x00, 0x00}, /*"��",1*/
    {0x00, 0xFE, 0x02, 0x42, 0x4A, 0xCA, 0x4A, 0x4A, 0xCA, 0x4A, 0x4A, 0x42, 0x02, 0xFE, 0x00, 0x00},
    {0x00, 0xFF, 0x40, 0x50, 0x4C, 0x43, 0x40, 0x40, 0x4F, 0x50, 0x50, 0x5C, 0x40, 0xFF, 0x00, 0x00}, /*"԰",2*/
    {0x00, 0x00, 0xF8, 0x88, 0x88, 0x88, 0x88, 0xFF, 0x88, 0x88, 0x88, 0x88, 0xF8, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x1F, 0x08, 0x08, 0x08, 0x08, 0x7F, 0x88, 0x88, 0x88, 0x88, 0x9F, 0x80, 0xF0, 0x00}, /*"��",3*/
    {0x80, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0xE2, 0xA2, 0x92, 0x8A, 0x86, 0x82, 0x80, 0x80, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"��",4*/
    {0x24, 0x24, 0xA4, 0xFE, 0xA3, 0x22, 0x00, 0x22, 0xCC, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x08, 0x06, 0x01, 0xFF, 0x00, 0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0xFF, 0x02, 0x02, 0x02, 0x00}, /*"��",5*/
    {0x10, 0x10, 0x10, 0xFF, 0x10, 0x90, 0x08, 0x88, 0x88, 0x88, 0xFF, 0x88, 0x88, 0x88, 0x08, 0x00},
    {0x04, 0x44, 0x82, 0x7F, 0x01, 0x80, 0x80, 0x40, 0x43, 0x2C, 0x10, 0x28, 0x46, 0x81, 0x80, 0x00}, /*"��",6*/
};
#endif