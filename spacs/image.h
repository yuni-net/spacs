#pragma once
#include "type_spacs.h"
#include "util_spacs.h"
#include "image_data.h"
#include "image_coor.h"

namespace spa
{
	class image
	{
	public:
		float x(const float value);
		float x() const;
		float y(const float value);
		float y() const;
		float magni(const float value);
		float magni() const;
		float degree(const float value);	// ��]�p�x�B�P�ʂ͓x
		float degree() const;
		float radian(const float value);	// ��]�p�x�B�P�ʂ̓��W�A��
		float radian() const;
		float sincos(const float sin_val, const float cos_val);	// ��]�p�x���T�C���ƃR�T�C���Ŏw��
		float sin() const;
		float cos() const;
		float rotcx(const float value);	// ��]�̒��S�ƂȂ�x���W(�摜�̍��ォ��̑��΍��W)
		float rotcx() const;
		float rotcy(const float value);	// ��]�̒��S�ƂȂ�y���W(�摜�̍��ォ��̑��΍��W)
		float rotcy() const;

		bool load(const char * path);
		bool load(const char * path, unsigned char r, unsigned char g, unsigned b);	// ���ߐF�w��p
//		bool load(const std::string & path);

		bool load_without_numset(const char * path);
		bool load_without_numset(const char * path, unsigned char r, unsigned char g, unsigned b);
		//		bool load_without_numset(const std::string & path);

		void image_data(const spa::image_data & target);
		void image_data_without_numset(const spa::image_data & target);

		virtual float width() const;
		virtual float height() const;
		void draw() const;
		void draw(const float basex, const float basey) const;







		image();
		~image();
	protected:
		image_coor coor;

		const spa::image_data * pImageData;
		bool ownership;

		void release();
		void numset();
		virtual void set_uv(top4_2D & uv) const;
	};
}