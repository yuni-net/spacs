#include "image_loader.h"

namespace spa
{
	TImageInfo * image_loader::GetImageInfo(const char * path)
	{
		// todo�@�g���q�ɂ���ēK�؂ȃt�@�C����͊֐����ĂԎ����ɂ��邱�ƁB�J���Ă݂Ĉ�����ꍇ�A�S�ʂ莎���B
		return GetBMPInfo(path);	// �b��I��BMP�t�@�C���Ō��ߑł�
	}
}