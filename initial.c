/*----------------------------------------------------------------------------
	Program : initial.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: Initialize GA parameters
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	<time.h>

#include	"ga_states.h"

void initial ()
{
	int		ndx, xp, xi, xo;

	EarlyBreak = 0.05;

	switch ( VisitThese )
	{
		case VISIT_ALL:
			AlleleCount = 49;
			break;
		case VISIT_LOWER:
			AlleleCount = 47;
			break;
		case VISIT_EAST:
			AlleleCount = 0;
			break;
		case VISIT_WEST:
			AlleleCount = 0;
			break;
		default:
			printf ( "Invalid Value %d for VisitThese<br>\n", VisitThese );
			exit ( 1 );
	}

	if ( RunMode == MODE_TERMINAL )
	{
		PopCount = 1000;
		if ( PopCount > MAXPOP )
		{
			printf ( "Exceeds MAXPOP\n" );
			exit ( 1 );
		}
		Generations = 500;
		pCross = 0.995;
		pMutation = 0.05;
	}

	for ( ndx = 0; ndx < 50; ndx++ )
	{
		if ( nsStrcmp ( StartState, CapitalArray[ndx].Abbr ) == 0 )
		{
			CapitalArray[ndx].IsOrigin = 1;
			OriginIndex = ndx;
			break;
		}
	}

	if ( ndx >= 50 )
	{
		printf ( "Unknown origin state, use 2 letter capitalized abbreviation\n" );
		exit ( 1 );
	}

	MinLat  = CapitalArray[OriginIndex].Latitude;
	MaxLat  = CapitalArray[OriginIndex].Latitude;
	MinLong = CapitalArray[OriginIndex].Longitude;
	MaxLong = CapitalArray[OriginIndex].Longitude;

	/*----------------------------------------------------------
		generate an intial random population.
	----------------------------------------------------------*/
	srand ( time ( NULL ) );

	for ( xp = 0; xp < PopCount; xp++ )
	{
		for ( xi = 0, xo = 0; xi < 50; xi++ )
		{
			if ( CapitalArray[xi].IsOrigin )
			{
				continue;
			}

			switch ( VisitThese )
			{
				case VISIT_ALL:
					break;
				case VISIT_LOWER:
					if ( CapitalArray[xi].Type == TYPE_FAR )
					{
						continue;
					}
					break;
				case VISIT_EAST:
					if ( CapitalArray[xi].Type != TYPE_EAST )
					{
						continue;
					}
					if ( xp == 0 )
					{
						AlleleCount++;
					}
					break;
				case VISIT_WEST:
					if ( CapitalArray[xi].Type != TYPE_WEST )
					{
						continue;
					}
					if ( xp == 0 )
					{
						AlleleCount++;
					}
					break;
			}

			OldPopArray[xp].chromosome[xo].CapitalIndex = xi;
			OldPopArray[xp].chromosome[xo].SortValue = d_random ();
			xo++;

			if ( MinLat  > CapitalArray[xi].Latitude )
			{
				MinLat  = CapitalArray[xi].Latitude;
			}
			if ( MaxLat  < CapitalArray[xi].Latitude )
			{
				MaxLat  = CapitalArray[xi].Latitude;
			}
			if ( MinLong > CapitalArray[xi].Longitude )
			{
				MinLong = CapitalArray[xi].Longitude;
			}
			if ( MaxLong < CapitalArray[xi].Longitude )
			{
				MaxLong = CapitalArray[xi].Longitude;
			}
		}
	}

	for ( xp = 0; xp < PopCount; xp++ )
	{
		OldPopArray[xp].distance = obj_func ( OldPopArray[xp].chromosome );
		OldPopArray[xp].parent1 = -1;
		OldPopArray[xp].parent2 = -1;
		OldPopArray[xp].xsite   = -1;
	}

	report ( 0 );

}
