#include <image_coor.h>
#include <math.h>

namespace spa
{
	float image_coor::x(const float value){ return x_ = value; }
	float image_coor::x() const { return x_; }
	float image_coor::y(const float value){ return y_ = value; }
	float image_coor::y() const { return y_; }
	float image_coor::magni(const float value){ return magni_ = value; }
	float image_coor::magni() const { return magni_; }

	float image_coor::degree(const float value)
	{
		radian(value*3.14159265f / 180.0f);
		return value;
	}

	float image_coor::degree() const
	{
		return radian()*180.0f / 3.14159265f;
	}

	float image_coor::radian(const float value){ return radian_ = value; }	// ��]�p�x�B�P�ʂ̓��W�A��
	float image_coor::radian() const { return radian_; }

	float image_coor::sincos(const float sin_val, const float cos_val)	// ��]�p�x���T�C���ƃR�T�C���Ŏw��
	{
		const float pi = 3.14159265f;
		const float pi2 = 2.0f * pi;

		if (cos_val < 0.000000001f)
		{
			radian(pi2 - asin(sin_val));
		}
		else
		{
			radian(asin(sin_val));
		}

		return radian();
	}

	float image_coor::sin() const
	{
		return ::sin(radian());
	}
	float image_coor::cos() const
	{
		return ::cos(radian());
	}

	float image_coor::rotcx(const float value){ return rotcx_ = value; }	// ��]�̒��S�ƂȂ�x���W(�摜�̍��ォ��̑��΍��W)
	float image_coor::rotcx() const { return rotcx_; }
	float image_coor::rotcy(const float value){ return rotcy_ = value; }	// ��]�̒��S�ƂȂ�y���W(�摜�̍��ォ��̑��΍��W)
	float image_coor::rotcy() const { return rotcy_; }

}