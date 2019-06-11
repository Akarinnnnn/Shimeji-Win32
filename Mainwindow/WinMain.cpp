#include "framework.h"
#include <future>
#include <string>
#include <thread>
#include "../D2DBitmapRead/BitmapRead.h"
#include "D2DWindow.h"
#include "com_uniqueptr.h"
#include "../Exceptions/HRESULT_exception.h"
std::shared_ptr<ID2D1Factory> D2DFactory;
using namespace std;

std::shared_ptr<ID2D1Factory> CreateFactory()
{
	ID2D1Factory* rawfactory = nullptr;
	HRESULT last_result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &rawfactory);
	if (FAILED(last_result))
		throw COM_helper::HRESULT_exception("Create D2D Factory failed.", last_result);
	return shared_ptr<ID2D1Factory>(rawfactory, COM_helper::COM_Deleter());
}

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previnst, wchar_t* cmdline, int cmdshow)
{
	try
	{
		D2DFactory = CreateFactory();
		D2DHelper::D2DWindowV3 theWindow(D2DFactory, instance);
		theWindow.show(cmdshow);
		return theWindow.run_msgloop();
	}
	catch (std::exception& e)
	{
		exception2msgbox(e,"wWinMain");
	}
}

