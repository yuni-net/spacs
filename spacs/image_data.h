#pragma once

#include "util_spacs.h"
#include "top4_2D_spacs.h"
#include "image_coor.h"

namespace spa
{
	class image_data
	{
	public:
		bool load(const char * path);
		bool load(const char * path, unsigned char r, unsigned char g, unsigned b);
		//	bool load(const std::string & path);
		uint width() const;
		uint height() const;






		void draw(const top4_2D & xy, const top4_2D & uv) const;
		image_data();
		~image_data();
	private:
		uint width_;
		uint height_;
		GLuint id;

		void safe_delete();
	};
}