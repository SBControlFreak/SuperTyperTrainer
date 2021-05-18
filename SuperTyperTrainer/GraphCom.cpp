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
	return GraphicObject.G_R.Font_SizeR;
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
void GraphComs::DrawBKey(D2D1_RECT_F& Location, WPARAM letter, bool Displayable, KBKColor Color)
{
	/*
	Function: Draws basic key of the keyboard (letter keys). 
	*/

	wstring temp;

	temp.push_back(letter);

	//Draw Box
	switch (Color)
	{
	case Normal:
		GraphicObject.G_R.pRenderTarget->FillRectangle(Location, GraphicObject.G_R.B_KeyBG_Normal.pB);
		break;
	case Right:
		GraphicObject.G_R.pRenderTarget->FillRectangle(Location, GraphicObject.G_R.B_KeyBG_Right.pB);
		break;
	case Wrong:
		GraphicObject.G_R.pRenderTarget->FillRectangle(Location, GraphicObject.G_R.B_KeyBG_Wrong.pB);
		break;
	case Next:
		GraphicObject.G_R.pRenderTarget->FillRectangle(Location, GraphicObject.G_R.B_KeyBG_Next.pB);
		break;
	default:
		break;
	}
	GraphicObject.G_R.pRenderTarget->DrawRectangle(Location, GraphicObject.G_R.B_Outline.pB, 1.0f);

	//Prepare text
	GraphicObject.G_R.pITextFormatR->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	GraphicObject.G_R.pITextFormatR->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	GraphicObject.G_R.pITextFormatS->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	GraphicObject.G_R.pITextFormatS->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	//Draw Text or keys
	if (Displayable)
	{
		//Displayable character
		GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 1, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
	}
	else
	{
		//Not Displayable
		switch (letter)
		{
		case 0x1B:	//Escape
		{
			temp.pop_back();
			temp.push_back('e');
			temp.push_back('s');
			temp.push_back('c');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 3, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x70:	//F1
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('1');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x71:	//F2
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('2');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x72:	//F3
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('3');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x73:	//F4
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('4');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x74:	//F5
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('5');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x75:	//F6
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('6');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x76:	//F7
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('7');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x77:	//F8
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('8');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x78:	//F9
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('9');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x79:	//F10
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('1');
			temp.push_back('0');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 3, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x7A:	//F11
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('1');
			temp.push_back('1');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 3, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x7B:	//F12
		{
			temp.pop_back();
			temp.push_back('F');
			temp.push_back('1');
			temp.push_back('2');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 3, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0xFF:	//Eject
		{
			//Es
			break;
		}
		case 0x08:	//Backkey (Delete key on MAC)
		{
			temp.pop_back();
			temp.push_back('d');
			temp.push_back('e');
			temp.push_back('l');
			temp.push_back('e');
			temp.push_back('t');
			temp.push_back('e');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 6, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x09:	//Tab
		{
			temp.pop_back();
			temp.push_back('t');
			temp.push_back('a');
			temp.push_back('b');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 3, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x14:	//Caps
		{
			temp.pop_back();
			temp.push_back('c');
			temp.push_back('a');
			temp.push_back('p');
			temp.push_back('s');
			temp.push_back(' ');
			temp.push_back('l');
			temp.push_back('o');
			temp.push_back('c');
			temp.push_back('k');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 9, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x0D:	//Return
		{
			temp.pop_back();
			temp.push_back('r');
			temp.push_back('e');
			temp.push_back('t');
			temp.push_back('u');
			temp.push_back('r');
			temp.push_back('n');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 6, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0xA0:	//LShift
		{
			temp.pop_back();
			temp.push_back('s');
			temp.push_back('h');
			temp.push_back('i');
			temp.push_back('f');
			temp.push_back('t');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 5, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0xA1:	//RShift
		{
			temp.pop_back();
			temp.push_back('s');
			temp.push_back('h');
			temp.push_back('i');
			temp.push_back('f');
			temp.push_back('t');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 5, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case NULL:	//Function Key
		{
			temp.pop_back();
			temp.push_back('f');
			temp.push_back('n');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 2, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0xA2:	//CTRL
		{
			temp.pop_back();
			temp.push_back('c');
			temp.push_back('o');
			temp.push_back('n');
			temp.push_back('t');
			temp.push_back('r');
			temp.push_back('o');
			temp.push_back('l');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 7, GraphicObject.G_R.pITextFormatS, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0xA4:	//LOption
		{
			temp.pop_back();
			temp.push_back('o');
			temp.push_back('p');
			temp.push_back('t');
			temp.push_back('i');
			temp.push_back('o');
			temp.push_back('n');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 6, GraphicObject.G_R.pITextFormatS, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x5B:	//LCommand
		{
			temp.pop_back();
			temp.push_back('c');
			temp.push_back('o');
			temp.push_back('m');
			temp.push_back('m');
			temp.push_back('a');
			temp.push_back('n');
			temp.push_back('d');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 7, GraphicObject.G_R.pITextFormatS, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x5C:	//RCommand
		{
			temp.pop_back();
			temp.push_back('c');
			temp.push_back('o');
			temp.push_back('m');
			temp.push_back('m');
			temp.push_back('a');
			temp.push_back('n');
			temp.push_back('d');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 7, GraphicObject.G_R.pITextFormatS, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0xA5:	//ROption
		{
			temp.pop_back();
			temp.push_back('o');
			temp.push_back('p');
			temp.push_back('t');
			temp.push_back('i');
			temp.push_back('o');
			temp.push_back('n');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 6, GraphicObject.G_R.pITextFormatS, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		case 0x25:	//LArrow
		{
			//Es
			break;
		}
		case 0x26:	//UArrow
		{
			//Es
			break;
		}
		case 0x28:	//DArrow
		{
			//Es
			break;
		}
		case 0x27:	//RArrow
		{
			//Es
			break;
		}
		default:
		{
			//Mistake
			temp.pop_back();
			temp.push_back('?');
			GraphicObject.G_R.pRenderTarget->DrawText(temp.c_str(), 1, GraphicObject.G_R.pITextFormatR, Location, GraphicObject.G_R.B_Font.pB);
			break;
		}
		}
	}
}
/**********Utility Functions**********/
void GraphComs::WinMessageBox(LPCWSTR Title, LPCWSTR Subject, int Type)
{
	/*
	Function: Allows calling function to display messages to the user.
	*/
	MessageBox(GraphicObject.hWnd, Subject, Title, Type);
}