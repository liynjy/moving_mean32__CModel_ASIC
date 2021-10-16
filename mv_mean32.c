// -------------------------------------------------------
// Author  : Lin Junyang
// Version : 01
// All rights reserved.
// -------------------------------------------------------

/*
   --------------------- C Model ---------------------
   >>> Bit Matched
   >>> Resource Precise
   >>> Cycle Accurate 
   ---------------------------------------------------
   32 Points Moving Average of Input Data Stream
   ---------------------------------------------------
   |   Input:
   |      din     - ufix9              [0,511]
   |   Output:
   |      dout    - ufix14_En5         [0,511.96875]
*/


#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "mv_mean32.h"

// #define PRINT_SE


int mv_mean32(uint16_t* din, uint16_t* dout, int N)
{
   #ifdef PRINT_SE
   printf("\nSTART ---- mv_mean32 ----\n");
   #endif

   // Initialization:
   // Regs
   uint16_t z32reg[32] = {0};
   uint16_t sumreg = 0;   //ufix14
   // Wires
   uint16_t sum;
   
   uint16_t max_in = pow(2,9)-1;
   //printf("maxin:%d",max_in);

   for(int i=0; i<N; i++)
   {
      // Input Range Check
      if(din[i] > max_in)
      {
         printf("*** Invalid Input Data.\n");
         printf("*** Model Quit.\n\n");
      }

      // Sequential Logic (Reg):
      if(i>0) 
      {
         for(int k=31; k>0; k--)
            z32reg[k] = z32reg[k-1];
         z32reg[0] = din[i-1];

         sumreg = sum;
      }

      // Combinational Logic:
      {  
         sum = sumreg + din[i] - z32reg[31];

         if(sum>=pow(2,14))
            sum=pow(2,14)-1;

         dout[i] = sumreg;
      }
   }


   #ifdef PRINT_SE
   printf("END   ---- mv_mean32 ----\n\n");
   #endif

   return 0;
}
