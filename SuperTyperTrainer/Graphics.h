#ifndef GRAPHICS_H
#define GRAPHICS_H
#pragma once
#include "framework.h"

class BrushColor
{
public:
	ID2D1SolidColorBrush* pB;
	D2D1_COLOR_F				C;

	BrushColor();
	~BrushColor();
	HRESULT CreateBrush(ID2D1HwndRenderTarget* pRenderTarget_);
	void DestroyBrush();
};
struct G_Resources
{
	RECT						rc;
	//Direct 2D Variables
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1GeometrySink* Sink;
	ID2D1StrokeStyle* strokeStyle;
	BrushColor					B_KeyBG_Normal, B_KeyBG_Next, B_KeyBG_Wrong, B_Outline, B_Font, B_Background, B_Scroll_B, B_Scroll_F;
	//DirectWrite Variables
	wstring						Font_Name;
	float						Font_Size, Font_Width, Font_Width_Base;
	IDWriteTextFormat* pITextFormat;
	IDWriteFactory* pIDWriteFactory;
};
class Graphics
{
	bool						UserDefault;
public:
	G_Resources					G_R;
	HWND						hWnd;

	Graphics();
	~Graphics();
	//Functions
	HRESULT CreateG_Resources(HWND& hWnd);
	void DestroyG_Resources();
	template <class T> void OnPaint(T** ppT);
	void Resize();
};
#endif
