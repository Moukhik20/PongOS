#ifndef PONG_H
#define PONG_H

#include "kernel.h"
#include "vga.h"
#include "keyboard.h"
#include "utils.h"
#include "bitmap.h"

#define VIRTUALBOX



#define RECT_SIZE      6


#ifdef QEMU
    #define RECT_SPEED_X   6
    #define RECT_SPEED_Y   6
#endif


#ifdef VIRTUALBOX
    #define RECT_SPEED_X   2
    #define RECT_SPEED_Y   2
#endif


#define PAD_POS_X    VGA_MAX_WIDTH - PAD_WIDTH - 1
#define PAD_WIDTH    6
#define PAD_HEIGHT   50


#ifdef QEMU
    #define PAD_SPEED    20
#endif


#ifdef VIRTUALBOX
    #define PAD_SPEED    6
#endif


void pong_game();


#endif
