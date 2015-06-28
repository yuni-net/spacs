#pragma once

#include "coor2D_spacs.h"

namespace spa
{
	struct top4_2D
	{
		coor2D lt;
		coor2D rt;
		coor2D rb;
		coor2D lb;

		void set(
			const float x, const float y,
			const float width, const float height,
			const float magni,
			const float radian,
			const float rotcx, const float rotcy);
	};
}