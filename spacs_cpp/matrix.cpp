#include <matrix.h>
#include <string.h>
#include <assert.h>
#include <math.h>

namespace spa
{
	matrix::matrix()
	{
		memset(values, 0, sizeof(values));
		values[3][3] = 1.0f;
	}
	matrix::matrix(
		float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22)
	{
		values[0][0] = _00;
		values[0][1] = _01;
		values[0][2] = _02;
		values[0][3] = 0.0f;

		values[1][0] = _10;
		values[1][1] = _11;
		values[1][2] = _12;
		values[1][3] = 0.0f;

		values[2][0] = _20;
		values[2][1] = _21;
		values[2][2] = _22;
		values[2][3] = 0.0f;

		values[3][0] = 0.0f;
		values[3][1] = 0.0f;
		values[3][2] = 0.0f;
		values[3][3] = 1.0f;
	}
	matrix::matrix(const matrix & mat){ memcpy(values, mat.values, sizeof(values)); }
	matrix & matrix::operator=(const matrix & mat)
	{
		memcpy(values, mat.values, sizeof(values));
		return *this;
	}
	float matrix::operator()(unsigned int y, unsigned int x)
	{
		assert(x <= 3 && y <= 3);
		return values[y][x];
	}
	matrix matrix::operator*(const matrix & mat) const
	{
		matrix result;
		multi(result.values, this->values, mat.values);
		return result;
	}
	matrix & matrix::operator*=(const matrix & mat)
	{
		float copy[4][4];
		memcpy(copy, values, sizeof(values));

		multi(this->values, copy, mat.values);

		return *this;
	}

	void matrix::x(float value){ values[0][3] = value; }
	void matrix::y(float value){ values[1][3] = value; }
	void matrix::z(float value){ values[2][3] = value; }
	float  matrix::x() const { return values[0][3]; }
	float  matrix::y() const { return values[1][3]; }
	float  matrix::z() const { return values[2][3]; }

	matrix & matrix::trans(float vx, float vy, float vz)
	{
		values[0][0] = 1.0f;
		values[0][1] = 0.0f;
		values[0][2] = 0.0f;
		values[0][3] = vx;

		values[1][0] = 0.0f;
		values[1][1] = 1.0f;
		values[1][2] = 0.0f;
		values[1][3] = vy;

		values[2][0] = 0.0f;
		values[2][1] = 0.0f;
		values[2][2] = 1.0f;
		values[2][3] = vz;

		return *this;
	}
	matrix & matrix::scale(float magni_x, float magni_y, float magni_z)
	{
		values[0][0] = magni_x;
		values[0][1] = 0.0f;
		values[0][2] = 0.0f;
		values[0][3] = 0.0f;

		values[1][0] = 0.0f;
		values[1][1] = magni_y;
		values[1][2] = 0.0f;
		values[1][3] = 0.0f;

		values[2][0] = 0.0f;
		values[2][1] = 0.0f;
		values[2][2] = magni_z;
		values[2][3] = 0.0f;

		return *this;
	}
	matrix & matrix::rotatez(float radian)
	{
		return rotatez(::sin(radian), ::cos(radian));
	}
	matrix & matrix::rotatez(float sin, float cos)
	{
		values[0][0] = cos;  values[0][1] = sin;  values[0][2] = 0.0f;  values[0][3] = 0.0f;
		values[1][0] = -sin; values[1][1] = cos;  values[1][2] = 0.0f;  values[1][3] = 0.0f;
		values[2][0] = 0.0f; values[2][1] = 0.0f; values[2][2] = 1.0f;  values[2][3] = 0.0f;

		return *this;
	}
	matrix & matrix::affine(const matrix & scale, const matrix & rotate, const matrix & trans)
	{
		return *this = scale * rotate * trans;
	}

	void matrix::multi(float result[4][4], const float a[4][4], const float b[4][4])
	{
		for (int ay = 0; ay < 4; ++ay)
		{
			for (int bx = 0; bx < 4; ++bx)
			{
				float total = 0.0f;
				for (int cnt = 0; cnt < 4; ++cnt)
				{
					total += b[ay][cnt] * a[cnt][bx];
				}

				result[ay][bx] = total;
			}
		}
	}

}