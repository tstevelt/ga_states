/*----------------------------------------------------------------------------
	Program : crossover.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: GA cross over function.
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"

void crossover (  ALLELE parent1[], ALLELE parent2[],
				  ALLELE child1[], ALLELE child2[],
				  int *xsite )
{
	int		cross_site;
	int		xi;

	if ( flip ( pCross ) )
	{
		cross_site = (int) u_random_range ( 0, AlleleCount - 2 );
	}
	else
	{
		cross_site = AlleleCount;
	}

	for ( xi = 0; xi < cross_site; xi++ )
	{
		memcpy ( &child1[xi], &parent1[xi], sizeof(ALLELE) );
		memcpy ( &child2[xi], &parent2[xi], sizeof(ALLELE) );
	}

	for ( ; xi < AlleleCount; xi++ )
	{
		memcpy ( &child1[xi], &parent2[xi], sizeof(ALLELE) );
		memcpy ( &child2[xi], &parent1[xi], sizeof(ALLELE) );
	}

	*xsite = cross_site;
}
