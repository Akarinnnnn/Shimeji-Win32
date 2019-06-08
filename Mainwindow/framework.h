// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
//#include <afxwin.h>  
//#include <afxdisp.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


//C++标准库头文件
#include <memory>
#include <iostream>
#include <string>
#include <vector>

//D2D头文件
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

//其他文件
#include "..\Exceptions\HRESULT_exception.h"