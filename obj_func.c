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

static	ALLELE	obj_chromo[MAXALLELE];

double obj_func ( ALLELE chromosome[] )
{
	double	rv;
	int		xc;
	static	int		ChromoSize = (sizeof(ALLELE)*MAXALLELE);

	rv = 0.0;

	memcpy ( obj_chromo, chromosome, ChromoSize );
	qsort ( obj_chromo, AlleleCount, sizeof(ALLELE), (int(*)()) CompareChromoSort );

	/*----------------------------------------------------------
		distance from origin to first city
	----------------------------------------------------------*/
	rv = rv + GridArray[OriginIndex][obj_chromo[0].CapitalIndex].Distance;

	/*----------------------------------------------------------
		distance from city to next city
	----------------------------------------------------------*/
	for ( xc = 0; xc < AlleleCount - 1; xc++ )
	{
		rv = rv + GridArray[obj_chromo[xc].CapitalIndex][obj_chromo[xc+1].CapitalIndex].Distance;
	}

	/*----------------------------------------------------------
		distance from last city back to origin
	----------------------------------------------------------*/
	rv = rv + GridArray[OriginIndex][obj_chromo[AlleleCount - 1].CapitalIndex].Distance;

	RouteCalcs++;

	return ( rv );
}
