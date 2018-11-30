#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "../include/bresenham.h"

int main_old()
{
    int fd = -1;
    int ret = -1;
    char *fbp = NULL;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

    fd = open("/dev/fb0", O_RDWR);
    if(fd < 0)
    {
        printf("open file failed");
        return -1;
    }

    ret = ioctl(fd, FBIOGET_FSCREENINFO, &finfo);

    if(ret < 0)
    {
        printf("ioctrl failed");
        return -1;
    }

    ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);

    if(ret < 0)
    {
        printf("ioctrl failed");
        return -1;
    }

    long screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    fbp = (char *)mmap(NULL, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(NULL == fbp)
    {
        printf("mmap failed");
        return -1;
    }

    int x = 120;
    int y = 120;


    std::vector<Point> line;
    bresenham2D(line, 0, 0, 80, 120);

    for(int i=0; i<line.size(); i++)
    {
        printf(" %d-%d", line.at(i).x, line.at(i).y);
    }

    for(int i=0; i< line.size(); i++)
    {
        long location = line.at(i).x * (vinfo.bits_per_pixel / 8) + line.at(i).y  *  finfo.line_length;
        
        *(fbp + location) = 100;
        *(fbp + location + 1) = 15;
        *(fbp + location + 2) = 200;
        *(fbp + location + 3) = 0;

    }
    munmap(fbp, screensize);
    close(fd);

    return 0;
}

void printBlank()
{
    putchar(' ');
    putchar(' ');
}
void printMark()
{
    putchar('O');
    putchar('O');
}
int main()
{
    std::vector<Point> line;
    bresenham2D(line, 0, 0, 40, 50);
    char screen[100 * 100] = {0};
    int p=0;
    char mark_char = 'O';

    for(int i=0; i<line.size(); i++)
    {
        for(int j=0; j<line.at(i).x; j++)
        {
            screen[p++] = ' ';
            screen[p++] = ' ';
        }
        screen[p++] = mark_char;
        screen[p++] = mark_char;
        if((i+1) <line.size())
        {
            int num = line.at(i+1).y - line.at(i).y;
            switch(num)
            {
                case 0:
                    screen[p++] = mark_char;
                    screen[p++] = mark_char;
                    i++;
                    screen[p++] = '\n';
                    break;
                default:
                    for(int i=0; i< num; i++)
                    {
                        screen[p++] = '\n';
                    }
                    break;
            }
        }
    }
    for(int i=0; i<p; i++)
    {
        putchar(screen[i]);
    }
   putchar('\n'); 

    return 0;
}
