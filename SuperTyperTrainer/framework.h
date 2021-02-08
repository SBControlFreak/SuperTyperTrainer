// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <vector>

//Direct2D and DirectWrite Libraries
#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1")	//Needed to tell linker to link the library
#pragma comment(lib, "Dwrite")	//Needed to tell linker to link the library

using namespace std;

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}
