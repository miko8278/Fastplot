#include "pbPlots.h"
#include "supportLib.h"


// Kommentiert viel

RGBABitmapImage *RotateAntiClockwise90DegreesCUSTOM(RGBABitmapImage *image){
  RGBABitmapImage *rotated;
  double x, y;

  rotated = CreateImage(ImageHeight(image), ImageWidth(image), GetBlack());

  for(y = 0.0; y < ImageHeight(image); y = y + 1.0){
    for(x = 0.0; x < ImageWidth(image); x = x + 1.0){
      SetPixel(rotated, y, ImageWidth(image) - 1.0 - x, GetImagePixel(image, x, y));
    }
  }

  return rotated;
}

//argc und argv sind die argumente der Funktion main,
//die sie durch Kommandozeilenparameter erhaelt.
//
int main(){
	_Bool success;
	StringReference *errorMessage;


	// PLOT POINTS
	double xs [] = {-2, -1, 0, 1, 2};
	double ys [] = {2, -1, -2, -1, 2};

	//was ist das...?
	StartArenaAllocator();

	//
	// SERIES SETTINGS
	// settings fuer jeweils einen Graphen...
	// kann man mehrere von erstellen
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
	ScatterPlotSeries *s [] = {series};
	settings->scatterPlotSeries = s;
	settings->scatterPlotSeriesLength = 1;
	//RGBABitmapImage *blub = CreateImage(1000,1000,GetGray(0.1));
	//Create canvas to draw on
	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	errorMessage = (StringReference *)malloc(sizeof(StringReference));
	success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);

	//miko8278:DrawText funktioniert bei mir
	//miko8278:DrawTextUpwards ist eine Funktion, die den Text um 90 grad drehend darstellen
	//soll. Funktioniert bei mir nicht 
	DrawText(canvasReference->image,800.0,800.0,L"TEST",4, CreateRGBColor(0,0,0));
	_Bool success2;

	//miko8278: DrawImageonImage verhaelt sich komisch bei mir
	//DrawImageOnImage(canvasReference->image, blub, 0, 0);

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
