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
static	int		pick = MAXPOP + 10;

static void makeshuffle ()
{
	short	xi;

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

static void preselect ()
{
	pick = 0;
	makeshuffle ();
}

int select_fit ( POPULATION population ) 
{
	int	first, second;

	if ( pick + 1 >= PopCount )
		preselect ();

	first  = shufflearray[pick++].CapitalIndex;
	second = shufflearray[pick++].CapitalIndex;

	if ( population[first].distance <= population[second].distance )
		return ( first );
	else
		return ( second ); 
}
