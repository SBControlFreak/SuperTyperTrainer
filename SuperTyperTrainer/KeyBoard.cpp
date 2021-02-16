#include "KeyBoard.h"
KeyObject::KeyObject()
{
}
KeyObject::KeyObject(const D2D1_RECT_F &Location_, char Meaning_[2], GraphComs* GC_)
	: Location (Location_), GC (GC_)
{
	Meaning[0] = Meaning_[0];
	Meaning[1] = Meaning_[1];

	Color = KBKColor::Normal;
}
KeyObject::~KeyObject()
{
}
void KeyObject::DrawKeyBox(const float& timestamp)
{
	/*
	Function: Draws Key. Uses timestamp to access how long to keep color
	*/
	//const WCHAR letterTest = 'K';
	GC->DrawBKey(Location, &Meaning[0]);
}
void KeyObject::UpdateLocation(const D2D1_RECT_F& Location_)
{
	Location = Location_;
}
/***********************************KeyBoardController**********************/
KeyBoardController::KeyBoardController()
{
}
KeyBoardController::KeyBoardController(GraphComs* GC_)
	: GC(GC_)
{
	/*
	Function: Setup and prepare keyboard for display.

	1. Determine left, right, top, and bottom coordinates of the window for sizing and position of the keyboard.
	2. Update position of keyboard
	3. Create, load, and position KeyObjects of the keyboard. 
	*/

	float			WWidth, WHeight, KeyHeight, KeyWidth;
	char			MeaningTemp[2];
	D2D1_RECT_F		LocationTemp;

	//1. Determine left, right, top, and bottom coordinates of the window for sizing and position of the keyboard.
	WWidth = GC_->GraphicObject.G_R.rc.right - GC_->GraphicObject.G_R.rc.left;
	WHeight = GC_->GraphicObject.G_R.rc.bottom - GC_->GraphicObject.G_R.rc.top;

	//2. Update position of keyboard
	Location.left = GC_->GraphicObject.G_R.rc.left + WWidth / 2.0f;
	Location.right = GC_->GraphicObject.G_R.rc.right - WWidth / 2.0f;

	Location.top = GC_->GraphicObject.G_R.rc.bottom + WHeight / 3.0f + 25.0f;
	Location.bottom = GC_->GraphicObject.G_R.rc.bottom + 25.0f;

	KeyHeight = (Location.bottom - Location.top - Spacing * 7.0f) / 6.0f;
	KeyWidth = (Location.right - Location.left - Spacing * 16.0f) / 14.5f;

	//3. Create, load, and position KeyObjects of the keyboard.
	//Escape Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F1 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F2 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F3 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F4 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F5 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F6 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F7 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F8 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F9 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F10 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F11 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F12 Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Eject Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Tilde Key
	MeaningTemp[0] = '`';
	MeaningTemp[1] = '~';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//1 Key
	MeaningTemp[0] = '1';
	MeaningTemp[1] = '!';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//2 Key
	MeaningTemp[0] = '2';
	MeaningTemp[1] = '@';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//3 Key
	MeaningTemp[0] = '3';
	MeaningTemp[1] = '#';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//4 Key
	MeaningTemp[0] = '4';
	MeaningTemp[1] = '$';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//5 Key
	MeaningTemp[0] = '5';
	MeaningTemp[1] = '%';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//6 Key
	MeaningTemp[0] = '6';
	MeaningTemp[1] = '^';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//7 Key
	MeaningTemp[0] = '7';
	MeaningTemp[1] = '&';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//8 Key
	MeaningTemp[0] = '8';
	MeaningTemp[1] = '*';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//9 Key
	MeaningTemp[0] = '9';
	MeaningTemp[1] = '(';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//0 Key
	MeaningTemp[0] = '0';
	MeaningTemp[1] = ')';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//- Key
	MeaningTemp[0] = '-';
	MeaningTemp[1] = '_';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//= Key
	MeaningTemp[0] = '=';
	MeaningTemp[1] = '+';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Delete Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Tab Key
	MeaningTemp[0] = 'Z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Q Key
	MeaningTemp[0] = 'q';
	MeaningTemp[1] = 'Q';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//W Key
	MeaningTemp[0] = 'w';
	MeaningTemp[1] = 'W';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//E Key
	MeaningTemp[0] = 'e';
	MeaningTemp[1] = 'E';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//R Key
	MeaningTemp[0] = 'r';
	MeaningTemp[1] = 'R';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//T Key
	MeaningTemp[0] = 't';
	MeaningTemp[1] = 'T';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Y Key
	MeaningTemp[0] = 'y';
	MeaningTemp[1] = 'Y';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//U Key
	MeaningTemp[0] = 'u';
	MeaningTemp[1] = 'U';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//I Key
	MeaningTemp[0] = 'i';
	MeaningTemp[1] = 'I';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//O Key
	MeaningTemp[0] = 'o';
	MeaningTemp[1] = 'O';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//P Key
	MeaningTemp[0] = 'p';
	MeaningTemp[1] = 'P';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//[ Key
	MeaningTemp[0] = '[';
	MeaningTemp[1] = '{';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//] Key
	MeaningTemp[0] = ']';
	MeaningTemp[1] = '}';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//\ Key
	MeaningTemp[0] = '\\';
	MeaningTemp[1] = '|';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Caps Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//A Key
	MeaningTemp[0] = 'a';
	MeaningTemp[1] = 'A';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//S Key
	MeaningTemp[0] = 'a';
	MeaningTemp[1] = 'S';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//D Key
	MeaningTemp[0] = 'd';
	MeaningTemp[1] = 'D';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//F Key
	MeaningTemp[0] = 'f';
	MeaningTemp[1] = 'F';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//G Key
	MeaningTemp[0] = 'g';
	MeaningTemp[1] = 'G';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//H Key
	MeaningTemp[0] = 'h';
	MeaningTemp[1] = 'H';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//J Key
	MeaningTemp[0] = 'j';
	MeaningTemp[1] = 'J';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//K Key
	MeaningTemp[0] = 'k';
	MeaningTemp[1] = 'K';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//L Key
	MeaningTemp[0] = 'l';
	MeaningTemp[1] = 'L';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//; Key
	MeaningTemp[0] = ';';
	MeaningTemp[1] = ':';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//' Key
	MeaningTemp[0] = '\'';
	MeaningTemp[1] = '"';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Return Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//LShift Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Z Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = 'Z';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//X Key
	MeaningTemp[0] = 'x';
	MeaningTemp[1] = 'X';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//C Key
	MeaningTemp[0] = 'c';
	MeaningTemp[1] = 'C';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//V Key
	MeaningTemp[0] = 'v';
	MeaningTemp[1] = 'V';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//B Key
	MeaningTemp[0] = 'b';
	MeaningTemp[1] = 'B';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//N Key
	MeaningTemp[0] = 'n';
	MeaningTemp[1] = 'N';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//M Key
	MeaningTemp[0] = 'm';
	MeaningTemp[1] = 'M';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//, Key
	MeaningTemp[0] = ',';
	MeaningTemp[1] = '<';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//. Key
	MeaningTemp[0] = '.';
	MeaningTemp[1] = '>';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	/// Key
	MeaningTemp[0] = '/';
	MeaningTemp[1] = '?';
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//RShift Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Function Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//CTRL Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//LOption Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//LCommand Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//Space bar Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//RCommand Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//ROption Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//LArrow Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//UArrow Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//DArrow Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));

	//RArrow Key
	MeaningTemp[0] = 'z';
	MeaningTemp[1] = NULL;
	KeyObjects.push_back(KeyObject(Location, MeaningTemp, GC));
}
KeyBoardController::~KeyBoardController()
{
}
void KeyBoardController::Resize()
{
	/*
	Function: Reorientate  keyboard for display.

	1. Determine left, right, top, and bottom coordinates of the window for sizing and position of the keyboard.
	2. Update position of keyboard
	3. Position KeyObjects of the keyboard.

	Apple Magic Keyboard:	11" x 4-1/2"
	Spacing:				1/8"
	Small key:				5/8" x 5/8"
	Command Key:			13/16" x 5/8"
	Tab Key:				8/8" x 5/8"
	Caps Key:				1-3/16" x 5/8"
	Shift Key:				1-9/16" x 5/8"
	Space Bar Key:			3-9/16" x 5/8"

	Smallest unit size:		1/16"

	In units
	Keyboard:				176 x 72
	Spacing:				2
	Small key:				10 x 10
	Command Key:			13 x 10
	Tab Key:				16 x 10
	Caps Key:				19 x 10
	Shift Key:				25 x 10
	Space Bar Key:			57 x 10
	*/

	float UnitsTempLR, UnitsTempUD;
	char			MeaningTemp[2];
	D2D1_RECT_F		LocationTemp;
	//1. Determine left, right, top, and bottom coordinates of the window for sizing and position of the keyboard.
	WWidth = GC->GraphicObject.G_R.rc.right - GC->GraphicObject.G_R.rc.left;
	WHeight = GC->GraphicObject.G_R.rc.bottom - GC->GraphicObject.G_R.rc.top;

	//2. Update position of keyboard
	Location.left = GC->GraphicObject.G_R.rc.left + (WWidth) / 4.0f;
	Location.right = GC->GraphicObject.G_R.rc.right - (WWidth) / 4.0f;

	Location.top = GC->GraphicObject.G_R.rc.bottom - WHeight / 3.0f - 25.0f;
	Location.bottom = GC->GraphicObject.G_R.rc.bottom - 25.0f;

	//Select the small unit and use for dimension
	UnitsTempLR = (Location.right - Location.left) / 176.0f;
	UnitsTempUD = (Location.bottom - Location.top) / 72.0f;

	if (UnitsTempLR < UnitsTempUD)
	{
		Units = UnitsTempLR;
		//Reposition left and right of Keyboard based on units
		Location.left = WWidth / 2.0f - ((176.0f / 2.0f) * Units);
		Location.right = WWidth / 2.0f + ((176.0f / 2.0f) * Units);
	}
	else
	{
		Units = UnitsTempUD;
		//Reposition Keyboard based on units
		Location.left = WWidth / 2.0f - ((176.0f / 2.0f) * Units);
		Location.right = WWidth / 2.0f + ((176.0f / 2.0f) * Units);
		Location.top = (GC->GraphicObject.G_R.rc.bottom - WHeight / 3.0f) - 25.0f;
		Location.bottom = Location.top + 74.0 * Units;
	}

	Spacing = Units * 2;

	//3. Position KeyObjects of the keyboard.
	//Escape Key
	LocationTemp.left = Location.left + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 16.0;
	LocationTemp.top = Location.top + Spacing;
	LocationTemp.bottom = LocationTemp.top + Units * 10.0;
	KeyObjects[0].UpdateLocation(LocationTemp);

	//F1 through escape Keys
	for (int i = 0; i < 13; i++)
	{
		LocationTemp.left = KeyObjects[i].Location.right + Spacing;
		LocationTemp.right = LocationTemp.left + Units * 10.0;
		KeyObjects[i + 1].UpdateLocation(LocationTemp);
	}

	//~ Key
	LocationTemp.left = Location.left + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 10.0;
	LocationTemp.top = KeyObjects[0].Location.bottom + Spacing;
	LocationTemp.bottom = LocationTemp.top + Units * 10.0;
	KeyObjects[14].UpdateLocation(LocationTemp);

	//1 through = Keys
	for (int i = 0; i < 12; i++)
	{
		LocationTemp.left = KeyObjects[i + 14].Location.right + Spacing;
		LocationTemp.right = LocationTemp.left + Units * 10.0;
		KeyObjects[i + 14 + 1].UpdateLocation(LocationTemp);
	}

	//Delete Key
	LocationTemp.left = KeyObjects[26].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 16.0;
	KeyObjects[27].UpdateLocation(LocationTemp);

	//Tab Key
	LocationTemp.left = Location.left + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 16.0;
	LocationTemp.top = KeyObjects[27].Location.bottom + Spacing;
	LocationTemp.bottom = LocationTemp.top + Units * 10.0;
	KeyObjects[28].UpdateLocation(LocationTemp);

	//Q through \ Keys
	for (int i = 0; i < 13; i++)
	{
		LocationTemp.left = KeyObjects[i + 28].Location.right + Spacing;
		LocationTemp.right = LocationTemp.left + Units * 10.0;
		KeyObjects[i + 28 + 1].UpdateLocation(LocationTemp);
	}

	//Caps Key
	LocationTemp.left = Location.left + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 19.0;
	LocationTemp.top = KeyObjects[41].Location.bottom + Spacing;
	LocationTemp.bottom = LocationTemp.top + Units * 10.0;
	KeyObjects[42].UpdateLocation(LocationTemp);

	//A through ' Keys
	for (int i = 0; i < 11; i++)
	{
		LocationTemp.left = KeyObjects[i + 42].Location.right + Spacing;
		LocationTemp.right = LocationTemp.left + Units * 10.0;
		KeyObjects[i + 42 + 1].UpdateLocation(LocationTemp);
	}

	//Return Key
	LocationTemp.left = KeyObjects[53].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 19.0;
	KeyObjects[54].UpdateLocation(LocationTemp);

	//LShift Key
	LocationTemp.left = Location.left + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 25.0;
	LocationTemp.top = KeyObjects[54].Location.bottom + Spacing;
	LocationTemp.bottom = LocationTemp.top + Units * 10.0;
	KeyObjects[55].UpdateLocation(LocationTemp);

	//Z through ? Keys
	for (int i = 0; i < 10; i++)
	{
		LocationTemp.left = KeyObjects[i + 55].Location.right + Spacing;
		LocationTemp.right = LocationTemp.left + Units * 10.0;
		KeyObjects[i + 55 + 1].UpdateLocation(LocationTemp);
	}

	//RShift Key
	LocationTemp.left = KeyObjects[65].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 25.0;
	KeyObjects[66].UpdateLocation(LocationTemp);

	//Function through LOption Keys
	LocationTemp.left = Location.left + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 10.0;
	LocationTemp.top = KeyObjects[66].Location.bottom + Spacing;
	LocationTemp.bottom = LocationTemp.top + Units * 10.0;
	KeyObjects[67].UpdateLocation(LocationTemp);

	for (int i = 0; i < 2; i++)
	{
		LocationTemp.left = KeyObjects[i + 67].Location.right + Spacing;
		LocationTemp.right = LocationTemp.left + Units * 10.0;
		KeyObjects[i + 67 + 1].UpdateLocation(LocationTemp);
	}

	//LCommand Key
	LocationTemp.left = LocationTemp.left = KeyObjects[69].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 13.0;
	KeyObjects[70].UpdateLocation(LocationTemp);

	//Space Bar Key
	LocationTemp.left = LocationTemp.left = KeyObjects[70].Location.right + Spacing;
	LocationTemp.right = KeyObjects[71 - 9].Location.right;	//Used -9 because precision of double was a little off reaching the M key
	KeyObjects[71].UpdateLocation(LocationTemp);

	//RCommand Key
	LocationTemp.left = LocationTemp.left = KeyObjects[71].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 13.0;
	KeyObjects[72].UpdateLocation(LocationTemp);

	//ROption Key
	LocationTemp.left = LocationTemp.left = KeyObjects[72].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 10.0;
	KeyObjects[73].UpdateLocation(LocationTemp);

	//LArrow Key
	LocationTemp.left = LocationTemp.left = KeyObjects[73].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 10.0;
	KeyObjects[74].UpdateLocation(LocationTemp);

	//UArrow Key
	LocationTemp.left = LocationTemp.left = KeyObjects[74].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 10.0;
	LocationTemp.bottom = KeyObjects[74].Location.bottom - Units * 5.0;
	KeyObjects[75].UpdateLocation(LocationTemp);

	//DArrow Key
	LocationTemp.top = KeyObjects[74].Location.bottom - Units *5.0;
	LocationTemp.bottom = KeyObjects[74].Location.bottom;
	KeyObjects[76].UpdateLocation(LocationTemp);

	//RArrow Key
	LocationTemp.left = LocationTemp.left = KeyObjects[76].Location.right + Spacing;
	LocationTemp.right = LocationTemp.left + Units * 10.0;
	LocationTemp.top = KeyObjects[74].Location.top;
	LocationTemp.bottom = KeyObjects[74].Location.bottom;
	KeyObjects[77].UpdateLocation(LocationTemp);
}
void KeyBoardController::DrawUpdate(const float& timestamp)
{
	GC->DrawKBBackground(&Location);

	for (size_t i = 0; i < KeyObjects.size(); i++)
	{
		KeyObjects[i].DrawKeyBox(timestamp);
	}
}