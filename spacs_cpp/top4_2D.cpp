#include <top4_2D_spacs.h>
#include <matrix.h>

namespace spa
{
	void top4_2D::set(
		const float x, const float y,
		const float width, const float height,
		const float magni,
		const float radian,
		const float rotcx, const float rotcy)
	{
		matrix affine;
		affine.affine(
			matrix().scale(magni, magni, 1.0f),
			matrix().rotatez(radian),
			matrix().trans(rotcx, rotcy, 0.0f));

		const float basex = x - rotcx;
		const float basey = y - rotcy;

		matrix lt;
		lt.x(basex);
		lt.y(basey);

		matrix rt;
		rt.x(basex + width);
		rt.y(basey);

		matrix rb;
		rb.x(basex + width);
		rb.y(basey + height);

		matrix lb;
		lb.x(basex);
		lb.y(basey + height);

		lt *= affine;
		rt *= affine;
		rb *= affine;
		lb *= affine;

		this->lt.x = lt.x();
		this->lt.y = lt.y();

		this->rt.x = rt.x();
		this->rt.y = rt.y();

		this->rb.x = rb.x();
		this->rb.y = rb.y();

		this->lb.x = lb.x();
		this->lb.y = lb.y();
	}
}