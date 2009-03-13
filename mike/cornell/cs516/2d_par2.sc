/* Heat diffusion modeler by Jody Shapiro and Mike Perham for CS516 */

#include <split-c/split-c.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include "shapes.h"

#define POS(array,x,y) array[((y)*size) + (x)]
#define GET_SECS() ((tv_e.tv_sec - tv_b.tv_sec) + (((double) tv_e.tv_usec - tv_b.tv_usec)/1000000))

void splitc_main(int argc, char **argv)
{
    double u1[256]::, u2[256]::;
    double elapsed[2]::, ratio;
    double loc_u1[256], loc_u2[256];
    double max;
    double *spread ucurr, *spread unext;
    double *l_uc, *l_un;
    double  dt = 0.001, t, dx, root2;
    int N = 3, x, y, i, hotx, hoty, size = 16;
    int *bitmap;
    struct timeval tv_b, tv_e;
    double mflops, secs;
    int val;

    if (argc != 2)
    {
        printf("usage: %s [barbell | rect | circle]\n", argv[0]);
        exit(-1);
    }

    if (!strcmp(argv[1], "rect")) {
        bitmap = (int *) rect;
        hotx = 6;
        hoty = 6;
    } else if (!strcmp(argv[1], "circle")) {
        bitmap = (int *) circle;
        hotx = hoty = size/2;
    } else {
        bitmap = (int *) barbell;
        hotx =  4;
        hoty = 8;
    }

    dx = 4.0 / size;
    ucurr = u1;
    unext = u2;

    for (y=0;y < size;y++)
        for (x=0;x < size;x++) 
        {
            POS(ucurr,x,y) = 0.0;
            POS(unext,x,y) = 0.0;
        }

    POS(ucurr,hotx,hoty) = 1.0;
      elapsed[MYPROC] = 0.0;

    /* Main temp. calculation loop */
    for (t=0; t<=0.25;t += dt) 
    {
        barrier();
        gettimeofday(&tv_b, NULL);
        POS(ucurr,hotx,hoty) = 1.0;
        for (y=1; y < 15; y++)
            for (x=(MYPROC==0) ? 1 : 2; x < 15; x+=2)
                if (POS(bitmap,x,y))
                    POS(unext,x,y) = POS(ucurr,x,y) +
                    (dt / (6 * dx * dx)) *
                    (4 * (POS(ucurr,x+1,y) + POS(ucurr,x-1,y) +
                          POS(ucurr,x,y+1) + POS(ucurr,x,y-1) -
                          4*POS(ucurr,x,y))
                     +
                     (4 * (POS(ucurr,x+1,y+1) + POS(ucurr,x+1,y-1) +
                           POS(ucurr,x-1,y+1) + POS(ucurr,x-1,y-1) -
                           4*POS(ucurr,x,y))));
                else
                    POS(unext,x,y) = 0.0;

        gettimeofday(&tv_e, NULL);
        elapsed[MYPROC] = elapsed[MYPROC] + GET_SECS();
        barrier();

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

        on_one {
            for(y=0;y < size;y++)
            {
                for(x=0;x < size;x++) 
                {
                    if (bitmap[y*size +x])
                    {
                        if (POS(ucurr,x,y) != 0.0)
                            val = 15 + (int) (log10(POS(ucurr,x,y))/log10(2));
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
    }

    on_one {
        if (elapsed[0] < elapsed[1])
            ratio = (double) elapsed[0] / (double) elapsed[1];
          else
            ratio = (double) elapsed[1] / (double) elapsed[0];
        fprintf(stderr,"Time: %2.5f %2.5f\nLoad ratio between processors: %1.4f\n", elapsed[0], elapsed[1], ratio);
    }

    /* MFLOPS test */

    for (i=0;i<256;i++) {
        loc_u1[i] = u1[i];
        loc_u2[i] = u2[i];
    }
    l_uc = loc_u1;
    l_un = loc_u2;

    for (t=0; t<=0.01;t += dt) 
    {
        barrier();
        gettimeofday(&tv_b, NULL);
        POS(ucurr,hotx,hoty) = 1.0;
        for (y=1; y < 15; y++)
            for (x=0; x < 15; x++)
                if (POS(bitmap,x,y))
                    POS(unext,x,y) = POS(ucurr,x,y) +
                    (dt / (6 * dx * dx)) *
                    (4 * (POS(ucurr,x+1,y) + POS(ucurr,x-1,y) +
                          POS(ucurr,x,y+1) + POS(ucurr,x,y-1) -
                          4*POS(ucurr,x,y))
                     +
        }
        else
        {
            l_uc = loc_u2;
            l_un = loc_u1;
        }
    }
    /* 56 FLOPs * (14 * 14 iterations) divided by 1 million * elapsed time */
    fprintf(stderr, "Proc: %d MFLOPS: %f\n", MYPROC, (10*56*14*14) / (1000000*elapsed[MYPROC]));
    return;
}



