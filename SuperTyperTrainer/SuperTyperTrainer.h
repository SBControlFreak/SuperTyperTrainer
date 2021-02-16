#pragma once

#include "resource.h"
#include "KeyBoard.h"

GraphComs MainGraph;
D2D1_RECT_F LocTest_;
WCHAR letterTest = 'A';
KeyBoardController KeyBoardCon(&MainGraph);
