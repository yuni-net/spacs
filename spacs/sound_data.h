#pragma once

#include "util_spacs.h"

namespace spa
{
	class sound_data
	{
	public:
		bool load(const char * path);
	//	bool load(const std::string & path);



		sound_data();
		void gen(GLuint source) const;
		~sound_data();
	private:
		GLuint buffer;

		void release();
	};
}