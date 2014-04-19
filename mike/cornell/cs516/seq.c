#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include "shapes.h"

#define POS(array,x,y) array[((y)*size) + (x)]
#define GET_SECS() ((end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000))

void main(int argc, char **argv)
{
    double u1[256], u2[256];
    double max;
    double *ucurr, *unext, dt = 0.0001, t, dx, root2;
    int N = 3, x, y, i, hotx, hoty, size = 16;
    int *bitmap;
    struct timeval begin, end;
    double mflops, secs, j = 10.0;
    int val, localminx, localmaxx, localminy, localmaxy;

    if (argc != 2) { printf("usage: %s [barbell | rect | circle]\n", argv[0]); exit(-1); }

    if (!strcmp(argv[1], "rect")) {
        bitmap = (int *) rect;
        hotx = 6;
        hoty = 6;
        } else if (!strcmp(argv[1], "circle")) {
        bitmap = (int *) circle;
        hotx = hoty = size/2;
        } else {
        bitmap = (int *) barbell;
        hotx = hoty = 5;
    }

    dx = 4.0 / size;
    ucurr = (double *)u1;
    unext = (double *)u2;

    for(y=0;y < size;y++)
        for(x=0;x < size;x++) 
        POS(ucurr,x,y) = 0.0;

    POS(ucurr,hotx,hoty) = 1.0;
    ucurr[hoty*size+hotx] = 1.0;
    printf("entering...\n");

    /* Main temp. calculation loop */
    for(t=0; t<=0.25;t += dt) 
    {   
        max = 0.0;
        POS(ucurr,hotx,hoty) = 1.0;
        for(y=1; y < 16; y++)
            for(x=1; x < 16; x++)
            {
                if (POS(bitmap,x,y))
                    POS(unext,x,y) = POS(ucurr,x,y) +
                    dt / (6 * dx * dx) *
                    (4 * (POS(ucurr,x+1,y) + POS(ucurr,x-1,y) +
                          POS(ucurr,x,y+1) + POS(ucurr,x,y-1) -
                          4*POS(ucurr,x,y)) +
                     (4 * (POS(ucurr,x+1,y+1) + POS(ucurr,x+1,y-1) +
                           POS(ucurr,x-1,y+1) + POS(ucurr,x-1,y-1) -
                           4*POS(ucurr,x,y))));
            }

        /* "Swap" the arrays */
        if (unext == u1)
        {
            ucurr = u1;
            unext = u2;
        }
        else
        {
            ucurr = u2;
            unext = u1;
        }

        for(y=0;y < size;y++)
        {
            for(x=0;x < size;x++) 
            {
                if (bitmap[y*size +x])
                {
                    if (POS(ucurr,x,y) != 0.0)         
                        val = 15 + (int) log10(POS(ucurr,x,y)/log10(2));
                    else
                        val = 1;
                    if (val < 1)
                        val = 1;
                    printf("%d ",val);
                }
                else
                    printf("0 ");
            }
            printf("\n");
        }
        printf("\n");
    }
    fprintf(stderr,"Exiting - energy max = 0.0\n");
}
