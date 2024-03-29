/*----------------------------------------------------------------------------
	Program : generation.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: GA create the next generation
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.


#include	"ga_states.h" 

#define		LOG_STATS
#undef		LOG_STATS

#ifdef LOG_STATS
static	int		firstpass = 1;
static	char	*fnLog = "/var/local/ga_states.csv";
#endif
static	FILE	*fpLog = (FILE *)0;

void generation ( int Generation )
{
	int		xi, mate1, mate2, xsite;
	ALLELE	SaveMe;
	int		xs, xd;

#ifdef LOG_STATS
	if ( firstpass )
	{
		firstpass = 0;
		if (( fpLog = fopen ( fnLog, "w" )) == (FILE *)0 )
		{
			printf ( "Cannot open %s.<br>\n", fnLog );
			exit ( 0 );
		}

		fprintf ( fpLog, "DataFormat,2\n" );
		fprintf ( fpLog, "Memo1\n" );
		fprintf ( fpLog, "Memo2\n" );
	}

#endif

	for ( xi = 0; xi < PopCount; xi++ )
	{
		OldPopArray[xi].counter = 0;
	}

	for ( xi = 0; xi < PopCount; xi += 2 )
	{
		mate1 = select_fit ( OldPopArray );
		mate2 = select_fit ( OldPopArray );

		OldPopArray[mate1].counter++;
		OldPopArray[mate2].counter++;

		crossover ( OldPopArray[mate1].chromosome, OldPopArray[mate2].chromosome, 
					NewPopArray[xi   ].chromosome, NewPopArray[xi+1 ].chromosome, 
					&xsite );

		if ( flip ( pMutation ) )
		{
			xs = u_random_range ( 0, AlleleCount - 1 );

			do 
			{
				xd = u_random_range ( 0, AlleleCount - 1 );

			} while ( xd == xs );

			memcpy ( &SaveMe, &NewPopArray[xi].chromosome[xs], sizeof(ALLELE) );
			NewPopArray[xi].chromosome[xs].SortValue = NewPopArray[xi].chromosome[xd].SortValue;
			NewPopArray[xi].chromosome[xd].SortValue = SaveMe.SortValue;
		}

		NewPopArray[xi].distance = obj_func ( NewPopArray[xi].chromosome );
		NewPopArray[xi].parent1 = mate1;
		NewPopArray[xi].parent2 = mate2;
		NewPopArray[xi].xsite   = xsite;

		NewPopArray[xi+1].distance = obj_func ( NewPopArray[xi+1].chromosome );
		NewPopArray[xi+1].parent1 = mate2;
		NewPopArray[xi+1].parent2 = mate1;
		NewPopArray[xi+1].xsite   = xsite;
	}

	if ( fpLog != (FILE *)0 )
	{
		qsort ( OldPopArray, PopCount, sizeof(INDIVIDUAL), (int(*)()) CompareIndividual );

		for ( xi = 0; xi < PopCount; xi++ )
		{
			fprintf ( fpLog, "%d,%.0f,%d,%d\n",
				Generation,
				OldPopArray[xi].distance,
				xi + 1,
				OldPopArray[xi].counter );
		}
	}

}
