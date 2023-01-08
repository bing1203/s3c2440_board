#include "framebuffer.h"
#include "math.h"

void draw_circle(int x, int y, int r, int color)
{
    int a, b, num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)          // 1/8圆即叄1�7
    {
        fb_put_pixel(x + a, y - b,color); // 0~1
        fb_put_pixel(x - a, y - b,color); // 0~7
        fb_put_pixel(x - a, y + b,color); // 4~5
        fb_put_pixel(x + a, y + b,color); // 4~3
 
        fb_put_pixel(x + b, y + a,color); // 2~3
        fb_put_pixel(x + b, y - a,color); // 2~1
        fb_put_pixel(x - b, y - a,color); // 6~7
        fb_put_pixel(x - b, y + a,color); // 6~5
        
        a++;
        num = (a * a + b * b) - r*r;
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}

void draw_circle_width(int x, int y, int r, int color, int level)
{
    int a = 0;
    int b = 0;

    for (a = 0; a <= r + 5; a++)
    {
        b = sqrt(r * r - a * a);
        fb_put_pixel(x + a, y + b,color);
        fb_put_pixel(x + a, y - b,color);
        fb_put_pixel(x - a, y + b,color);
        fb_put_pixel(x - a, y - b,color);
    }
}


void fill_fb(int start_x, int end_x, int start_y, int end_y, unsigned int val)
{
    int i, j;
    for(i = start_y; i < end_y; i++)
    {
        for(j = start_x; j < end_x; j++)
        {
			fb_put_pixel(j, i, val);
        }
    }
}

void draw_line(int x1,int y1,int x2,int y2,int color)
{
    int dx,dy,e;
    dx=x2-x1; 
    dy=y2-y1;
    if(dx>=0)
    {
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 1/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    fb_put_pixel(x1,y1,color);
                    if(e>0){y1+=1;e-=dx;}   
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 2/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    fb_put_pixel(x1,y1,color);
                    if(e>0){x1+=1;e-=dy;}   
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 8/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    fb_put_pixel(x1,y1,color);
                    if(e>0){y1-=1;e-=dx;}   
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 7/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    fb_put_pixel(x1,y1,color);
                    if(e>0){x1+=1;e-=dy;}   
                    y1-=1;
                    e+=dx;
                }
            }
        }   
    }
    else //dx<0
    {
        dx=-dx;     //dx=abs(dx)
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 4/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    fb_put_pixel(x1,y1,color);
                    if(e>0){y1+=1;e-=dx;}   
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 3/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    fb_put_pixel(x1,y1,color);
                    if(e>0){x1-=1;e-=dy;}   
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 5/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    fb_put_pixel(x1,y1,color);
                    if(e>0){y1-=1;e-=dx;}   
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 6/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    fb_put_pixel(x1,y1,color);
                    if(e>0){x1-=1;e-=dy;}   
                    y1-=1;
                    e+=dx;
                }
            }
        }   
    }
}





