#include "pbPlots.h"
#include "supportLib.h"
#include <string.h>

// Kommentiert viel
#define PLOTNUM 20


//splittet einen string in substrings mit dem angegebenen delimiter
int split (const char *txt, char delim, char ***tokens);


//Liest csv Datei aus.
//returned ein 2 dim double array, nennen wir es array[x][y]
//x ist hierbei die Zeile, y ist die Spalte
//dafuer muss mit malloc dynamisch Speicherplatz reserviert
//werden, wenn wir wissen nicht, wie gross die datei ist *wuerg*
double **readCSV(char *dateiname, int *spalte, int *zeile);



//argc und argv sind die argumente der Funktion main,
//die sie durch Kommandozeilenparameter erhaelt.
int main(int argc, char* argv[]){

	//Idee ist maximal 20 Plots in einem Graphen plotten
	//zu koennen. Man kann unproblematisch mehr machen,
	//aber dann muss man hoehere Werte fuer Speicher, Zeilen etc
	//veranschlagen. Regelt man es dynamisch haste 100 Zeilen *&ptr->xptr **malloc(size_t** yptnr[]->.cs)&*&*&*
	//PLOTNUM = 20!
	int x[PLOTNUM];
	int y[PLOTNUM];
	int col[PLOTNUM];
	int min_p[PLOTNUM];
	int p_cnt = 0;
	int min_p_spot[PLOTNUM];
	char *colors[PLOTNUM];
	char *lines[PLOTNUM];
	//arrays initialisieren
	for(int h = 0; h < PLOTNUM; h++){
		min_p[h] = 0;
		min_p_spot[h] = 0;
		x[h] = 0;
		y[h] = 0;
		colors[h] = NULL;
		lines[h] = NULL;
	}

	_Bool success;
	StringReference *errorMessage;
	double **plotData;
	int spalt = 0;
	int zeil = 0;

	//Kommandozeilenshit anfang
	//Hier Scope fuer Kommandozeilenvariablen.
	_Bool min_h = false; //hilfsseite
	_Bool min_d = false; //dateiname
	_Bool min_ng = false; //no grid on/off
	_Bool min_t = false; // titel
	_Bool min_o = false;
	_Bool min_xl = false;
	_Bool min_yl = false;
	int min_d_spot = 0;
	int min_t_spot = 0;
	int min_o_spot = 0;
	int min_xl_spot = 0;
	int min_yl_spot = 0;

	//Kommandozeilenargumente abchecken
	for (int i = 1; i < argc; i++){
		//"-h" ; Hilfeseite anzeigen
		if(strcmp("-h",argv[i]) == 0){
			min_h = true;
		}


		//-d Dateiname ; Eingabe des Dateinamens
		else if(strcmp("-d",argv[i]) == 0){
			min_d = true;
			//Wir haben den Fall vorliegen, dass
			//eine Datei angegeben wurde.
			if(strncmp(argv[i+1],"-",1) != 0){
				printf("%s \n",argv[i+1]);
				i = i+1;
				min_d_spot = i;
				continue;
			}
			else{
				printf("Keine Datei angeben\n");
				printf("Abbruch\n");
				return 1;
			}

		}

		//-t Titel ; Eingabe des Titelnamens
		else if(strcmp("-t",argv[i]) == 0){
			min_t = true;
			if(strncmp(argv[i+1],"-",1) != 0){
				printf("%s \n",argv[i+1]);
				i = i+1;
				min_t_spot = i;
				continue;
			}
			else{
				printf("Keine gueltiger Titel angeben\n");
				printf("Abbruch\n");
				return 1;
			}

		}

		//-o Titel ; Eingabe der Ausgangsdatei
		else if(strcmp("-o",argv[i]) == 0){
			min_o = true;
			if(strncmp(argv[i+1],"-",1) != 0){
				printf("%s \n",argv[i+1]);
				i = i+1;
				min_o_spot = i;
				continue;
			}
			else{
				printf("Keine gueltige Ausgangsdatei angeben\n");
				printf("Abbruch\n");
				return 1;
			}

		}

		//-xl Xlabel
		else if(strcmp("-xl",argv[i]) == 0){
			min_xl = true;
			if(strncmp(argv[i+1],"-",1) != 0){
				printf("%s \n",argv[i+1]);
				i = i+1;
				min_xl_spot = i;
				continue;
			}
			else{
				printf("Keine gueltiges Xlabel angeben\n");
				printf("Abbruch\n");
				return 1;
			}

		}

		//-yl Ylabel
		else if(strcmp("-yl",argv[i]) == 0){
			min_yl = true;
			if(strncmp(argv[i+1],"-",1) != 0){
				printf("%s \n",argv[i+1]);
				i = i+1;
				min_yl_spot = i;
				continue;
			}
			else{
				printf("Keine gueltiges Ylabel angeben\n");
				printf("Abbruch\n");
				return 1;
			}

		}


		//-g fuer grid on/off
		else if(strcmp("-ng",argv[i]) == 0){
			min_ng = true;
		}

		//-p ist fuer das aktivieren eines bestimmten
		//plottes und dem angeben von optionen:
		//-p "x=0 y=1 color=red ls=solid" entspricht
		//Plot 1, x-Werte aus Spalte 0 der csv, y-Werte aus Spalte 1 der csv, rote Farbe,
		//linear interpoliert mit solidem Strich gezeichnet
		else if(strcmp("-p",argv[i]) == 0){
			//es ist moeglich 20 verschiedene -p optionen anzugeben...
			min_p[p_cnt] = 1;

			if(strncmp(argv[i+1],"-",1) != 0){
				min_p_spot[p_cnt] = i+1;
				printf("%s \n",argv[min_p_spot[p_cnt]]);
				i = i+1;
			}
			else{
				printf("Keine/falsche Plotoptionen\n");
				printf("Abbruch\n");
				return 1;
			}

			if(p_cnt < PLOTNUM){
				p_cnt++;
			}
		}

		//Abbruch, wenn irgendetwas anderes als die oberen
		//Optionen genannt wurden
		else{
			printf("Unbekanntes Argument %s \n", argv[i]);
			printf("Abbruch\n");
			return 1;
		}
	}


	//Hilfsseite -h
	//bitte erweitern mit allen opts
	if(min_h){
		printf("Hilfeseite fuer fastplot:\n  Optionen: \n\n");
		printf("  %-20s%-100s \n","-h","Zeige diese Hilfeseite an \n");
		printf("  %-20s%-100s \n","-d Dateiname","Benutze diese Datei als Quelle fuer Plot \n");
		printf("  %-20s%-100s \n","-p \"Optionen\" ","Optionen sind: x=spaltennum y=spaltennum color=farbe ls=linestyle\n");


		//Nach der helppage beende das Programm erfolgreich
		return 0;
	}

	//-ng no grid
	if(min_ng){
		printf("min_ng set\n");
	}

	//-t Titelname
	if(min_t){
		printf("min_t set Inhalt: %s \n",argv[min_t_spot]);
	}


	//-o Ausgangsdatei z.b graph.png
	if(min_o){
		printf("min_o set Inhalt %s \n",argv[min_o_spot]);
        if (strlen(argv[min_o_spot]) > 100){    //Kontrolle auf Namenslänge
            printf("Dateiname ist zu lang\n");
            printf("Abbruch\n");
        return 1;
				}
	}

	//-xl Xlabel
	if(min_xl){
		printf("min_xl set Inhalt %s \n",argv[min_xl_spot]);
	}

	//-yl Ylabel
	if(min_yl){
		printf("min_yl set Inhalt %s \n",argv[min_yl_spot]);
	}

	//Dateiargument -d
	if(min_d){
		printf("min_d set\n");
		printf("min_d_spot is %d\n",min_d_spot);
		printf("Datei ist an stelle argv[min_d_spot], hier: %s \n",argv[min_d_spot]);

		//ACHTUNG, aktuell keine Fehlerpruefung...
		plotData = readCSV(argv[min_d_spot],&spalt,&zeil);
	}

	//Plotargument -p
	//kann bis zu 20 mal verwendet werden. Fuer jeden Plot eines mit Optionen.
	for(int g = 0; g <= p_cnt; g++){
		if(min_p[g]){
			printf("min_p[%d] set\n",g);

			char **tokens;
			//int x = 0,y=0;
			//Der String wird gesplittet in viele Teile, diese werden
			//durchiteriert.
			int count = split (argv[min_p_spot[g]], ' ', &tokens);
			for (int i = 0; i < count; i++){
				if(strncmp(tokens[i],"x=",2) == 0) {
					char **subtokens;
					char *spntr;
					int cnt;
					cnt = split(tokens[i],'=',&subtokens);
					x[g] = (int) strtod(subtokens[1],&spntr);
					printf("token1x: %s token2x: %d \n",subtokens[0],x[g]);
					// freeing subtokens
					for (int i = 0; i < cnt; i++) free (subtokens[i]);
					free (subtokens);
				}
				else if(strncmp(tokens[i],"y=",2) == 0){
					char **subtokens;
					char *spntr;
					int cnt;
					cnt = split(tokens[i],'=',&subtokens);
					y[g] = (int) strtod(subtokens[1],&spntr);
					printf("token1y: %s token2y: %d \n",subtokens[0],y[g]);
					// freeing subtokens
					for (int i = 0; i < cnt; i++) free (subtokens[i]);
					free (subtokens);
				}
				//nicht fertig
				else if(strncmp(tokens[i],"col=",4) == 0){
					char **subtokens;
					int cnt;
					cnt = split(tokens[i],'=',&subtokens);
					colors[g] = subtokens[1];
					printf("token1c: %s token2c: %s \n",subtokens[0],colors[g]);
					// subtokens nicht free, da wir darauf zugreifen nachher!
					//
					//for (int i = 0; i < cnt; i++) free (subtokens[i]);
					//free (subtokens);
				}
				//nicht fertig
				else if(strncmp(tokens[i],"ls=",3) == 0){
					char **subtokens;
					int cnt;
					cnt = split(tokens[i],'=',&subtokens);
					lines[g] = subtokens[1];
					printf("token1ls: %s token2ls: %s \n",subtokens[0],lines[g]);
					// nicht free, wir brauchen sie nachher!
					//for (int i = 0; i < cnt; i++) free (subtokens[i]);
					//free (subtokens);
				}
		}
		// freeing tokens
		for (int i = 0; i < count; i++) free (tokens[i]);
		free (tokens);

		}
	}
	//Kommandozeilenshit ENDE



	//HIER geht pbPlots los!
	printf("Okay, ich plotte mal!\n");

	// PLOT POINTS alt
	//Alte Test Arrays
	double xs[] = {0,0}; // :D :D
	double ys[] = {0,0};


	printf("Spalten:%d Zeilen:%d\n",spalt,zeil);
	//was ist das...?
	StartArenaAllocator();

	//
	// SERIES SETTINGS
	// settings fuer jeweils einen Graphen...
	// kann man mehrere von erstellen
	ScatterPlotSeries *plot[PLOTNUM];
	ScatterPlotSeries *nullplot;
	double *xsspalte = malloc(sizeof(double)* zeil);
	//double xstest[] = {0,1,2,3,4,5,6,7,8,9};
	//double ystest[] = {0.1,0.2,0.5,1,2,5,10,20,50,70};

	for(int i = 0; i < PLOTNUM; i++){
		plot[i] = GetDefaultScatterPlotSeriesSettings();
		printf("Plot no: %d  xSpalte: %d  ySpalte: %d \n" ,i,x[i],y[i]);
		printf("Plot no %d  Farbe: %s\n",i,colors[i]);
		printf("Plot no %d  linestyle: %s\n",i,lines[i]);
		//Speicherplatz reservieren fuer eine Spalte
		//Werte reinpressen, scheiss auf free, programm laeuft nur kurz
		double *ysspalte = malloc(sizeof(double) * zeil);
		for(int b = 0; b < zeil; b++){
			if(i == 0){
				xsspalte[b] = plotData[b][x[i]];
			}
				ysspalte[b] = plotData[b][y[i]];
		}
		//immer dieselbe X-Achse.
		plot[i]->xs = xsspalte;
		plot[i]->xsLength = zeil;
		//immer unterschiedliche Y-Achsen.
		plot[i]->ys = ysspalte;
		plot[i]->ysLength = zeil;

		plot[i]->linearInterpolation = false;
		//Wenn linearInterpolation = true, dann gelten alle line settings
		//wenn false, dann gelten pointType.
		plot[i]->pointType = L"circles";
		plot[i]->pointTypeLength = wcslen(plot[i]->pointType);
		plot[i]->lineType = L"solid";
		plot[i]->lineTypeLength = wcslen(plot[i]->lineType);
		plot[i]->lineThickness = 2;
		//irgendwas fuer farbvariation... potentiell geht das kaputt...
		plot[i]->color = CreateRGBColor((0.2*i), (0.1*i)+0.5, (0.05*i)+0.2);
	}

	//
	// SCATTERPLOTSETTINGS
	//	settings fuer das Koordinatensystem.
	//	Nur eines.
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();

	//Aufloesung
	settings->width = 800;
	settings->height = 800;

	//Grenzen des Plots
	settings->autoBoundaries = true;
	//Wenn autoBoundaries = false, dann muessen folgende 4 settings auskommentiert werden:
	//pbplot Softwarebug: Wenn die boundaries zu weit ausserhalb von dem sind,
	//was geplottet wird, dann gibts Speicherzugriffsfehler. FUUUUU
	//settings->xMax = 1000;
	//settings->xMin = -10;
	//settings->yMax = 4000;
	//settings->yMin = -10;

	settings->autoPadding = true;
	// Wenn autoPadding = false; dann muessen folgende 2 settings auskommentiert werden:
	//settings->xPadding = 100;
	//settings->yPadding = 100;
	settings->title = L"Titel von dem Ganzen";
	settings->titleLength = wcslen(settings->title);
	settings->xLabel = L"Dies ist ein Xlabel"; // miko8278: Ich hab das Gefuehl, dass es an einer komischen Stelle auftaucht
	settings->xLabelLength = wcslen(settings->xLabel);
	settings->yLabel = L"Dies soll ein Y label sein"; // Funktioniert bei mir nicht
	settings->yLabelLength = wcslen(settings->yLabel);
	settings->showGrid = true;

	//workaround, der legendaere NULLplot
	ScatterPlotSeries *s [PLOTNUM];
	nullplot = GetDefaultScatterPlotSeriesSettings();
	nullplot->xs = xs;
	nullplot->xsLength = 2;
	nullplot->ys = ys;
	nullplot->ysLength = 2;
	nullplot->linearInterpolation = false;

	//hier muessen die Plots rein, wenns mehr sind als 1!
	//Jetzt automatisiert mit for schleife
	for(int i = 0; i < PLOTNUM; i++){
		if(i < p_cnt){
		s[i] = plot[i];
		}
		else{
			s[i] = nullplot;
		}
		//workaround
		//ich weiss nicht warum, aber wenn man nicht alle 20
		//Plots plottet, dann gibts Speicherzugriffsfehler
		//Daher wird hier der 0-Plot geplottet, immer wenns
		//keine Optionen gibt.
	}
	settings->scatterPlotSeries = s;
	//hier anpassen, wie viele plots man hat...
	//PLOTNUM ist immer richtig...
	settings->scatterPlotSeriesLength = PLOTNUM;


	//RGBABitmapImage *blub = CreateImage(1000,1000,GetGray(0.1));
	//Create canvas to draw on
	//ScatterPlotSettings *settings2 = GetDefaultScatterPlotSettings();


	_Bool success2;
	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	//RGBABitmapImageReference *canvasReference2 = CreateRGBABitmapImageReference();
	errorMessage = (StringReference *)malloc(sizeof(StringReference));
	success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);
	//success2 = DrawScatterPlotFromSettings(canvasReference2, settings2, errorMessage);
	//miko8278:DrawText funktioniert bei mir
	//miko8278:DrawTextUpwards ist eine Funktion, die den Text um 90 grad drehend darstellen
	//soll. Funktioniert bei mir nicht
	//DrawText(canvasReference->image,800.0,800.0,L"TEST",4, CreateRGBColor(0,0,0));


	//miko8278: DrawImageonImage verhaelt sich komisch bei mir
	//DrawImageOnImage(canvasReference->image, canvasReference2->image, 0, 0);


	//Wenn zeichnen erfolgreich war, erstelle png.
	if(success){
        const char filetype[5]= ".png";   //Png Endung
        char *stdname = "FastPlotOutput.png";
        char *filename = malloc(sizeof(char)*150); //Speicherreservierung für Dateinamen
        if (min_o) {                //Ein Name ist gewünscht
            filename = argv[min_o_spot];
            strcat(filename, filetype);
        }
        else {                      //Kein Name ist gewünscht
            filename = stdname;
        }
        printf("%s\n", filename);
		ByteArray *pngdata = ConvertToPNG(canvasReference->image);
		WriteToFile(pngdata, filename);
		DeleteImage(canvasReference->image);
	}else{
		fprintf(stderr, "Error: ");
		for(int i = 0; i < errorMessage->stringLength; i++){
			fprintf(stderr, "%c", errorMessage->string[i]);
		}
		fprintf(stderr, "\n");
	}

	FreeAllocations();

	return success ? 0 : 1;
}





