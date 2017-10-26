//////////////////////////////////////////////////////////////////////////////
// * SJTU DSP Tech. Center
// *
// * Description: TMS320C5535 Program Demo for Students Experiment
// *
// * Copyright (C) 2013 SJTU DSP Tech. Center. All Rights Reserved.
// * Copyright (C) Shanghai Jiao Tong University
// *¡¤
// * History:
// * 	Date		Authors			Changes
// *	2013/12		Zhe Sheng		Created.
// *
// *
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "Dsplib.h"

#define NX 8
#define NH 4
#define FNAME "t3"
#define MAXERROR 10  // max absolute value

DATA x[NX] ={
-10408,
2233,
14884,
-12499,
22183,
4461,
-8493,
13286,
};

DATA h[NH] ={
3654,
-4326,
15268,
9519,
};

DATA rtest[NX+NH-1] ={
-1161,
1622,
-3485,
-5342,
11708,
-3931,
5169,
11126,
};

DATA x_np[NX+NH-1] = {
0,
0,
0,
-10408,
2233,
14884,
-12499,
22183,
4461,
-8493,
13286,
};

#define	NR	NX
short eflag=PASS; 	       // error flag (-1: no error; else error)
DATA r[NR];

void StopTest()
{
    //SW_BREAKPOINT;
    return;
}

short test(DATA *r, DATA *rtest, short n, DATA maxerror)
{
short i;
short eflag = PASS;		// error flag or index into r vector where error
DATA elevel = 0;		// error level at failing eflag index location
DATA emax = 0;			// max error level detected across when NOERROR

for (i=0;i<n;i++)
    {
    if ( (elevel = ABSVAL(rtest[i] - r[i])) > maxerror)
       {
       eflag =i;	// if error --> eflag = index and emax= max error
       emax = elevel;	// if no error --> eflag = -1 and emax = max error
       break;
       }
    else
    if (elevel>emax) emax = elevel;
   }
			// Pass to Host: eflag and emax
return(eflag);
}


void main( void )
{
	short i;

    /* Display test ID */
    printf( "\nTesting Convolution of DSPLIB...\n");

	//clear
	for (i = 0; i < NX; i++) r[i] = 0;

	// compute
	(void)convol(x_np, h, r, NR, NH);

	printf( "\nResult vector: ");
	for (i = 0; i < NX; i++) printf("%d ", r[i]) ;
	printf( "\nRight  vector: ");
	for (i = 0; i < NX; i++) printf("%d ", rtest[i]) ;

	// test
	eflag = test(r, rtest, NR, MAXERROR);

	if(eflag != PASS)
		printf( "\nConvolution test error...\n");
	else
		printf( "\nConvolution test passed...\n");

    StopTest();
}
