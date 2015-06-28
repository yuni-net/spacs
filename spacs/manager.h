#pragma once

#include "util_spacs.h"

namespace spa
{
	class manager
	{
	public:
		static bool init(int * argc, char ** argv);
		static bool ok();		// Do call it before process of each frame
		static void clear();	// Clearing screen data
		static void show();		// Screen will be updated





		static manager & instance();
		static GLFWwindow * window();
		~manager();
	private:
		bool init_(int * argc, char ** argv);
		bool ok_();
		void clear_();
		void show_();

		GLFWwindow * window_;
	};
}