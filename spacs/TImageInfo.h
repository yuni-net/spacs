#pragma once

namespace spa
{
	struct TImageInfo
	{
		int nWidth;					// �摜�̉���(�s�N�Z����)�������Ɋi�[���Ă�������
		int nHeight;				// �摜�̏c��(�s�N�Z����)�������Ɋi�[���Ă��������B�}�C�i�X�l���i�[����ƁARGB��񂪏ォ�牺�Ɍ������Ċi�[����Ă���Ɣ��f����܂�
		unsigned char * pbyPixels;	// RGB�����i�[���郁�����̈��malloc�Ŋm�ۂ��A���̐擪�A�h���X�������Ɋi�[���Ă�������
		/*
		 * R,G,B�͂��ꂼ��1�o�C�g�ł�
		 * R��G��B��R��G��B��R�c�ƂȂ�悤�Ƀf�[�^���i�[���Ă�������
		 * �C���g����2�����z��ɂ���K�v�͂���܂���
		 */
		bool bEffective;			// true...�Ή��\�t�@�C���`���@false...�Ή��s�t�@�C���`��
	};
}