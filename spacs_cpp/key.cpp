#include <key.h>
#include <manager.h>
#include <cstring>

namespace spa
{
	bool key::pushing(int key)
	{
		return singleton().nowkey(key);
	}
	bool key::releasing(int key)
	{
		return singleton().nowkey(key) == false;
	}

	bool key::pushed(int key)
	{
		if (singleton().nowkey(key) &&
			singleton().oldkey(key) == false)
		{
			return true;
		}

		return false;
	}
	bool key::released(int key)
	{
		if (singleton().oldkey(key) &&
			singleton().nowkey(key) == false)
		{
			return true;
		}

		return false;
	}


	key & key::singleton()
	{
		static key instance;
		return instance;
	}
	key::key()
	{
		memset(buffer[active], 0, sizeof(buffer[active]));
		memset(buffer[!active], 0, sizeof(buffer[!active]));
	}
	void key::renew()
	{
		active = !active;

		for (int key = 0; key < GLFW_KEY_LAST + 1; ++key)
		{
			nowkey(key) = (glfwGetKey(manager::window(), key) == GL_TRUE);
		}
	}

	bool & key::nowkey(int key)
	{
		return buffer[active][key];
	}
	bool & key::oldkey(int key)
	{
		return buffer[!active][key];
	}

}