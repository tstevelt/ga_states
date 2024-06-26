/*----------------------------------------------------------------------------
	Program : select_fit.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: GA selection function
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"

static	ALLELE	shufflearray[MAXPOP];
static	int		pick = MAXPOP;

static void makeshuffle ()
{
	short	xi;

	ShuffleCount++;

	pick = 0;

	/*--------------------------------
		initialize
	---------------------------------*/
	for ( xi = 0; xi < PopCount; xi++ )
	{
		shufflearray[xi].CapitalIndex = xi;
		shufflearray[xi].SortValue = d_random ();
	}

	qsort ( shufflearray, PopCount, sizeof(ALLELE), (int(*)()) CompareChromoSort );
}

int select_fit ( POPULATION population ) 
{
	int	first, second;

	if ( pick >= PopCount )
		makeshuffle ();

	first  = shufflearray[pick++].CapitalIndex;
	second = shufflearray[pick++].CapitalIndex;

#define FIND_SHORTEST
#ifdef FIND_SHORTEST
	if ( population[first].distance <= population[second].distance )
#else
	if ( population[first].distance > population[second].distance )
#endif
		return ( first );
	else
		return ( second ); 
}
