#include <image_drawer.h>

namespace spa
{
	void image_drawer::draw(const GLuint id, const top4_2D & xy, const top4_2D & uv)
	{
		const GLfloat vtx[] = {
			xy.lt.x, xy.lt.y,
			xy.rt.x, xy.rt.y,
			xy.rb.x, xy.rb.y,
			xy.lb.x, xy.lb.y,
		};

		static const GLfloat texuv[] = {
			uv.lt.x, uv.lt.y,
			uv.rt.x, uv.rt.y,
			uv.rb.x, uv.rb.y,
			uv.lb.x, uv.lb.y,
		};


		glVertexPointer(2, GL_FLOAT, 0/*�z��̃I�t�Z�b�g*/, vtx);
		// Step5. �e�N�X�`���̗̈�w��
		glTexCoordPointer(2, GL_FLOAT, 0, texuv);
		// Step6. �e�N�X�`���̉摜�w��
		glBindTexture(GL_TEXTURE_2D, id);


		// Step7. �e�N�X�`���̕`��
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);

	}
}