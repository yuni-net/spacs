#include <image.h>
#include <math.h>
#include <top4_2D_spacs.h>

namespace spa
{
	float image::x(const float value){ return coor.x(value); }
	float image::x() const { return coor.x(); }
	float image::y(const float value){ return coor.y(value); }
	float image::y() const { return coor.y(); }
	float image::magni(const float value){ return coor.magni(value); }
	float image::magni() const { return coor.magni(); }
	float image::degree(const float value){ return coor.degree(value); }
	float image::degree() const { return coor.degree(); }
	float image::radian(const float value){ return coor.radian(value); }	// 回転角度。単位はラジアン
	float image::radian() const { return coor.radian(); }
	float image::sincos(const float sin_val, const float cos_val){ return coor.sincos(sin_val, cos_val); }	// 回転角度をサインとコサインで指定
	float image::sin() const { return coor.sin(); }
	float image::cos() const { return coor.cos(); }
	float image::rotcx(const float value){ return coor.rotcx(value); }	// 回転の中心となるx座標(画像の左上からの相対座標)
	float image::rotcx() const { return coor.rotcx(); }
	float image::rotcy(const float value){ return coor.rotcy(value); }	// 回転の中心となるy座標(画像の左上からの相対座標)
	float image::rotcy() const { return coor.rotcy(); }

	bool image::load(const char * path)
	{
		bool result = load_without_numset(path);
		numset();
		return result;
	}
	bool image::load(const char * path, unsigned char r, unsigned char g, unsigned b)	// 透過色指定用
	{
		bool result = load_without_numset(path, r, g, b);
		numset();
		return result;
	}
	//	bool image::load(const std::string & path){ return load(path.c_str()); }

	bool image::load_without_numset(const char * path)
	{
		release();
		spa::image_data * pNewImageData = new spa::image_data();
		bool result = pNewImageData->load(path);
		pImageData = pNewImageData;
		ownership = true;
		return result;
	}
	bool image::load_without_numset(const char * path, unsigned char r, unsigned char g, unsigned b)
	{
		release();
		spa::image_data * pNewImageData = new spa::image_data();
		bool result = pNewImageData->load(path, r, g, b);
		pImageData = pNewImageData;
		ownership = true;
		return result;
	}
	//	bool image::load_without_numset(const std::string & path){ return load_without_numset(path.c_str()); }

	void image::image_data(const spa::image_data & target)
	{
		image_data_without_numset(target);
		numset();
	}
	void image::image_data_without_numset(const spa::image_data & target)
	{
		release();
		pImageData = &target;
	}

	float image::width() const { return static_cast<float>(pImageData->width())*magni(); }
	float image::height() const { return static_cast<float>(pImageData->height())*magni(); }

	void image::draw() const { draw(0.0f, 0.0f); }
	void image::draw(const float basex, const float basey) const
	{
		top4_2D xy;
		xy.set(
			basex + x(), basey + y(),
			width(), height(),
			magni(),
			radian(),
			rotcx(), rotcy());

		top4_2D uv;
		set_uv(uv);

		pImageData->draw(xy, uv);
	}



	image::image()
	{
		pImageData = nullptr;
		ownership = false;
	}

	image::~image()
	{
		release();
	}

	void image::release()
	{
		if (ownership == true)
		{
			delete pImageData;
		}

		pImageData = nullptr;
		ownership = false;
	}

	void image::numset()
	{
		magni(1.0f);
		radian(0.0f);
		rotcx(width() / 2.0f);
		rotcy(height() / 2.0f);
	}

	void image::set_uv(top4_2D & uv) const
	{
		uv.lt.x = 0.0f;
		uv.lt.y = 0.0f;

		uv.rt.x = 1.0f;
		uv.rt.y = 0.0f;

		uv.rb.x = 1.0f;
		uv.rb.y = 1.0f;

		uv.lb.x = 0.0f;
		uv.lb.y = 1.0f;
	}
}
