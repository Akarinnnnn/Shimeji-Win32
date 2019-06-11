#include "framework.h"
using namespace std;
void exception2msgbox(exception& e, const char hint[32])
{
	char out[48] = { 0 };
	sprintf_s<48>(out, "��%s��%s", hint, "����C++�쳣");
	MessageBoxExA(nullptr, e.what(), out, MB_OK | MB_ICONWARNING, 0);
}