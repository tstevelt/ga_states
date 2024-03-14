/*----------------------------------------------------------------------------
	Program : initgrid.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: Set up a 2-dimensional array of distances.
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"


void initgrid ()
{
	int		xa, xb, xc, start, end;
	int		xmileage, xbearing;
	double	TotalMiles;
	int		CountMiles;

	TotalMiles = 0.0;
	CountMiles = 0;

	for ( xa = 0; xa < 50; xa++ )
	{
		for ( xb = 0; xb < 50; xb++ )
		{
			if ( xa == xb )
			{
				GridArray[xa][xb].Distance = 0;
			}
			else
			{
			// int CalcDistance ( double olatitude , double olongitude , double dlatitude , double dlongitude , int *mileage , int *bearing );

				CalcDistance ( CapitalArray[xa].Latitude, CapitalArray[xa].Longitude, 
							   CapitalArray[xb].Latitude, CapitalArray[xb].Longitude, &xmileage, &xbearing );

				GridArray[xa][xb].Distance = xmileage;
				TotalMiles += xmileage;
				CountMiles++;

			}
		}
	}

	
	if ( Debug || GridOnly )
	{
		/*---------------------------------------------------------------------------
			 xx   xx   xx ...
		XX 9999 9999 9999 ...
		XX 9999 9999 9999 ...
		---------------------------------------------------------------------------*/
		for ( xc = 0; xc < 2; xc++ )
		{
			if ( xc == 0 )
			{
				start = 0;
				end = 25;
			}
			else
			{
				start = 25;
				end = 50;
				printf ( "\n" );
			}

			printf ( "   " );
			for ( xa = start; xa < end; xa++ )
			{
				printf ( "   %2.2s", CapitalArray[xa].Abbr );
			}
			printf ( "\n" );

			for ( xb = 0; xb < 50; xb++ )
			{
				printf ( "%2.2s ", CapitalArray[xb].Abbr );
				for ( xa = start; xa < end; xa++ )
				{
					printf ( "%5d", GridArray[xa][xb].Distance );
				}
				printf ( "\n" );
			}
		}

		TotalMiles = TotalMiles / (double)CountMiles;

		printf ( "Average miles between state capitals is %.0f miles.\n", TotalMiles );
	}

	if ( GridOnly )
	{
		exit ( 0 );
	}
}
