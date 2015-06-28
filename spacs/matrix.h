#pragma once

namespace spa
{
	/*
	* Š|‚¯Z‚Í’Êí‰‰Z‚Ì‚Æ‚«‚Æ“¯‚¶‡”Ô‚Å‹Lq‚µ‚Ä—Ç‚¢B
	*/
	class matrix
	{
	public:
		matrix();
		matrix(
			float _00, float _01, float _02,
			float _10, float _11, float _12,
			float _20, float _21, float _22);
		matrix(const matrix & mat);
		matrix & operator=(const matrix & mat);
		float operator()(unsigned int y, unsigned int x);
		matrix operator*(const matrix & mat) const;
		matrix & operator*=(const matrix & mat);

		void x(float value);
		void y(float value);
		void z(float value);
		float  x() const;
		float  y() const;
		float  z() const;

		matrix & trans(float vx, float vy, float vz);
		matrix & scale(float magni_x, float magni_y, float magni_z);
		matrix & rotatez(float radian);
		matrix & rotatez(float sin, float cos);
		matrix & affine(const matrix & scale, const matrix & rotate, const matrix & trans);




	private:
		float values[4][4];
		float _00, _01, _02, _03;
		float _10, _11, _12, _13;
		float _20, _21, _22, _23;
		float _30, _31, _32, _33;

		static void multi(float result[4][4], const float a[4][4], const float b[4][4]);
	};
}