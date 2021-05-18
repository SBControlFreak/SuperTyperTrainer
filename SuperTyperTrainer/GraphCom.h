#ifndef GRAPHCOMS_H
#define GRAPHCOMS_H
#pragma once
#include "Graphics.h"

class GraphComs
{
	D2D1_RECT_F					Location_Text;		//Used as scratch pad
public:
	Graphics					GraphicObject;
	GraphComs();
	~GraphComs();

	HRESULT LoadGraphics(HWND& hWnd_);
	void						Resize();
	float						GetFontSize();
	float						GetFontWidth();

	/**********************Draw Functions used by all other classes needing graphics*******/
	/******************************Draw Functions******************************/
	bool						BeginDraw();
	void						EndDraw();
	void						DrawScrollBar();
	void						DrawKBBackground(const D2D1_RECT_F* Location);
	void						DrawBKey(D2D1_RECT_F& Location, WPARAM letter, bool Displayable, KBKColor Color);
	/******************************Utility Functions******************************/
	void						WinMessageBox(LPCWSTR Title, LPCWSTR Subject, int Type);
};
#endif