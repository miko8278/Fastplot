#include "pbPlots.h"
#include "supportLib.h"
#include "string.h"

// Kommentiert viel
#define PLOTNUM 5


//splittet einen string in substrings mit dem angegebenen delimiter
int split (const char *txt, char delim, char ***tokens);

int readCSV(char *dateiname){

		//Die angegebene CSV auslesen
		FILE* filePointer;
		//Das Auslesen funktioniert Zeile fuer Zeile.
		//Wenn eine Zeile mehr als 10000 Zeichen hat
		// wird das Programm nicht funktionieren
		// Passiert bei einer harten Limitierung von
		// Plots auf 20 aber nicht.
		int bufferLength = 10000;
		char buffer[bufferLength];
		// oeffne die angegebene file im readonly modus
		filePointer = fopen(dateiname, "r");
		//Datei konnte nicht geoeffnet
		if(filePointer == NULL){
			printf("Kann Datei nicht oeffnen. Existiert die Datei?\n");
			return 1; //failed return
		}
		//gebe Datei 1zu1 aus
		//als naechstes muss mit split geparsed werden...
		else{
			for(int i =0; fgets(buffer, bufferLength, filePointer); i++) {
				printf("Zeile No. %d: %s", i,buffer);
			}   
		}

		fclose(filePointer);
		return 0; //return success

}

//argc und argv sind die argumente der Funktion main,
//die sie durch Kommandozeilenparameter erhaelt.
int main(int argc, char* argv[]){

	_Bool success;
	StringReference *errorMessage;



	//Kommandozeilenshit anfang
	//Hier Scope fuer Kommandozeilenvariablen.
	_Bool min_h = false;
	_Bool min_d = false;
	int min_d_spot = 0;
	_Bool min_p = false;
	int min_p_spot = 0;

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



		//-p ist fuer das aktivieren eines bestimmten
		//plottes und dem angeben von optionen:
		//-p "1 x=0 y=1 color=red ls=solid" entspricht
		//Plot 1, x-Werte aus Spalte 0 der csv, y-Werte aus Spalte 1 der csv, rote Farbe, 
		//linear interpoliert mit fester 
		else if(strcmp("-p",argv[i]) == 0){
			min_p = true;
			if(strncmp(argv[i+1],"-",1) != 0){
				min_p_spot = i+1;
				printf("%s \n",argv[min_p_spot]);
				i = i+1;
				continue;
			}
			else{
				printf("Keine/falsche Plotoptionen\n");
				printf("Abbruch\n");
				return 1;
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
	if(min_h){
		printf("Hilfeseite fuer fastplot:\n  Optionen: \n\n");
		printf("  %-20s%-100s \n","-h","Zeige diese Hilfeseite an \n");
		printf("  %-20s%-100s \n","-d Dateiname","Benutze diese Datei als Quelle fuer Plot \n");
		printf("  %-20s%-100s \n","-p \"Optionen\" ","Optionen sind: x=spaltennum y=spaltennum color=farbe ls=linestyle\n");
		

		//Nach der helppage beende das Programm erfolgreich
		return 0;
	}

	//Dateiargument -d
	if(min_d){
		printf("min_d set\n");
		printf("min_d_spot is %d\n",min_d_spot);
		printf("Datei ist an stelle argv[min_d_spot], hier: %s \n",argv[min_d_spot]);

		//failed
		if(readCSV(argv[min_d_spot])){
			return 1;
		}
		//else sucess

	}

	//Plotargument -p
	if(min_p){ 
		printf("min_p set\n");

		char **tokens;
	    int x = 0,y=0;
    	//Der String wird gesplittet in viele Teile, diese werden
    	//durchiteriert.
    	int count = split (argv[min_p_spot], ' ', &tokens);
    	for (int i = 0; i < count; i++){
			if(strncmp(tokens[i],"x=",2) == 0) {
				char **subtokens;
				int cnt;
				cnt = split(tokens[i],'=',&subtokens);
				printf("token1x: %s token2x: %s \n",subtokens[0],subtokens[1]);
				// freeing subtokens 
				for (int i = 0; i < cnt; i++) free (subtokens[i]);
				free (subtokens);
			}
			else if(strncmp(tokens[i],"y=",2) == 0){
				char **subtokens;
				int cnt;
				cnt = split(tokens[i],'=',&subtokens);
				printf("token1y: %s token2y: %s \n",subtokens[0],subtokens[1]);
				// freeing subtokens 
				for (int i = 0; i < cnt; i++) free (subtokens[i]);
				free (subtokens);
			}
			else if(strncmp(tokens[i],"col=",4) == 0){
				char **subtokens;
				int cnt;
				cnt = split(tokens[i],'=',&subtokens);
				printf("token1c: %s token2c: %s \n",subtokens[0],subtokens[1]);
				// freeing subtokens 
				for (int i = 0; i < cnt; i++) free (subtokens[i]);
				free (subtokens);
			}
			else if(strncmp(tokens[i],"ls=",2) == 0){
				char **subtokens;
				int cnt;
				cnt = split(tokens[i],'=',&subtokens);
				printf("token1ls: %s token2ls: %s \n",subtokens[0],subtokens[1]);
				// freeing subtokens 
				for (int i = 0; i < cnt; i++) free (subtokens[i]);
            	free (subtokens);
        	}
    }
    // freeing tokens 
    for (int i = 0; i < count; i++) free (tokens[i]);
    free (tokens);



	}

	//Kommandozeilenshit ENDE



	//HIER geht pbPlots los!
	printf("Okay, ich plotte mal!\n");
	// PLOT POINTS
	//Aktuell maximal 5 punkte... 
	//Anpassen, wenn man csv dateien ausliest.
	double xs [] = {-6, -3, 0, 3, 6};
	double ys [PLOTNUM][5] = {{2, -1, -2, -1, 2},
						{1, -0, -1, -3, 4},
						{3, -1, 0, -2, 3},
						{4, -7, 1, -1, 1},
						{3, -2, 2, -5, 6}};

	//was ist das...?
	StartArenaAllocator();

	//
	// SERIES SETTINGS
	// settings fuer jeweils einen Graphen...
	// kann man mehrere von erstellen
	ScatterPlotSeries *plot[PLOTNUM];
	for(int i = 0; i < PLOTNUM; i++){
		plot[i] = GetDefaultScatterPlotSeriesSettings();

		//xs, ys sind die double arrays mit den Punkten. 5 ist die Laenge aktuell.
		//Wenn man als Laenge bsp 4 eintraegt, dann zeichnet er auch nur 4.
		//Traegt man mehr ein, so sind alle folgenden Punkte 0 und es sieht richtig komisch aus.

		//immer dieselbe X-Achse.
		plot[i]->xs = xs;
		plot[i]->xsLength = 5;
		//immer unterschiedliche Y-Achsen.
		plot[i]->ys = ys[i];
		plot[i]->ysLength = 5;

		plot[i]->linearInterpolation = true;
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
	settings->autoBoundaries = false;
	//Wenn autoBoundaries = false, dann muessen folgende 4 settings auskommentiert werden:
	settings->xMax = 10;
	settings->xMin = -10;
	settings->yMax = 10;
	settings->yMin = -10;

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

	//hier muessen die Plots rein, wenns mehr sind als 1!
	//Jetzt automatisiert mit for schleife
	ScatterPlotSeries *s [PLOTNUM];
	for(int i = 0; i < PLOTNUM; i++){
		s[i] = plot[i];
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
		ByteArray *pngdata = ConvertToPNG(canvasReference->image);
		WriteToFile(pngdata, "example2.png");
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