/*----------------------------------------------------------
	ga_states.h
	data courtesy of: http://www.xfront.com/us_states/
----------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.


#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<ctype.h>

#include	"shslib.h"
#include	"weblib.h"

#ifndef TYPE
#ifdef MAIN
#define		TYPE	/* */
#else
#define		TYPE	extern
#endif
#endif

TYPE	int		Debug;
TYPE	int		GridOnly;

#define		MODE_TERMINAL	'T'
#define		MODE_CGI		'C'
#ifdef MAIN
int		RunMode = MODE_CGI;
#else
TYPE	int		RunMode;
#endif

#define		VISIT_ALL	'A'
#define		VISIT_LOWER	'L'
#define		VISIT_EAST	'E'
#define		VISIT_WEST	'W'
TYPE	char	VisitThese;

TYPE	char	*StartState;

#define		TYPE_EAST	'E'
#define		TYPE_WEST	'W'
#define		TYPE_FAR	'F'

typedef struct
{
	char	*State;
	char	*Abbr;
	char	*City;
	double	Latitude;
	double	Longitude;
	int		Type;

	int		IsOrigin;

} CAPITAL_RECORD;

#ifdef MAIN
CAPITAL_RECORD		CapitalArray[] = 
{
	{ "Alabama","AL","Montgomery",32.361538,-86.279118, TYPE_EAST },
	{ "Alaska","AK","Juneau",58.301935,-134.419740, TYPE_FAR },
	{ "Arizona","AZ","Phoenix",33.448457,-112.073844, TYPE_WEST },
	{ "Arkansas","AR","Little Rock",34.736009,-92.331122, TYPE_WEST },
	{ "California","CA","Sacramento",38.555605,-121.468926, TYPE_WEST },
	{ "Colorado","CO","Denver",39.7391667,-104.984167, TYPE_WEST },
	{ "Connecticut","CT","Hartford",41.767,-72.677, TYPE_EAST },
	{ "Delaware","DE","Dover",39.161921,-75.526755, TYPE_EAST },
	{ "Florida","FL","Tallahassee",30.4518,-84.27277, TYPE_EAST },
	{ "Georgia","GA","Atlanta",33.76,-84.39, TYPE_EAST },
	{ "Hawaii","HA","Honolulu",21.30895,-157.826182, TYPE_FAR },
	{ "Idaho","ID","Boise",43.613739,-116.237651, TYPE_WEST },
	{ "Illinois","IL","Springfield",39.783250,-89.650373, TYPE_EAST },
	{ "Indiana","IN","Indianapolis",39.790942,-86.147685, TYPE_EAST },
	{ "Iowa","IA","Des Moines",41.590939,-93.620866, TYPE_WEST },
	{ "Kansas","KS","Topeka",39.04,-95.69, TYPE_WEST },
	{ "Kentucky","KY","Frankfort",38.197274,-84.86311, TYPE_EAST },
	{ "Louisiana","LA","Baton Rouge",30.45809,-91.140229, TYPE_EAST },
	{ "Maine","ME","Augusta",44.323535,-69.765261, TYPE_EAST },
	{ "Maryland","MD","Annapolis",38.972945,-76.501157, TYPE_EAST },
//	{ "Massachusetts","MA","Boston",42.2352,-71.0275, TYPE_EAST },
	{ "Massachusetts","MA","Boston",42.3611,-71.0582, TYPE_EAST },
	{ "Michigan","MI","Lansing",42.7335,-84.5467, TYPE_EAST },
	{ "Minnesota","MN","Saint Paul",44.95,-93.094, TYPE_WEST },
	{ "Mississippi","MS","Jackson",32.320,-90.207, TYPE_EAST },
	{ "Missouri","MO","Jefferson City",38.572954,-92.189283, TYPE_WEST },
	{ "Montana","MT","Helana",46.595805,-112.027031, TYPE_WEST },
	{ "Nebraska","NE","Lincoln",40.809868,-96.675345, TYPE_WEST },
	{ "Nevada","NV","Carson City",39.160949,-119.753877, TYPE_WEST },
	{ "New Hampshire","NH","Concord",43.220093,-71.549127, TYPE_EAST },
	{ "New Jersey","NJ","Trenton",40.221741,-74.756138, TYPE_EAST },
	{ "New Mexico","NM","Santa Fe",35.667231,-105.964575, TYPE_WEST },
	{ "New York","NY","Albany",42.659829,-73.781339, TYPE_EAST },
	{ "North Carolina","NC","Raleigh",35.771,-78.638, TYPE_EAST },
//	{ "North Dakota","ND","Bismarck",48.813343,-100.779004, TYPE_WEST },
	{ "North Dakota","ND","Bismarck",46.813343,-100.779004, TYPE_WEST },
	{ "Ohio","OH","Columbus",39.962245,-83.000647, TYPE_EAST },
	{ "Oklahoma","OK","Oklahoma City",35.482309,-97.534994, TYPE_WEST },
	{ "Oregon","OR","Salem",44.931109,-123.029159, TYPE_WEST },
	{ "Pennsylvania","PA","Harrisburg",40.269789,-76.875613, TYPE_EAST },
	{ "Rhode Island","RI","Providence",41.82355,-71.422132, TYPE_EAST },
	{ "South Carolina","SC","Columbia",34.000,-81.035, TYPE_EAST },
	{ "South Dakota","SD","Pierre",44.367966,-100.336378, TYPE_WEST },
	{ "Tennessee","TN","Nashville",36.165,-86.784, TYPE_EAST },
	{ "Texas","TX","Austin",30.266667,-97.75, TYPE_WEST },
	{ "Utah","UT","Salt Lake City",40.7547,-111.892622, TYPE_WEST },
	{ "Vermont","VT","Montpelier",44.26639,-72.57194, TYPE_EAST },
	{ "Virginia","VA","Richmond",37.54,-77.46, TYPE_EAST },
	{ "Washington","WA","Olympia",47.042418,-122.893077, TYPE_WEST },
	{ "West Virginia","WV","Charleston",38.349497,-81.633294, TYPE_EAST },
	{ "Wisconsin","WI","Madison",43.074722,-89.384444, TYPE_EAST },
	{ "Wyoming","WY","Cheyenne",41.145548,-104.802042, TYPE_WEST },
};
int		CapitalCount = sizeof ( CapitalArray ) / sizeof(CAPITAL_RECORD);

