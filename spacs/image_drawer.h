#pragma once

#include "util_spacs.h"
#include "top4_2D_spacs.h"
#include "image_coor.h"

namespace spa
{
	class image_drawer
	{
	public:
		static void draw(const GLuint id, const top4_2D & xy, const top4_2D & uv);
	};
}