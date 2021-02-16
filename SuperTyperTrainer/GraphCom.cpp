#include "GraphCom.h"
GraphComs::GraphComs()
{
}
GraphComs::~GraphComs()
{
	GraphicObject.DestroyG_Resources();
}
HRESULT GraphComs::LoadGraphics(HWND& hWnd_)
{
	/*
	Function: Calls the graphic resources create function to generate all basic drawing components
	*/
	return GraphicObject.CreateG_Resources(hWnd_);
}
void GraphComs::Resize()
{
	//Resizing is required to recalculate the logical coordinates for proper drawing
	if (GraphicObject.G_R.pRenderTarget != NULL)
	{
		GetClientRect(GraphicObject.hWnd, &GraphicObject.G_R.rc);

		D2D1_SIZE_U size = D2D1::SizeU(GraphicObject.G_R.rc.right, GraphicObject.G_R.rc.bottom);

		GraphicObject.G_R.pRenderTarget->Resize(size);
		InvalidateRect(GraphicObject.hWnd, NULL, FALSE);
	}
	return;
}
float GraphComs::GetFontSize()
{
	return GraphicObject.G_R.Font_Size;
}
float GraphComs::GetFontWidth()
{
	return GraphicObject.G_R.Font_Width;
}
/**********************Draw Functions used by all other classes needing graphics*******/
/**********Draw Functions**********/
bool GraphComs::BeginDraw()
{
	GetClientRect(GraphicObject.hWnd, &GraphicObject.G_R.rc);
	if (GraphicObject.G_R.pRenderTarget != nullptr)
	{
		GraphicObject.G_R.pRenderTarget->BeginDraw();
		// Start with white background
		GraphicObject.G_R.pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		return true;
	}
	else
	{
		return false;
	}
}
void GraphComs::EndDraw()
{
	HRESULT hr = GraphicObject.G_R.pRenderTarget->EndDraw();
	if (hr != 0x88990012)
	{
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			//DiscardGraphicsResources(hWnd);
			//MessageBox(hWnd, L"Failed to Draw", L"Pages: Graphics Error", MB_OK);

			//TODO: Fix Connector Arrow issue
			//0x88990012 -> D2DERR_WRONG_FACTORY
			//Objects used together were not all created from the same factory instance.
		}
	}
}
void GraphComs::DrawScrollBar()
{
	////Draw scroll bar background
	//GraphicObject.G_R.pRenderTarget->DrawRectangle(SBVars_.Location, GraphicObject.G_R.B_Scroll_B.pB, 1.0f);
	//GraphicObject.G_R.pRenderTarget->FillRectangle(SBVars_.Location, GraphicObject.G_R.B_Scroll_B.pB);

	////Draw Arrow1 head
	//GraphicObject.G_R.pRenderTarget->DrawRectangle(SBVars_.Location_ArrowBox1, GraphicObject.G_R.B_Scroll_F.pB, 1.0f);

	//GraphicObject.G_R.pRenderTarget->DrawGeometry(SBVars_.Arrow1.pGeo_Arrow, GraphicObject.G_R.B_Scroll_F.pB, 1.0f);
	//GraphicObject.G_R.pRenderTarget->FillGeometry(SBVars_.Arrow1.pGeo_Arrow, GraphicObject.G_R.B_Scroll_F.pB);

	////Draw Arrow2 head
	//GraphicObject.G_R.pRenderTarget->DrawRectangle(SBVars_.Location_ArrowBox2, GraphicObject.G_R.B_Scroll_F.pB, 1.0f);

	//GraphicObject.G_R.pRenderTarget->DrawGeometry(SBVars_.Arrow2.pGeo_Arrow, GraphicObject.G_R.B_Scroll_F.pB, 1.0f);		//Draw Arrow2 Head
	//GraphicObject.G_R.pRenderTarget->FillGeometry(SBVars_.Arrow2.pGeo_Arrow, GraphicObject.G_R.B_Scroll_F.pB);				//Fill Arrow2 Head

	//if (SBVars_.BarRatioLeft_Top != 1.0 || SBVars_.BarRatioRight_Bottom != 1.0)
	//{
	//	//Draw Bar
	//	GraphicObject.G_R.pRenderTarget->DrawRectangle(SBVars_.Location_Bar, GraphicObject.G_R.B_Scroll_F.pB, 1.0f);
	//	GraphicObject.G_R.pRenderTarget->FillRectangle(SBVars_.Location_Bar, GraphicObject.G_R.B_Scroll_F.pB);
	//}
}
void GraphComs::DrawKBBackground(const D2D1_RECT_F* Location)
{
	//Draw Keyboard background
	GraphicObject.G_R.pRenderTarget->FillRectangle(Location, GraphicObject.G_R.B_KeyBoardFrame.pB);
}
void GraphComs::DrawBKey(D2D1_RECT_F& Location, const WCHAR *letter)
{
	/*
	Function: Draws basic key of the keyboard (letter keys). 
	*/

	//Draw Box
	GraphicObject.G_R.pRenderTarget->FillRectangle(Location, GraphicObject.G_R.B_KeyBG_Normal.pB);
	GraphicObject.G_R.pRenderTarget->DrawRectangle(Location, GraphicObject.G_R.B_Outline.pB, 1.0f);

	//Prepare text
	GraphicObject.G_R.pITextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	GraphicObject.G_R.pITextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	//Draw Text
	GraphicObject.G_R.pRenderTarget->DrawText(letter, 1, GraphicObject.G_R.pITextFormat, Location, GraphicObject.G_R.B_Font.pB);
}
/**********Utility Functions**********/
void GraphComs::WinMessageBox(LPCWSTR Title, LPCWSTR Subject, int Type)
{
	/*
	Function: Allows calling function to display messages to the user.
	*/
	MessageBox(GraphicObject.hWnd, Subject, Title, Type);
}