#else
TYPE	CAPITAL_RECORD		CapitalArray[];
TYPE	int		CapitalCount;
#endif

TYPE	int		OriginIndex;

typedef struct
{
	int		Distance;
} GRID_RECORD;

TYPE	GRID_RECORD		GridArray[50][50];

TYPE	double	MinLat, MinLong, MaxLat, MaxLong;

/*----------------------------------------------------------
	genetic algoritm structures, defines and variables.
----------------------------------------------------------*/
#define		MAXPOP		10000
#define		MAXALLELE	49

typedef struct
{
	int		CapitalIndex;
	double	SortValue;
} ALLELE;


typedef struct
{
	ALLELE	chromosome[MAXALLELE];
	double	distance;
	short 	parent1;
	short	parent2;
	short	xsite;
	short	counter;
} INDIVIDUAL;

typedef	INDIVIDUAL	POPULATION[MAXPOP];

TYPE	POPULATION	OldPopArray;
TYPE	POPULATION	NewPopArray;
TYPE	int			PopCount;
TYPE	int			AlleleCount;
TYPE	int			Generations;
TYPE	double		pCross;
TYPE	double		pMutation;
TYPE	int			RouteCalcs;
TYPE	ALLELE		BestChromosome[49];
TYPE	double		BestDistance;
TYPE	double		EarlyBreak;
TYPE	int			MatchBestCount;

/*------------------------------
:.,$d
:r ! mkproto -p *.c
------------------------------*/

/* crossover.c */
void crossover ( ALLELE parent1 [], ALLELE parent2 [], ALLELE child1 [], ALLELE child2 [], int *xsite );

/* ga_states.c */
int main ( int argc , char *argv []);

/* generation.c */
void generation ( int Generation );

/* getargs.c */
void getargs ( int argc , char *argv []);

/* GetInput.c */
void GetInput ( void );

/* initgrid.c */
void initgrid ( void );

/* initial.c */
void initial ( void );

/* MakeMap.c */
void MakeMap ( void );

/* obj_func.c */
double obj_func ( ALLELE chromosome []);

/* random.c */
double d_random ( void );
int u_random_range ( int low , int high );
short flip ( double probability );

/* report.c */
void report ( int gen_number );

/* select_fit.c */
int select_fit ( POPULATION population );

/* sortfuncs.c */
int CompareChromoIndex ( ALLELE *a , ALLELE *b );
int CompareChromoSort ( ALLELE *a , ALLELE *b );
int CompareIndividual ( INDIVIDUAL *a , INDIVIDUAL *b );
