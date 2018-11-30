#ifndef _BRESENHAM_H_
#define _BRESENHAM_H_
#include <vector>

struct Point
{
  int x;
  int y;
  Point(int x0, int y0):x(x0), y(y0){}
};

/*
 * @brief Raytrace a line and do some action at step
 * @param pv The vector contain the line point
 * @param x0 The starting x cordination
 * @param y0 The starting y cordination
 * @param x1 The ending x cordination
 * @param y1 Th ending y cordination
 */
void bresenham2D(std::vector<Point>& pv, int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    unsigned int abs_dx = abs(dx);
    unsigned int abs_dy = abs(dy);
    unsigned int abs_da;
    unsigned int abs_db;
    int step_a;
    int step_b;

    if(abs_dx > abs_dy)//If x is dominant
    {
        abs_da = abs_dx;
        abs_db = abs_dy;
        step_a = signed(dx);
        step_b = signed(dy);
    }
    else//y is dominant
    {
        abs_da = abs_dy;
        abs_db = abs_dx;
        step_a = dy >= 0 ? 1 : -1;
        step_b = dx >= 0 ? 1 : -1;
    }

    double error = 0.0; //偏差初始值
    double error_a = 0.5 * abs_da;//比较标准
    int a = x0;
    int b = y0;
    pv.push_back(Point(a, b));
    int end = abs_da - 1;//计算个数

    for(int i=0; i<end; i++)
    {
        error += abs_db;
        a += step_a;
        if(error > error_a)
        {
            error -= abs_da;
            b += step_b;
        }

        pv.push_back(Point(a, b));
    }
}

#endif
