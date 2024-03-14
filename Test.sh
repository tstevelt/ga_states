#!/bin/sh
# 	Copyright © 2018-2024 Tom Stevelt
# 	Tom Stevelt <tstevelt@silverhammersoftware.com>
# 	This software is free software; you can redistribute it and/or modify
# 	it under the terms of the MIT license. See LICENSE for details.

#INPUT=input.txt
#echo "VisitThese=E" > $INPUT
#echo "StartCity=IN" >> $INPUT
#echo "PopCount=1000" >> $INPUT
#echo "Generations=250" >> $INPUT
#echo "ProbCross=0.995" >> $INPUT
#echo "ProbMutation=0.2" >> $INPUT

export QUERY_STRING="VisitThese=E&StartCity=IN&PopCount=1000&Generations=250 ProbCross=0.995 ProbMutation=0.2"
gdb /var/www/vhosts/stevelt/html/ga_states.cgi


