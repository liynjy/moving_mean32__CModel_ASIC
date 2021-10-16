// -------------------------------------------------------
// Author  : Lin Junyang
// Version : 01
// All rights reserved.
// -------------------------------------------------------


#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "mv_mean32.h"

/*
    Testbench Input and expected Output.
*/
#define NT 7542

float di[NT] = {
    #include "mv_mean32_din.txt"
    };
float do_exp[NT] = {
    #include "mv_mean32_dout_exp.txt"
    };

/*
    The is the testbench for C Model of [mv_mean32]
*/
int main()
{
    //printf("Main Debug: %f\n", do_exp[25]);

    // Test Input - ufix9
    uint16_t din[NT], dout[NT];
    for(int i=0; i<NT; i++)
    {
        din[i] = (uint16_t)di[i];
    }
    
    //printf("Main Debug: %d\t", din[13]);
    //printf("Main Debug: %d\n", din[22]);

    mv_mean32(din, dout, NT);

    float tmp;
    for(int i=0; i<NT; i++)
    {
        // Convert expected value to ufix14_En5
        tmp = do_exp[i];
        tmp *= pow(2,5);
        if(dout[i] != (uint16_t)tmp)
        {
            printf("******************************** TEST FAILED ********************************\n");
            printf("Ni=%d, dout=[%d (ufix14_En5)], do_exp=[%d (ufix14_En5)] or [%f (float)]\n", i, dout[i], (uint16_t)tmp, do_exp[i]);
            printf("*****************************************************************************\n\n");
            return 1;

            // if(i==23)
            // {
            //     printf("Main Debug: %f (%d %f)\n", tmp, (uint16_t)tmp, do_exp[i]);
            // }
        }        
    }

    printf("======== TEST PASSED ========\n\n");
    return 0;
}
