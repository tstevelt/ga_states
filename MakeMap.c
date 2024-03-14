/*----------------------------------------------------------------------------
	Program : MakeMap.c
	Author  : Tom Stevelt
	Date    : 2018-2024
	Synopsis: Output route for google to draw the map.
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2018-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"ga_states.h"

void MakeMap ()
{
	int		xc;
	double	CenterLat, CenterLong;
	int		ZoomValue;
	double	Percent;

	CenterLat = (MinLat + MaxLat) / 2.0;
	CenterLong = (MinLong + MaxLong) / 2.0;
	switch ( VisitThese )
	{
		case VISIT_ALL:
			ZoomValue = 3;
			break;
		case VISIT_LOWER:
			ZoomValue = 4;
			break;
		case VISIT_EAST:
		case VISIT_WEST:
			ZoomValue = 5;
			break;
	}


	printf ( "<!DOCTYPE html>\n" );
	printf ( "<html>\n" );
	printf ( "<body>\n" );

	printf ( "<div id='googleMap' style='width:100%%;height:600px;'></div>\n" );

	printf ( "<script>\n" );
	printf ( "function myMap() \n" );
	printf ( "{\n" );
		printf ( "var myTrip = [\n" );
		printf ( "{ lat: %.2f, lng: %.2f },\n", 
			CapitalArray[OriginIndex].Latitude,
			CapitalArray[OriginIndex].Longitude );
		for ( xc = 0; xc < AlleleCount; xc++ )
		{
			printf ( "{ lat: %.2f, lng: %.2f },\n", 
				CapitalArray[BestChromosome[xc].CapitalIndex].Latitude,
				CapitalArray[BestChromosome[xc].CapitalIndex].Longitude );
		}
		printf ( "{ lat: %.2f, lng: %.2f }\n", 
			CapitalArray[OriginIndex].Latitude,
			CapitalArray[OriginIndex].Longitude );
		printf ( "];\n" );

		printf ( "var mapProp= \n" );
		printf ( "{\n" );
	  	printf ( "center:new google.maps.LatLng(%.2f,%.2f),\n", CenterLat, CenterLong );
	  	printf ( "zoom:%d,\n", ZoomValue );
		printf ( "};\n" );

		printf ( "var map = new google.maps.Map(document.getElementById('googleMap'),mapProp);\n" );

		printf ( "var flightPath = new google.maps.Polyline(\n" );
		printf ( "{\n" );
	  	printf ( "path:myTrip,\n" );
	  	printf ( "strokeColor:'#0000FF',\n" );
	  	printf ( "strokeOpacity:0.8,\n" );
	  	printf ( "strokeWeight:2\n" );
		printf ( "});\n" );

		printf ( "flightPath.setMap(map);\n" );

		printf ( "var myStartPosition = {lat: %.2f, lng: %.2f};\n",
			CapitalArray[OriginIndex].Latitude,
			CapitalArray[OriginIndex].Longitude );

		printf ( "var marker = new google.maps.Marker({position: myStartPosition});\n" );

		printf ( "marker.setMap(map);\n" );

	Percent = 100.0 * (double) MatchBestCount / (double)(PopCount * Generations);

	printf ( "var infowindow = new google.maps.InfoWindow({ content:'Round trip %.0f miles.<br>Routes evaluated %d.<br>Same answer %d (%.1f%%)' });\n", 
				BestDistance, RouteCalcs, MatchBestCount, Percent );

  	printf ( "infowindow.open(map,marker);\n" );

	printf ( "}\n" );

	printf ( "</script>\n" );

	GetGoogleCfg ();
	printf ( "<script src='https://maps.googleapis.com/maps/api/js?key=%s&callback=myMap'></script>\n", env_GoogleMapKey );

	printf ( "</body>\n" );
	printf ( "</html>\n" );
}
