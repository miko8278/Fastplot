#include "pbPlots.h"
#include "supportLib.h"
#include "string.h"

// Kommentiert viel




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

	//Kommandozeilenargumente abchecken
	for (int i = 1; i < argc; i++){
		//Haben wir ein "-h" liegen
		if(strcmp("-h",argv[i]) == 0){
			min_h = true;
		}
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
		else if(strcmp("-p",argv[i]) == 0){
			min_p = true;
		}
		else{ 
			printf("Unbekanntes Argument %s \n", argv[i]);
			printf("Abbruch\n");
			return 1;
		}
	}


	//Hilfsseite
	if(min_h){
		printf("Hilfeseite fuer fastplot:\n  Optionen: \n\n");
		printf("  %-20s%-100s \n","-h","Zeige diese Hilfeseite an \n");
		printf("  %-20s%-100s \n","-d Dateiname","Benutze diese Datei als Quelle fuer Plot \n");
		printf("  %-20s%-100s \n","-p","Zeige diese Hilfeseite an \n");
		



		//Nach der helppage beende das Programm erfolgreich
		return 0;
	}

	//Dateiargument
	if(min_d){
	 printf("min_d set\n");
	 printf("min_d_spot is %d\n",min_d_spot);
	 printf("Datei ist an stelle argv[min_d_spot], hier: %s \n",argv[min_d_spot]);
	}
	if(min_p) printf("min_p set\n");

	//Kommandozeilenshit ENDE



	//HIER geht pbPlots los!
	printf("Okay, ich plotte mal!\n");
	// PLOT POINTS
	double xs [] = {-2, -1, 0, 1, 2};
	double ys [] = {2, -1, -2, -1, 2};
	double ys2 [] = {3, -2, -0, -3, 4};

	//was ist das...?
	StartArenaAllocator();

	//
	// SERIES SETTINGS
	// settings fuer jeweils einen Graphen...
	// kann man mehrere von erstellen
	//PLOT 1
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	//xs, ys sind die double arrays mit den Punkten. 5 ist die Laenge aktuell.
	//Wenn man als Laenge bsp 4 eintraegt, dann zeichnet er auch nur 4.
	//Traegt man mehr ein, so sind alle folgenden Punkte 0 und es sieht richtig komisch aus.
	series->xs = xs;
	series->xsLength = 5;
	series->ys = ys;
	series->ysLength = 5;

	series->linearInterpolation = true;
	//Wenn linearInterpolation = true, dann gelten alle line settings
	//wenn false, dann gelten pointType. 
	series->pointType = L"circles";
	series->pointTypeLength = wcslen(series->pointType);
	series->lineThickness = 2;
	series->lineType = L"solid";
	series->lineTypeLength = wcslen(series->lineType);
	series->lineThickness = 3;
	series->color = CreateRGBColor(0.5, 0.5, 0);


	//PLOT 2
	ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = xs;
	series2->xsLength = 5;
	series2->ys = ys2;
	series2->ysLength = 5;

	series2->linearInterpolation = true;

	series2->pointType = L"circles";
	series2->pointTypeLength = wcslen(series->pointType);
	series2->lineThickness = 2;
	series2->lineType = L"solid";
	series2->lineTypeLength = wcslen(series->lineType);
	series2->lineThickness = 3;
	series2->color = CreateRGBColor(0.1, 0.5, 0.1);



	//
	// SCATTERPLOTSETTINGS
	//	settings fuer das Koordinatensystem.
	//	Nur eines.
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();

	//Aufloesung
	settings->width = 1800;
	settings->height = 1200;

	//Grenzen des Plots
	settings->autoBoundaries = false;
	//Wenn autoBoundaries = false, dann muessen folgende 4 settings auskommentiert werden:
	settings->xMax = 3;
	settings->xMin = -3;
	settings->yMax = 3.5;
	settings->yMin = -5.77;

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

	//hier muessen die Plots rein, wenns mehr sind!
	ScatterPlotSeries *s [] = {series,series2};
	settings->scatterPlotSeries = s;
	//hier anpassen, wie viele plots man hat...
	settings->scatterPlotSeriesLength = 2;
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
