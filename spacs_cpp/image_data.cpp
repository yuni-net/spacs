#include <image_data.h>
#include <image_loader.h>
#include <image_drawer.h>

namespace spa
{
	bool image_data::load(const char * path)
	{
		safe_delete();
		return image_loader::load(path, id, width_, height_);
	}
	bool image_data::load(const char * path, unsigned char r, unsigned char g, unsigned b)
	{
		safe_delete();
		return image_loader::load(path, id, width_, height_, r,g,b);
	}
	//	bool image_data::load(const std::string & path){ return load(path.c_str()); }

	uint image_data::width() const
	{
		return width_;
	}

	uint image_data::height() const
	{
		return height_;
	}









	void image_data::draw(const top4_2D & xy, const top4_2D & uv) const
	{
		return image_drawer::draw(id, xy, uv);
	}

	image_data::image_data()
	{
		id = NULL;
	}

	image_data::~image_data()
	{
		safe_delete();
	}

	void image_data::safe_delete()
	{
		if (id != NULL)
		{
			glDeleteTextures(1, &id);
			id = NULL;
		}
	}
}