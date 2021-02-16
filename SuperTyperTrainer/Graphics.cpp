#include "Graphics.h"
/***********BrushColor Class*************/
BrushColor::BrushColor()
{}
BrushColor::~BrushColor()
{
	SafeRelease(&pB);
}
HRESULT BrushColor::CreateBrush(ID2D1HwndRenderTarget* pRenderTarget_)
{
	return pRenderTarget_->CreateSolidColorBrush(C, &pB);
}
void BrushColor::DestroyBrush()
{
	SafeRelease(&pB);
}

/***********Graphics Class*************/
Graphics::Graphics()
{
	UserDefault = true;
}
Graphics::~Graphics()
{
	//Release Direct 2D Variables
	SafeRelease(&G_R.pFactory);
	SafeRelease(&G_R.pRenderTarget);
	SafeRelease(&G_R.Sink);
	SafeRelease(&G_R.strokeStyle);

	//Release DirectWrite Variables
	SafeRelease(&G_R.pIDWriteFactory);
	SafeRelease(&G_R.pITextFormat);
	return;
}

//Functions
HRESULT Graphics::CreateG_Resources(HWND& hWnd_)
{
	/*
	Function: Creates all the needed graphic objects.
	*/
	hWnd = hWnd_;
	G_R.Font_Name = L"Consolas";
	G_R.Font_Size = 12.0;
	G_R.Font_Width = G_R.Font_Width_Base = 6.5977;
	HRESULT hr = S_OK;
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &G_R.pFactory)))
	{
		return -1;
	}
	if (G_R.pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		hr = G_R.pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&G_R.pRenderTarget);

		if (SUCCEEDED(hr))
		{
			//B_KeyBG_Normal, B_KeyBG_Next, B_KeyBG_Wrong, B_Outline, B_Font, B_Scroll_B, B_Scroll_F
			if (UserDefault)
			{
				// Direct2D Variables
				G_R.B_KeyBG_Normal.C = D2D1::ColorF(D2D1::ColorF::AntiqueWhite);
				G_R.B_KeyBG_Next.C = D2D1::ColorF(D2D1::ColorF::LightGreen);
				G_R.B_KeyBG_Wrong.C = D2D1::ColorF(D2D1::ColorF::Red);
				G_R.B_KeyBoardFrame.C = D2D1::ColorF(D2D1::ColorF::LightGray);
				G_R.B_Outline.C = D2D1::ColorF(D2D1::ColorF::Black);
				G_R.B_Font.C = D2D1::ColorF(D2D1::ColorF::Black);
				G_R.B_Scroll_B.C = D2D1::ColorF(D2D1::ColorF::LightGray);
				G_R.B_Scroll_F.C = D2D1::ColorF(D2D1::ColorF::Gray);
				G_R.B_Background.C = D2D1::ColorF(D2D1::ColorF::White);
			}

			hr = G_R.B_KeyBG_Normal.CreateBrush(G_R.pRenderTarget);
			hr = G_R.B_KeyBG_Next.CreateBrush(G_R.pRenderTarget);
			hr = G_R.B_KeyBG_Wrong.CreateBrush(G_R.pRenderTarget);
			hr = G_R.B_KeyBoardFrame.CreateBrush(G_R.pRenderTarget);
			hr = G_R.B_Outline.CreateBrush(G_R.pRenderTarget);
			hr = G_R.B_Font.CreateBrush(G_R.pRenderTarget);
			hr = G_R.B_Scroll_B.CreateBrush(G_R.pRenderTarget);
			hr = G_R.B_Scroll_F.CreateBrush(G_R.pRenderTarget);
			hr = G_R.B_Background.CreateBrush(G_R.pRenderTarget);

			//Direct Write
			if (SUCCEEDED(hr))
			{
				hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
					__uuidof(IDWriteFactory),
					reinterpret_cast<IUnknown**>(&G_R.pIDWriteFactory));
			}

			if (SUCCEEDED(hr))
			{
				hr = G_R.pIDWriteFactory->CreateTextFormat(
					G_R.Font_Name.c_str(),
					NULL,
					DWRITE_FONT_WEIGHT_NORMAL,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_NORMAL,
					G_R.Font_Size,
					L"en-US",
					&G_R.pITextFormat);
			}
		}
	}
	return hr;
}
void Graphics::DestroyG_Resources()
{
	//Release Direct 2D Variables
	SafeRelease(&G_R.pFactory);
	SafeRelease(&G_R.pRenderTarget);
	SafeRelease(&G_R.Sink);
	SafeRelease(&G_R.strokeStyle);

	G_R.B_KeyBG_Normal.DestroyBrush();
	G_R.B_KeyBG_Next.DestroyBrush();
	G_R.B_KeyBG_Wrong.DestroyBrush();
	G_R.B_Background.DestroyBrush();
	G_R.B_Font.DestroyBrush();
	G_R.B_Outline.DestroyBrush();
	G_R.B_Scroll_B.DestroyBrush();
	G_R.B_Scroll_F.DestroyBrush();

	//Release DirectWrite Variables
	SafeRelease(&G_R.pIDWriteFactory);
	SafeRelease(&G_R.pITextFormat);
	return;
}
//template <class T> void Graphics::OnPaint(T** ppT)
//{
//	HRESULT hr;
//
//	if (*ppT)
//	{
//		//RECT rc;
//		//GetClientRect(hWnd, &rc);
//		//D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
//
//		if (G_R.pRenderTarget != nullptr)
//		{
//			G_R.pRenderTarget->BeginDraw();
//			//pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
//			(*ppT)->OnPaint();
//			/************Finish Drawing********/
//			hr = G_R.pRenderTarget->EndDraw();
//		}
//		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
//		{
//			//DiscardGraphicsResources(hWnd);
//			MessageBox(hWnd, L"Failed to Draw", L"Graphics Error", MB_OK);
//		}
//	}
//}
void Graphics::Resize()
{
	//Resizing is required to recalculate the logical coordinates for proper drawing
	if (G_R.pRenderTarget != NULL)
	{
		GetClientRect(hWnd, &G_R.rc);

		D2D1_SIZE_U size = D2D1::SizeU(G_R.rc.right, G_R.rc.bottom);

		G_R.pRenderTarget->Resize(size);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	return;
}