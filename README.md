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

## How to use fastplot
Get fastplot with:
```git clone https://github.com/miko8278/Fastplot.git ```

First try ```fastplot -h``` to generate following helppage:

```
Hilfeseite fuer fastplot:
Beispiele:
fastplot -d file.csv -p "x=0 y=1 col=r in=0" -p "x=0 y=2 col=b in=1" -o output -ng -t "Bester Titel" -xl "Bestes XLabel" 

Optionen: 

  -h                  Zeige diese Hilfeseite an                                                                            

  -d "Dateiname"      Benutze diese Datei als Quelle fuer Plot                                                             

  -p "Optionen"       Optionen sind:                                                                                       
                      x="spaltennum"                                                                                       
                      y="spaltennum"                                                                                       
                      col="Farbe"                                                                                          
                      (Farben: rot=r, schwarz=b, blau=u, gruen=g, tuerkis=t, orange=o, rosa=f)                             
                      in=1 oder in=0                                                                                       

  -t                  Titel vom Plot                                                                                       

  -ng                 Grid verstecken

  -xl "Xlabel"        X-Label

  -yl "Ylabel"        Y-Label  

```

As a first example try using:
```
fastplot -d file.csv -p "y=1"
```

This should plot a black sine-curve.
Do not forget to use "" around the options after the -p option or it won't parse the plotoptions correctly.

This is a more complicated example:
``` fastplot -d file.csv -p "x=0 y=1 col=r in=0" -p "x=0 y=2 col=b in=1" -o output -ng -t "Bester Titel" -xl "Bestes XLabel"  ```
This creates 2 plots: The first one plots column 1 (y) of the data against column 0 (x) of the data. The color is red and the interpolation is turned on.
The second plot plots column 2 of the data against column 0 of the data. The color is black and interpolation ist turned off.
The data is read from file.csv.
Grid is turned off, the title is "Bester Title" and the xlabel is "Bestes Xlabel".

Please note that Ylabel right now is fundamentally broken in the pbplot libary, even though it is implemented as option.
