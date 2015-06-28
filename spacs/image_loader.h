#pragma once

#include "util_spacs.h"
#include "TImageInfo.h"

namespace spa
{
	class image_loader
	{
	public:
		static bool load(const char * path, GLuint & id, uint & width, uint & height);
		static bool load(const char * path, GLuint & id, uint & width, uint & height, unsigned char r, unsigned char g, unsigned b);







	private:
		static TImageInfo * GetImageInfo(const char * path);
		static TImageInfo * GetBMPInfo(const char * path);
	};
}