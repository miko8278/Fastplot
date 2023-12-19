# Fastplot
Plotting program

Fastplot is a BHT Berlin programming class project.
It utilizes pbPlots https://github.com/InductiveComputerScience/pbPlots as libary
and builds around it to have compact functionality for our everyday use.


## How to build fastplot
First get pbPlots.c, pbPlots.h, supportLib.c and supportLib.h from the link above.
Then first you need to compile those to object files:
```
gcc -c pbPlots.c
gcc -c supportLib.c
```
Finally you can compile and link fastplot in one step:

```gcc fastplot.c pbPlots.o supportLib.o -lm -o fastplot```

This creates a executable called fastplot.

