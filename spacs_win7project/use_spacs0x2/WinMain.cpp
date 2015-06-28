#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#include <spacs.h>
#include <cassert>

int main(int argc, char * argv[])
{

	spa::manager::init(&argc, argv);

	spa::sound bgm;
	bgm.load("test.wav");
	bgm.loop();

	spa::image tex;
	tex.load("texture.bmp");
	tex.x(0.0f);
	tex.y(0.0f);

	while (spa::manager::ok())
	{
		float speed = 2.0f;

		if (spa::key::pushing(spa::key::up))
		{
			tex.y(tex.y() + speed);
		}
		if (spa::key::pushing(spa::key::right))
		{
			tex.x(tex.x() + speed);
		}
		if (spa::key::pushing(spa::key::down))
		{
			tex.y(tex.y() - speed);
		}
		if (spa::key::pushing(spa::key::left))
		{
			tex.x(tex.x() - speed);
		}

		spa::manager::clear();

		tex.draw();

		spa::manager::show();
	}

	return 0;
}