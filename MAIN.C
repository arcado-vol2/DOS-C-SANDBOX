#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define SET_MODE 0x00
#define VIDEO_INT 0x10
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03
#define SCREEN_HIGHT 200
#define SCREEN_WIDHT 320
typedef unsigned char byte;

byte far *VGA = (byte far *)0xA0000000L;


#define SETP(x,y,c) *(VGA+(x)+(y)*SCREEN_WIDHT) = c
#define GETP(x,y) *(VGA + (x) + (y) * SCREEN_WIDHT)

/*assume that FF is transperent*/
const byte GNOME_SPRITE[10][10] = {
        {0xff, 0xff, 0xff, 0xff, 0x0c, 0x0c, 0xff, 0xff, 0xff, 0xff},
        {0xff, 0xff, 0xff, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xff, 0xff},
        {0xff, 0xff, 0xff, 0x5a, 0x5a, 0x5a, 0x5a, 0xff, 0xff, 0xff},
        {0xff, 0xff, 0x5a, 0x00, 0x5a, 0x5a, 0x00, 0x5a, 0xff, 0xff},
        {0xff, 0xff, 0x5a, 0x5a, 0x0c, 0x0c, 0x5a, 0x5a, 0xff, 0xff},
        {0xff, 0xff, 0xb8, 0xb8, 0x5a, 0x5a, 0xb8, 0xb8, 0xff, 0xff},
        {0xff, 0xff, 0xb8, 0xb8, 0xb8, 0xb8, 0xb8, 0xb8, 0xff, 0xff},
        {0xff, 0xff, 0x0c, 0xb8, 0xb8, 0xb8, 0xb8, 0x0c, 0xff, 0xff},
        {0xff, 0xff, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xff},
        {0xff, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0xff}
};

const byte ARROW_UP[3][3]
void setVideoMode(char mode) {
    union REGS regs;
    regs.h.ah = SET_MODE;
    regs.h.al = mode;
    int86(VIDEO_INT, &regs, &regs);
}

void draw_bg(){
      int x, y;
    for (x = 0; x < SCREEN_WIDHT; ++x){
        for (y = 0; y < SCREEN_HIGHT; ++y){
                SETP(x, y, 0x0F);
                
        }
    }  
}

void draw_gnome(int px, int py){
    int x, y;
    for (x = 0; x < 10; ++x){
        for (y = 0; y < 10; ++y){
                if (GNOME_SPRITE[y][x]!=0xff){
                        SETP(px + x, py + y, GNOME_SPRITE[y][x]);
                }

                
        }
    }
}

int main(void) {
    char kc = 0;
    int x = 20;
    int y = 20;
    setVideoMode(VGA_256_COLOR_MODE);
    draw_bg();
    draw_gnome(x, y);
    

    while (kc != 0x1b) {
        kc = getch();
        if (kc == 0x00) {
            kc = getch();
            switch (kc)
            {
            case 0x48:
                y--;
                break;
            case 0x50:
                y++;
                break;
            case 0x4d:
                x++;
                break;
            case 0x4b:
                x--;
                break;
            default:
                break;
            }
        }
        draw_bg();
        draw_gnome(x, yud);
    }
    setVideoMode(TEXT_MODE);
    return 0;
}

