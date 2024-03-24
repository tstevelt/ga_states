/*----------------------------------------------------------------------------
	Program : report.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: Print report if run from command line
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"

void report ( int gen_number )
{
	int		xp, xc, PrintIt;
	static	int		mindist = 0;
	static	int		maxdist = 0;

	PrintIt = 1;

	for ( xp = 0; xp < PopCount; xp++ )
	{
		// Chromosomes may not match because of mutation changes.
		// if ( mindist > 0 && memcmp ( BestChromosome, OldPopArray[xp].chromosome,  sizeof(BestChromosome) ) == 0 )
		// This is too simplistic to break early on, but interesting statistic nevertheless.
		if ( mindist > 0 && mindist == OldPopArray[xp].distance )
		{
			MatchBestCount++;
		}
		else if ( mindist == 0 || mindist > OldPopArray[xp].distance )
		{
			BestDistance = mindist = OldPopArray[xp].distance;
			memcpy ( BestChromosome, OldPopArray[xp].chromosome, sizeof(BestChromosome) );
			MatchBestCount = 0;

			if ( PrintIt != 2 && RunMode == MODE_TERMINAL )
			{
				if ( PrintIt == 1 )
				{
					printf ( "Generation %d\n", gen_number );
					PrintIt = 0;
				}

				qsort ( OldPopArray[xp].chromosome, AlleleCount, sizeof(ALLELE), (int(*)()) CompareChromoSort );

				printf (  "%4d", xp );

				for ( xc = 0; xc < AlleleCount; xc++ )
				{
					printf ( " %2.2s", CapitalArray[OldPopArray[xp].chromosome[xc].CapitalIndex].Abbr );
				}

				printf (  " %5.0f\n", OldPopArray[xp].distance );
				
				qsort ( OldPopArray[xp].chromosome, AlleleCount, sizeof(ALLELE), (int(*)()) CompareChromoIndex );
			}
		}
		if ( maxdist == 0 || maxdist < OldPopArray[xp].distance )
		{
			maxdist = OldPopArray[xp].distance;
		}
	}

	if ( PrintIt == 2 && RunMode == MODE_TERMINAL )
	{
		printf ( "Generation %4d, %8d\n", gen_number, mindist );
	}
}
