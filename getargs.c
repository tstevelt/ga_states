/*----------------------------------------------------------------------------
	Program : getargs.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: Get command line args if run from command line instead of web
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.


#include	"ga_states.h"


static void MyUsage ()
{
	printf ( "USAGE: ga_states Origin [-d]\n" );
	printf ( "USAGE: ga_states Origin -grid\n" );
	exit ( 1 );
}

void getargs ( int argc, char *argv[] )
{
	int		ndx;

	if ( argc < 2 )
	{
		MyUsage ();
	}

	VisitThese = VISIT_ALL;
	PopCount = 1000;
	Generations = 500;
	pCross = 0.995;
	pMutation = 0.05;

	StartState = argv[1];

	Debug = 0;
	GridOnly = 0;
	for ( ndx = 2; ndx < argc; ndx++ )
	{
		if ( nsStrcmp ( argv[ndx], "-d" ) == 0 )
		{
			Debug = 1;
		}
		else if ( nsStrcmp ( argv[ndx], "-grid" ) == 0 )
		{
			GridOnly = 1;
		}
		else
		{
			MyUsage ();
		}
	}
}
