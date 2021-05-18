#ifndef KEYBOARD_H
#define KEYBOARD_H
#pragma once
#include "GraphCom.h"

class KeyBoardController;

class KeyObject
{
private:
	D2D1_RECT_F			Location;
	WPARAM				Displayable[2];
	KBKColor			Color;
	GraphComs*			GC;
	bool				SecondaryKey;
public:
	void				DrawKeyBox(const float &timestamp);
	bool				CheckChar(WPARAM LetterHit, bool CorrectHit, bool Displayable, bool &VirtualKey);
	void				UpdateLocation(const D2D1_RECT_F	&Location);

	KeyObject();
	KeyObject(const D2D1_RECT_F &Location, WPARAM Displayable[2], GraphComs* GC);
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
	bool				HitTest, VirtualKey;

public:
	void				Resize();
	bool				CheckChar(char LetterHit, char LetterCorrect);
	void				DrawUpdate(const float& timestamp, bool wm_char);
	bool				WM_char(WPARAM LetterHit, WPARAM LetterCorrect);
	bool				WM_keydown(WPARAM LetterHit, WPARAM LetterCorrect);

	KeyBoardController();
	KeyBoardController(GraphComs* GC);
	~KeyBoardController();
};
#endif