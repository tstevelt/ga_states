/*----------------------------------------------------------------------------
	Program : sortfuncs.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: Various comparison functions for qsort/bsearch
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"

int CompareChromoIndex ( ALLELE *a, ALLELE *b )
{
	if ( a->CapitalIndex < b->CapitalIndex )
	{
		return ( -1 );
	}	
	return ( 1 );
}

int CompareChromoSort ( ALLELE *a, ALLELE *b )
{
	if ( a->SortValue < b->SortValue )
	{
		return ( -1 );
	}	
	return ( 1 );
}

int CompareIndividual ( INDIVIDUAL *a, INDIVIDUAL *b )
{
	if ( a->distance < b->distance )
	{
		return ( -1 );
	}

	return ( 1 );
}
