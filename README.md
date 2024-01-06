# Aktuelles
aktuell sollte folgende Eingabe funktionieren.
```
fastplot -d file.csv -p "x=0 y=1 col=red" -p "y=2" -p "y=3"
```
Es koennen maximal files mit 10000 Zeichen Zeilenlaenge gelesen werden.

Die -p "Optionen" macht jeweils einen neuen Plot zum Plotten auf.
Standardmaessig wird die x-Achse aus Spalte 0 gezogen der Datei, die man
mit -d angibt. man kann aber auch x=0 oder jede andere Spalte angeben.
y muss explizit angeben werden, damit er weiss, was er plotten soll.
Alle anderen Optionen stehen noch aus.
```
-p "Optionen" - Optionen für den Plot
	XAchse:		x[] : int;	Enthält die Spalte mit der verwendeten X-Achse 
					(Standartmäßig die nullte Zeile)
	YAchse:		y[] : int;	Enthält die Spalte mit der verwendeten Y-Achse
	Farbe:
	LineStyle:


-t "Titel" - Titel des Ganzen
	min_t : bool;			- True: Es gibt einen Titel
	min_t_spot : int;		- Argument position des Strings
	argv[min_t_spot] : str;   	- Inhalt des Arguments

-ng 	- grid an/aus				
	min_ng: bool; 			- true: es gibt kein grid


-o "Ausgangsname" - Name der Ausgangs png
	min_o: bool;			-es gibt eine gewuenschte bezeichnung
	min_o_spot: int;		-an dieser stelle
	argv[min_o_spot]		-wie sie heisst steht hier

-xl "NAme des Xlabels" - Xlabel
	min_xl: bool
	min_xl_spot
	argv[min_xl_spot]

-yl "Name des Ylabels"
	min_yl: bool
	min_yl_spot
	argv[min_yl_spot]

```
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

