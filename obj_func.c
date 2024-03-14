/*----------------------------------------------------------------------------
	Program : obj_func.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: GA scoring function
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"

double obj_func ( ALLELE chromosome[] )
{
	double	rv;
	int		xc;

	rv = 0.0;

	qsort ( chromosome, AlleleCount, sizeof(ALLELE), (int(*)()) CompareChromoSort );

	/*----------------------------------------------------------
		distance from origin to first city
	----------------------------------------------------------*/
	rv = rv + GridArray[OriginIndex][chromosome[0].CapitalIndex].Distance;

	/*----------------------------------------------------------
		distance from city to next city
	----------------------------------------------------------*/
	for ( xc = 0; xc < AlleleCount - 1; xc++ )
	{
		rv = rv + GridArray[chromosome[xc].CapitalIndex][chromosome[xc+1].CapitalIndex].Distance;
	}

	/*----------------------------------------------------------
		distance from last city back to origin
	----------------------------------------------------------*/
	rv = rv + GridArray[OriginIndex][chromosome[AlleleCount - 1].CapitalIndex].Distance;

	qsort ( chromosome, AlleleCount, sizeof(ALLELE), (int(*)()) CompareChromoIndex );

	RouteCalcs++;

	return ( rv );
}
