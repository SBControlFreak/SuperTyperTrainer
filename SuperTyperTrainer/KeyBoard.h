#ifndef KEYBOARD_H
#define KEYBOARD_H
#pragma once
#include "GraphCom.h"

class KeyBoardController;

class KeyObject
{
private:
	D2D1_RECT_F			Location;
	WCHAR				Meaning[2];
	KBKColor			Color;
	GraphComs*			GC;
public:
	void				DrawKeyBox(const float &timestamp);
	bool				CheckChar(char LetterHit, char LetterCorrect);
	void				UpdateLocation(const D2D1_RECT_F	&Location);

	KeyObject();
	KeyObject(const D2D1_RECT_F &Location, char Meaning[2], GraphComs* GC);
	~KeyObject();

	friend class KeyBoardController;
};
/***********************************KeyBoardController**********************/
class KeyBoardController
{
private:
	vector<KeyObject>	KeyObjects;
	D2D1_RECT_F			Location;
	GraphComs*			GC;
	double				Units, Spacing, WWidth, WHeight;

public:
	void				Resize();
	bool				CheckChar(char LetterHit, char LetterCorrect);
	void				DrawUpdate(const float& timestamp);

	KeyBoardController();
	KeyBoardController(GraphComs* GC);
	~KeyBoardController();
};
#endif