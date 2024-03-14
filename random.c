/*----------------------------------------------------------------------------
	Program : random.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: Random functions
				double d_random ( void );
				int u_random_range ( int low , int high );
				short flip ( double probability );
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"

double d_random ()
{
	long 	xl;
	double	rv;

	xl = rand ();

	rv = (double) xl / (double)RAND_MAX;

	return ( rv );
}

int u_random_range ( int low, int high )
{
	double	xd;
	int		rv;

	if ( low >= high )
		return ( low );

	xd = d_random ();

	rv = xd * ( high - low + 1 ) + low;
	
	if ( rv > high ) 
		rv = high;

	return ( rv );
}

short flip ( double probability )
{
	double	rv;

	if ( probability == 1.0 )
	{
		return ( 1 );
	}
	else
	{
		rv = d_random ();
		if ( rv <= probability )
			return ( 1 );
		else
			return ( 0 );
	}
}
