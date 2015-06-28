#pragma once

#include "util_spacs.h"

namespace spa
{
	class key
	{
	public:
		static bool pushing(int key);
		static bool releasing(int key);

		static bool pushed(int key);
		static bool released(int key);

		enum
		{
			slash = GLFW_KEY_SLASH,  /* / */
			back_slash = GLFW_KEY_BACKSLASH,  /* \ */
			world_1 = GLFW_KEY_WORLD_1, /* non-US #1 */
			world_2 = GLFW_KEY_WORLD_2, /* non-US #2 */

			/* Function keys */
			esc = GLFW_KEY_ESCAPE,
			enter = GLFW_KEY_ENTER,
			tab = GLFW_KEY_TAB,
			backspace = GLFW_KEY_BACKSPACE,
			insert = GLFW_KEY_INSERT,
			Delete = GLFW_KEY_DELETE,
			right = GLFW_KEY_RIGHT,
			left = GLFW_KEY_LEFT,
			down = GLFW_KEY_DOWN,
			up = GLFW_KEY_UP,
			page_up = GLFW_KEY_PAGE_UP,
			page_down = GLFW_KEY_PAGE_DOWN,
			home = GLFW_KEY_HOME,
			end = GLFW_KEY_END,
			lock = GLFW_KEY_CAPS_LOCK,
			scroll_lock = GLFW_KEY_SCROLL_LOCK,
			num_lock = GLFW_KEY_NUM_LOCK,
			print_screen = GLFW_KEY_PRINT_SCREEN,
			pause = GLFW_KEY_PAUSE,
			F1 = GLFW_KEY_F1,
			F2 = GLFW_KEY_F2,
			F3 = GLFW_KEY_F3,
			F4 = GLFW_KEY_F4,
			F5 = GLFW_KEY_F5,
			F6 = GLFW_KEY_F6,
			F7 = GLFW_KEY_F7,
			F8 = GLFW_KEY_F8,
			F9 = GLFW_KEY_F9,
			F10 = GLFW_KEY_F10,
			F11 = GLFW_KEY_F11,
			F12 = GLFW_KEY_F12,
			F13 = GLFW_KEY_F13,
			F14 = GLFW_KEY_F14,
			F15 = GLFW_KEY_F15,
			F16 = GLFW_KEY_F16,
			F17 = GLFW_KEY_F17,
			F18 = GLFW_KEY_F18,
			F19 = GLFW_KEY_F19,
			F20 = GLFW_KEY_F20,
			F21 = GLFW_KEY_F21,
			F22 = GLFW_KEY_F22,
			F23 = GLFW_KEY_F23,
			F24 = GLFW_KEY_F24,
			F25 = GLFW_KEY_F25,
			KP_0 = GLFW_KEY_KP_0,
			KP_1 = GLFW_KEY_KP_1,
			KP_2 = GLFW_KEY_KP_2,
			KP_3 = GLFW_KEY_KP_3,
			KP_4 = GLFW_KEY_KP_4,
			KP_5 = GLFW_KEY_KP_5,
			KP_6 = GLFW_KEY_KP_6,
			KP_7 = GLFW_KEY_KP_7,
			KP_8 = GLFW_KEY_KP_8,
			KP_9 = GLFW_KEY_KP_9,
			KP_decimal = GLFW_KEY_KP_DECIMAL,
			KP_divide = GLFW_KEY_KP_DIVIDE,
			KP_multiply = GLFW_KEY_KP_MULTIPLY,
			KP_subtract = GLFW_KEY_KP_SUBTRACT,
			KP_add = GLFW_KEY_KP_ADD,
			KP_enter = GLFW_KEY_KP_ENTER,
			KP_equal = GLFW_KEY_KP_EQUAL,
			left_shift = GLFW_KEY_LEFT_SHIFT,
			control = GLFW_KEY_LEFT_CONTROL,
			left_alt = GLFW_KEY_LEFT_ALT,
			left_super = GLFW_KEY_LEFT_SUPER,
			right_shift = GLFW_KEY_RIGHT_SHIFT,
			right_control = GLFW_KEY_RIGHT_CONTROL,
			right_alt = GLFW_KEY_RIGHT_ALT,
			right_super = GLFW_KEY_RIGHT_SUPER,
			menu = GLFW_KEY_MENU
		};







		static key & singleton();
		key();
		void renew();
	private:
		bool buffer[2][GLFW_KEY_LAST + 1];
		bool active;

		bool & nowkey(int key);
		bool & oldkey(int key);
	};
}