//stackoverflowcode zum splitten von strings
//versteh ich 50%
//willkommen in der c hoelle
int split (const char *txt, char delim, char ***tokens)
{
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;
    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}



double **readCSV(char *dateiname, int *spalte, int *zeile){

		//Die angegebene CSV auslesen
		FILE* filePointer;
		//Das Auslesen funktioniert Zeile fuer Zeile.
		//Wenn eine Zeile mehr als 10000 Zeichen hat
		// wird das Programm nicht funktionieren
		// Passiert bei einer harten Limitierung von
		// Plots auf 20 aber nicht.
		int bufferLength = 10000;
		char buffer[bufferLength];
		char *endpntr; // fuer strtod() noetig
		int cnt = 0;
		int i = 0;
		// oeffne die angegebene file im readonly modus
		filePointer = fopen(dateiname, "r");
		//Datei konnte nicht geoeffnet
		if(filePointer == NULL){
			printf("Kann Datei nicht oeffnen. Existiert die Datei?\n");
			//return 1; //failed return
		}
		//zaehle Zeilen und Spalten der Datei
		else{
			for(i = 0; fgets(buffer, bufferLength, filePointer); i++) {
				char **tokenf;
				int newcnt = 0;
				newcnt = split(buffer,';',&tokenf);
				if(cnt < newcnt) cnt = newcnt; // maximale Spaltenzahl
				printf("Zeile No. %d;Elemente: %d : %s ", i,newcnt,buffer);
				for (int j = 0; j < cnt; j++) free (tokenf[j]);
				free (tokenf);
			}
		}
		printf("Final result: Spalten: %d Zeilen: %d \n",cnt, i);
		//Uebergabe der Spalten und Zeilenwerte, Plot braucht es auch.
		*spalte = cnt;
		*zeile = i;
		fclose(filePointer);
		//Jetzt ist bekannt, wie viele Spalten und Zeilen die csv Datei hat.
		//Dynamisch Speicherplatz reservieren fuer ein 2D array.
		// https://www.youtube.com/watch?v=22wkCgsPZSU
		//wenn man den kack verstehen will.
		double **matrix;
		//zeilen
		matrix = malloc(sizeof(double *) * i);
		for(int j = 0;j < i;j++){
			//spalten
			matrix[j] = malloc(sizeof(double) * cnt);
		}

		//Speicherplatz ist reserviert, jetzt die Werte aus der csv
		//in das double[][] reinkriegen...
		//Oeffne ERNEUT die angegebene file im readonly modus
		filePointer = fopen(dateiname, "r");
		if(filePointer == NULL){
			printf("Kann Datei nicht oeffnen beim 2. Versuch.\n");
			//return 1; //failed return
		}
		else{
			for(int m = 0; fgets(buffer, bufferLength, filePointer); m++) {
				char **tokenf;
				int newcnt = 0;
				newcnt = split(buffer,';',&tokenf);
				for(int n = 0; n < newcnt; n++){
					//Wir muessen den string noch in
					//ein double 'casten'.
					//endpntr enthaelt den reststring, der nicht double ist
					//sollte in unserem Falle immer leer sein.
					//Koennte potentiell mal fuer Einheiten verwendet werden.
					matrix[m][n] = strtod(tokenf[n],&endpntr);
					printf("%10lf |",matrix[m][n]);
				}
				printf("\n");
				//printf("Zeile No. %d;Elemente: %d : %s ", m,newcnt,buffer);
				for (int j = 0; j < cnt; j++) free (tokenf[j]);
				free (tokenf);
			}
		}
		fclose(filePointer);

		return matrix; //return success

}
