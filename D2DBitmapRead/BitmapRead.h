﻿// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BITMAPREAD_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BITMAPREAD_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef D2DBITMAPREAD_EXPORTS
#define BITMAPREAD_API __declspec(dllexport)
#else
#define BITMAPREAD_API __declspec(dllimport)
#endif
#include <wincodec.h>
#include <d2d1.h>
#include <memory>
#include <exception>
#include "..\Exceptions\HRESULT_exception.h"
#include "../Mainwindow/com_uniqueptr.h"

//导出的命名空间
namespace D2DHelper 
{
	class BITMAPREAD_API bmpreader
	{
	public:
		bmpreader();
		bmpreader(ID2D1RenderTarget* RenderTarget);
		ID2D1Bitmap* read(const wchar_t * filename);
	private:
		COM_helper::unique_com<IWICImagingFactory2> WICFactory;
		ID2D1RenderTarget* RenderTarget;
	};
}
