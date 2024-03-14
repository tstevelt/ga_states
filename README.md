
## Find the shortest route

Use a Genetic Algorithm (GA) to find the shortest route between the state capitals. An exhaustive search would require 6.08e62 route calculations. This is based on a given starting point, where the other 49 capitals can be arranged in any order. GA may require around a million route evaluations (population count times number of generations). 

The program can be run from the command line or from a web page.

When run from the command line, all that is needed is an origin state. GA parameters are set to some reasonable defaults.
```
USAGE: ga_states.cgi Origin [-d]
USAGE: ga_states.cgi Origin -grid
```

When run from a web page, the following inputs are recommended.

Prompt | Description
-------|----------------------------------------------------------------------
Cities to visit | All, Lower 48, East or West
Starting City | Two letter state code
Population count | Number of routes in the population
Number of generations | Maximum number of generations
Probabilty of cross over | Probability that selected parents will combine DNA.
Probabilty of mutation | Probablity of mutation

Live web demo at <https://www.silverhammersoftware.com/?MenuIndex=3>

Source code at <https://github.com/tstevelt/ga_states>



