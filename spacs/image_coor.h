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
		float degree(const float value);	// 回転角度。単位は度
		float degree() const;
		float radian(const float value);	// 回転角度。単位はラジアン
		float radian() const;
		float sincos(const float sin_val, const float cos_val);	// 回転角度をサインとコサインで指定
		float sin() const;
		float cos() const;
		float rotcx(const float value);	// 回転の中心となるx座標(画像の左上からの相対座標)
		float rotcx() const;
		float rotcy(const float value);	// 回転の中心となるy座標(画像の左上からの相対座標)
		float rotcy() const;



	private:
		float x_;
		float y_;
		float radian_;
		float rotcx_;	// 回転の中心となるx座標(画像の左上からの相対座標)
		float rotcy_;	// 回転の中心となるy座標(画像の左上からの相対座標)
		float magni_;

	};
}