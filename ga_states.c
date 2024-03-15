/*----------------------------------------------------------------------------
	Program : ga_states.c
	Author  : Tom Stevelt
	Date    : 12/26/2018
	Synopsis: Genetic Algorithm shortest route through all 50 state capitals.
	Return  : 
	See also: http://www.randalolson.com/2016/06/05/computing-optimal-road-trips-on-a-limited-budget/

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		Mar 2024	Added GetGoogleCfg and released on Github

----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#define		MAIN
#include	"ga_states.h"

int main ( int argc, char *argv[] )
{
	int		xg, xp, xc;

	RouteCalcs = 0;

	if ( argc > 1 )
	{
		getargs ( argc, argv );
		RunMode = MODE_TERMINAL;
	}
	else
	{
		printf ( "Content-type: text/html\n\n" );
		GetInput ();
	}

	initgrid ();

	initial ();

	for  ( xg = 1; xg <= Generations; xg++ )
	{
		generation ( xg );

	     for ( xp = 0; xp < PopCount; xp++ )
             memcpy ( &OldPopArray[xp], &NewPopArray[xp], sizeof(INDIVIDUAL) );

		report ( xg );

		// this is too simplistic. (see report)
		//if ( (double) MatchBestCount / (double)(PopCount * Generations) > EarlyBreak )
		//{
		//	break;
		//}
	}

	qsort ( BestChromosome, AlleleCount, sizeof(ALLELE), (int(*)()) CompareChromoSort );

	if ( RunMode == MODE_TERMINAL )
	{
		printf ( "Route calculations %d\n", RouteCalcs );
		printf ( "Shuffle count      %d\n", ShuffleCount );
		printf ( "Minimum Latitude : %7.2f\n", MinLat );
		printf ( "Maximum Latitude : %7.2f\n", MaxLat );
		printf ( "Minimum Longitude: %7.2f\n", MinLong );
		printf ( "Maximum Longitude: %7.2f\n", MaxLong );
		printf ( "Center  Latitude : %7.2f\n", (MinLat + MaxLat) / 2.0 );
		printf ( "Center  Longitude: %7.2f\n", (MinLong + MaxLong) / 2.0 );

		printf ( "%-20.20s %2.2s %7.2f %7.2f\n", 
			CapitalArray[OriginIndex].City,
			CapitalArray[OriginIndex].Abbr,
			CapitalArray[OriginIndex].Latitude,
			CapitalArray[OriginIndex].Longitude );

		for ( xc = 0; xc < AlleleCount; xc++ )
		{
			printf ( "%-20.20s %2.2s %7.2f %7.2f\n", 
				CapitalArray[BestChromosome[xc].CapitalIndex].City,
				CapitalArray[BestChromosome[xc].CapitalIndex].Abbr,
				CapitalArray[BestChromosome[xc].CapitalIndex].Latitude,
				CapitalArray[BestChromosome[xc].CapitalIndex].Longitude );
		}
	}
	else
	{
		MakeMap ();
	}

	return ( 0 );
}
