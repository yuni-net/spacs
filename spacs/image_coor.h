#pragma once

namespace spa
{
	class image_coor
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



	private:
		float x_;
		float y_;
		float radian_;
		float rotcx_;	// ��]�̒��S�ƂȂ�x���W(�摜�̍��ォ��̑��΍��W)
		float rotcy_;	// ��]�̒��S�ƂȂ�y���W(�摜�̍��ォ��̑��΍��W)
		float magni_;

	};
}