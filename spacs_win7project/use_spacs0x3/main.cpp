#include <spacs.h>

int main()
{

	spa::manager::init();

	while (spa::manager::ok())
	{
		spa::manager::clear();

		// todo

		spa::manager::show();
	}

	return 0;
}