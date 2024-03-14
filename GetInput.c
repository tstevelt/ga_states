/*----------------------------------------------------------------------------
	Program : GetInput.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: Get parameters from screen
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"

void GetInput ()
{
	int		xa;

	if ( webGetInput () != 0 )
	{
		printf ( "cgiIntergrate: Input error!<br>\n" );
	}

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );

// printf ( "name=value %s = %s<br>\n", webNames[xa] , webValues[xa] );
		
		if ( nsStrcmp ( webNames[xa], "VisitThese" ) == 0 )
		{
			VisitThese = webValues[xa][0];
		}
		else if ( nsStrcmp ( webNames[xa], "StartCity" ) == 0 )
		{
			StartState = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "PopCount" ) == 0 )
		{
			PopCount = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "Generations" ) == 0 )
		{
			Generations = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "ProbCross" ) == 0 )
		{
			pCross = nsAtof ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "ProbMutation" ) == 0 )
		{
			pMutation = nsAtof ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "submitMapRoute" ) == 0 )
		{
		}
		else
		{
			sprintf ( ErrorArray[ErrorCount++].Message, "Unknown name=value %s = %s", webNames[xa] , webValues[xa] );
		}
	}


}
