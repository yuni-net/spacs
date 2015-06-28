#include <spacs.h>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{

	spa::manager::init();

	while(spa::manager::ok())
	{
		spa::manager::clear();

		// todo

		spa::manager::show();
	}

	return 0;
}