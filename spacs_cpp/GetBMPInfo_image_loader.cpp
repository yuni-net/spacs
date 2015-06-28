#include "image_loader.h"
#pragma warning(push)
#pragma warning(disable:4996)
#include <cstdio>
#include <cstdlib>

namespace spa
{

	static const int FILE_HEADER_BYTE = 14;
	static const int BYTE_OF_INFO_HEADER_SIZE = 4;
	static const int SIZE_OF_CORE_HEADER = 12;
	static const int SIZE_OF_INFO_HEADER = 40;

	//==========================================
	// �֐� : LoadBMP
	// �ړI : BMP�̃��[�h
	// �߂�l: TImageInfo *	���ǂݍ��݂Ɏ��s�����ꍇ��NULL��Ԃ�
	// ���� : const char *pszFName	�t�@�C����
	//==========================================
	TImageInfo * LoadBMP(const char *pszFName);

	//==========================================
	// �֐� : LoadHeader
	// �ړI : BMP�t�@�C���̃t�@�C���w�b�_���̓ǂݍ���
	// �߂�l: bool ����...true, ���s...false
	// ���� : FILE * pf	�t�@�C���|�C���^
	//==========================================
	bool LoadHeader(FILE * pf);

	//==========================================
	// �֐� : LoadInfo
	// �ړI : BMP�t�@�C���̏��w�b�_���̓ǂݍ���
	// �߂�l: bool ����...true, ���s...false
	// ���� : FILE * pf	�t�@�C���|�C���^
	//        int * pnWidth  �������i�[�������ϐ��ւ̃A�h���X
	//        int * pnHeight �c�����i�[�������ϐ��ւ̃A�h���X
	//        unsigned short * pwBitCount    �r�b�g�����i�[�������ϐ��ւ̃A�h���X
	//        unsigned long * pdwCompression ���k�����i�[�������ϐ��ւ̃A�h���X
	//==========================================
	bool LoadInfo(FILE * pf, int * pnWidth, int * pnHeight, unsigned short * pwBitCount, unsigned long * pdwCompression);

	//==========================================
	// �֐� : ComputePaddingByte
	// �ړI : �s�v�ȃf�[�^�̃o�C�g�������߂Ă����Ԃ�
	// �߂�l: long �s�v�ȃf�[�^�̃o�C�g��
	// ���� : int nWidth �摜�̉���(�s�N�Z����)
	//==========================================
	long ComputePaddingByte(int nWidth);

	//==========================================
	// �֐� : BGR_to_RGB
	// �ړI : BGR�̏��ɕ���ł���F����RGB�̏��ɕ��בւ���
	// �߂�l: �Ȃ�
	// ���� : unsigned char * pbyRGBDatas RGB��񂪊i�[���ꂽ�������̐擪�A�h���X
	//        unsigned int uPixelNum �摜�̑��s�N�Z����
	//==========================================
	void BGR_to_RGB(unsigned char * pbyRGBDatas, unsigned int uPixelNum);

	//==========================================
	// �֐� : LoadRGB
	// �ړI : RGB����ǂݍ���
	// �߂�l: unsigned char * RGB��񂪊i�[���ꂽ�������̃A�h���X�B�ǂݍ��݂Ɏ��s�����ꍇNULL��Ԃ�
	// ���� : FILE * pf   �t�@�C���|�C���^
	//        int nWidth  �摜�̉���(�s�N�Z����)
	//        int nHeight �摜�̏c��(�s�N�Z����)
	//==========================================
	unsigned char * LoadRGB(FILE * pf, int nWidth, int nHeight);

	//==========================================
	// �֐� : LoadBMPFromFilePointer
	// �ړI : �󂯎�����t�@�C���|�C���^������BMP�t�@�C���̃��[�h
	// �߂�l: TImageInfo	���ǂݍ��݂Ɏ��s�����ꍇ��NULL��Ԃ�
	// ���� : FILE * pf	�t�@�C���|�C���^
	//==========================================
	TImageInfo * LoadBMPFromFilePointer(FILE * pf);

	TImageInfo * image_loader::GetBMPInfo(const char * path)
	{
		// BMP��ǂݍ���
		TImageInfo * pImageInfo = LoadBMP(path);

		// BMP�ǂݍ��߂Ȃ������ꍇ�̃G���[����
		if (pImageInfo == nullptr)
		{
			return nullptr;
		}

		// BMP�t�@�C���̌`���ɑΉ����Ă��Ȃ������ꍇ�̃G���[����
		if (pImageInfo->bEffective == false)
		{
			if (pImageInfo->pbyPixels)
			{
				free(pImageInfo->pbyPixels);
			}
			free(pImageInfo);
			return nullptr;
		}

		return pImageInfo;
	}



	//==========================================
	// �֐� : LoadBMP
	// �ړI : BMP�̃��[�h
	// �߂�l: TImageInfo *	���ǂݍ��݂Ɏ��s�����ꍇ��NULL��Ԃ�
	// ���� : const char *pszFName	�t�@�C����
	//==========================================
	TImageInfo * LoadBMP(const char *pszFName)
	{
		TImageInfo * pBmp;		// BMP�p�\���̂̃|�C���^
		//********************************************************************
		//	������BMP�̓ǂݍ��ݏ������L�q



		FILE * pf = fopen(pszFName, "rb");	// �t�@�C�����I�[�v��
		if (pf == NULL) return NULL;			// �t�@�C���̃I�[�v���Ɏ��s�����ꍇ�A�������I�����Ċ֐�����E�o����

		pBmp = LoadBMPFromFilePointer(pf);	// BMP����ǂݍ��ށB�����Ń��������m�ۂ����B���̐擪�A�h���X���󂯎��

		fclose(pf);							// �t�@�C�����N���[�Y

		return pBmp;
	}


	//==========================================
	// �֐� : LoadBMPFromFilePointer
	// �ړI : �󂯎�����t�@�C���|�C���^������BMP�t�@�C���̃��[�h
	// �߂�l: TImageInfo *	���ǂݍ��݂Ɏ��s�����ꍇ��NULL��Ԃ�
	// ���� : FILE * pf	�t�@�C���|�C���^
	//==========================================
	TImageInfo * LoadBMPFromFilePointer(FILE * pf)
	{
		TImageInfo * pBmp;				// BMP�p�\���̂̃|�C���^
		int nWidth;						// �������󂯎��p
		int nHeight;					// �c�����󂯎��p
		unsigned short wBitCount;		// �r�b�g�����󂯎��p
		unsigned long dwCompression;	// ���k���󂯎��p
		bool nResult;					// �������ʎ󂯎��p

		nResult = LoadHeader(pf);
		if (nResult == false) return NULL;		// �t�@�C���w�b�_���̓ǂݍ��݂Ɏ��s�����ꍇ�A�������I�����Ċ֐�����E�o����

		// ���w�b�_���̓ǂݍ��݂��s���A�����E�c���E�r�b�g���E���k���@�̃f�[�^���󂯎��
		nResult = LoadInfo(pf, &nWidth, &nHeight, &wBitCount, &dwCompression);

		if (nResult == false) return NULL;		// ���w�b�_���̓ǂݍ��݂Ɏ��s�����ꍇ�A�������I�����Ċ֐�����E�o����

		pBmp = (TImageInfo *)malloc(sizeof(TImageInfo));	// TImageInfo�^�ϐ��𓮓I�m�ۂ���
		pBmp->nWidth = nWidth;							// ��قǎ擾������������������
		pBmp->nHeight = nHeight;						// ��قǎ擾�����c������������
		pBmp->pbyPixels = NULL;							// �s�N�Z����������|�C���^��NULL�ŏ��������Ă���

		if (wBitCount != 24)	// 24bit�`���łȂ������ꍇ
		{
			pBmp->bEffective = false;	// �Ή��ł��Ȃ��`���ł��邽�߁A�t���O��܂��Ċ֐�����E�o����
			return pBmp;
		}
		if (dwCompression != 0)	// ���k����Ă���ꍇ
		{
			pBmp->bEffective = false;	// �Ή��ł��Ȃ��`���ł��邽�߁A�t���O��܂��Ċ֐�����E�o����
			return pBmp;
		}
		pBmp->bEffective = true;	// �ȏ�̏������N���A�����Ƃ������Ƃ͑Ή��ł���`���ł��邽�߁A�t���O�𗧂ĂĂ���

		pBmp->pbyPixels = LoadRGB(pf, pBmp->nWidth, pBmp->nHeight);	// RGB����ǂݍ���

		if (pBmp->pbyPixels == NULL)	// RGB���̓ǂݍ��݂Ɏ��s�����ꍇ
		{
			free(pBmp);				// TImageInfo�p�Ɋm�ۂ������������������
			return NULL;
		}

		return pBmp;
	}


	//==========================================
	// �֐� : LoadHeader
	// �ړI : BMP�t�@�C���̃t�@�C���w�b�_���̓ǂݍ���
	// �߂�l: bool ����...true, ���s...false
	// ���� : FILE * pf	�t�@�C���|�C���^
	//==========================================
	bool LoadHeader(FILE * pf)
	{
		typedef struct
		{
			unsigned char byB;			// �����R�[�h'B'������͂�
			unsigned char byM;			// �����R�[�h'M'������͂�

			// ����ȉ��̕ϐ��͍���͊֌W�Ȃ��B�t�@�C���ǂݍ��݃T�C�Y�̊֌W�Ő����킹�����Ă��邾�� ********
			unsigned long  dwSize;
			unsigned short wReserved1;
			unsigned short wReserved2;
			unsigned long  dwOffBits;
			// *********************************************************************************************

		} TBMPHeader;

		TBMPHeader header;	// �t�@�C���w�b�_���f�[�^�󂯎��p

		// �t�@�C������t�@�C���w�b�_����ǂݍ��݁A���s�����ꍇ��false��Ԃ��Ċ֐�����E�o����
		if (fread(&header, FILE_HEADER_BYTE, 1, pf) < 1) return false;

		// �t�@�C���̐擪�� BM �Ŏn�܂��Ă��Ȃ����BMP�t�@�C���ł͖�������false��Ԃ��Ċ֐�����E�o����
		if (header.byB != 'B' || header.byM != 'M') return false;

		return true;
	}

	//==========================================
	// �֐� : LoadInfo
	// �ړI : BMP�t�@�C���̏��w�b�_���̓ǂݍ���
	// �߂�l: bool ����...true, ���s...false
	// ���� : FILE * pf	�t�@�C���|�C���^
	//        int * pnWidth  �������i�[�������ϐ��ւ̃A�h���X
	//        int * pnHeight �c�����i�[�������ϐ��ւ̃A�h���X
	//        unsigned short * pwBitCount    �r�b�g�����i�[�������ϐ��ւ̃A�h���X
	//        unsigned long * pdwCompression ���k�����i�[�������ϐ��ւ̃A�h���X
	//==========================================
	bool LoadInfo(FILE * pf, int * pnWidth, int * pnHeight, unsigned short * pwBitCount, unsigned long * pdwCompression)
	{
		typedef struct
		{
			unsigned long  dwSize;
			short          nWidth;
			short          nHeight;
			unsigned short wPlanes;
			unsigned short wBitCount;

		} TBMPCoreHeader;

		typedef struct
		{
			unsigned long  dwSize;
			long           lWidth;
			long           lHeight;
			unsigned short wPlanes;
			unsigned short wBitCount;
			unsigned long  dwCompression;
			unsigned long  dwSizeImage;
			long           lXPixPerMeter;
			long           lYPixPerMeter;
			unsigned long  dwClrUsed;
			unsigned long  dwClrImporant;

		} TBMPInfoHeader;


		unsigned long dwHeaderSize;	// ���w�b�_���̃T�C�Y�i�[�p

		// ���w�b�_���̃T�C�Y����ǂݍ��ށB���s�����ꍇfalse��Ԃ��Ċ֐�����E�o����
		if (fread(&dwHeaderSize, BYTE_OF_INFO_HEADER_SIZE, 1, pf) < 1) return false;

		// ���w�b�_���̃T�C�Y��
		if (dwHeaderSize != SIZE_OF_CORE_HEADER && dwHeaderSize != SIZE_OF_INFO_HEADER) return false;

		// ���w�b�_���̃T�C�Y����ǂݍ��ޑO�̏ꏊ�܂Ńt�@�C���J�[�\����߂��B���s�����ꍇfalse��Ԃ��Ċ֐�����E�o����
		if (fseek(pf, -BYTE_OF_INFO_HEADER_SIZE, SEEK_CUR) != 0) return false;

		if (dwHeaderSize == SIZE_OF_CORE_HEADER)	// ���w�b�_���̃T�C�Y��SIZE_OF_CORE_HEADER�������ꍇ
		{
			//���̃t�@�C���̏��w�b�_���� core_header �`���ŋL�q����Ă���

			TBMPCoreHeader info;	// ���w�b�_���f�[�^�󂯎��p

			// ���w�b�_����ǂݍ��ށB���s�����ꍇ��false��Ԃ��Ċ֐�����E�o����
			if (fread(&info, SIZE_OF_CORE_HEADER, 1, pf) < 1) return false;

			// ����ꂽ�����i�[���ׂ��ꏊ�Ɋi�[����
			*pnWidth = info.nWidth;
			*pnHeight = info.nHeight;
			*pwBitCount = info.wBitCount;
			*pdwCompression = 0;
		}

		if (dwHeaderSize == SIZE_OF_INFO_HEADER)	// ���w�b�_���̃T�C�Y��SIZE_OF_INFO_HEADER�������ꍇ
		{
			//���̃t�@�C���̏��w�b�_���� core_header �`���ŋL�q����Ă���

			TBMPInfoHeader info;	// ���w�b�_���f�[�^�󂯎��p

			// ���w�b�_����ǂݍ��ށB���s�����ꍇ��false��Ԃ��Ċ֐�����E�o����
			if (fread(&info, SIZE_OF_INFO_HEADER, 1, pf) < 1) return false;

			// ����ꂽ�����i�[���ׂ��ꏊ�Ɋi�[����
			*pnWidth = info.lWidth;
			*pnHeight = info.lHeight;
			*pwBitCount = info.wBitCount;
			*pdwCompression = info.dwCompression;
		}


		return true;

	}

	//==========================================
	// �֐� : LoadRGB
	// �ړI : RGB����ǂݍ���
	// �߂�l: unsigned char * RGB��񂪊i�[���ꂽ�������̃A�h���X�B�ǂݍ��݂Ɏ��s�����ꍇNULL��Ԃ�
	// ���� : FILE * pf   �t�@�C���|�C���^
	//        int nWidth  �摜�̉���(�s�N�Z����)
	//        int nHeight �摜�̏c��(�s�N�Z����)
	//==========================================
	unsigned char * LoadRGB(FILE * pf, int nWidth, int nHeight)
	{
		unsigned int nSizeOfRGBDatas = nWidth * nHeight * sizeof(unsigned char)* 3/* R, G, B ���ꂼ��1�o�C�g���ō��v3�o�C�g*/;	// RGB�����i�[���郁�����̃T�C�Y
		unsigned char * pbyRGBDatas = (unsigned char *)malloc(nSizeOfRGBDatas);		// RGB�����i�[���郁�����𓮓I�m�ۂ��A���̐擪�A�h���X��ێ�����
		long lPaddingByte = ComputePaddingByte(nWidth);								// �s�v�ȃf�[�^�̃o�C�g��
		long lColByte = nWidth * 3/* R, G, B ���ꂼ��1�o�C�g���ō��v3�o�C�g*/;	// �摜�̉���񕪂̃f�[�^�̃o�C�g��
		int nColIndex;																// �摜�̉�����ڂ̃f�[�^���������B�܂��A���܂ŉ����񕪓ǂݍ��񂾂��������B

		for (nColIndex = 0; nColIndex<nHeight; ++nColIndex)	// ��1�񂸂摜��RGB����ǂݍ���ł���
		{
			if (fread(pbyRGBDatas + lColByte * nColIndex, lColByte, 1, pf) == 0)	// �摜�̉�1�񕪂�ǂݍ���
			{
				free(pbyRGBDatas);	// �ǂݍ��݂Ɏ��s�����ꍇ��������������ANULL��Ԃ��Ċ֐�����E�o����
				return NULL;
			}

			fseek(pf, lPaddingByte, SEEK_CUR);	// �s�v�ȃf�[�^��ǂݔ�΂�
		}

		BGR_to_RGB(pbyRGBDatas, nWidth * nHeight);

		return pbyRGBDatas;
	}

	//==========================================
	// �֐� : ComputePaddingByte
	// �ړI : �s�v�ȃf�[�^�̃o�C�g�������߂Ă����Ԃ�
	// �߂�l: long �s�v�ȃf�[�^�̃o�C�g��
	// ���� : int nWidth �摜�̉���(�s�N�Z����)
	//==========================================
	long ComputePaddingByte(int nWidth)
	{
		// �摜�f�[�^�̉���񕪂�4�o�C�g�̔{���ɍ��킹���Ă���B
		// �܂�摜�f�[�^�̉�����4�o�C�g�̔{���łȂ��ꍇ��4�o�C�g�̔{���ɂȂ�悤�ɖ����ɕs�v�ȃf�[�^�����������Ă����ԁB
		// �ǂݍ��݂̍ہA�����ǂݔ�΂��K�v������B
		// �����ŁA�����ł͕s�v�ȃf�[�^�����o�C�g�Ȃ̂������߂�B

		long lColByte = nWidth * 3/* R, G, B ���ꂼ��1�o�C�g���ō��v3�o�C�g*/;	// �摜�̉���񕪂̃f�[�^�̃o�C�g��
		long lOverByte = lColByte % 4;	// �摜�̉���񕪂̃f�[�^�̃o�C�g�����A4�o�C�g�̔{����艽�o�C�g������

		if (lOverByte > 0)	// �u4�o�C�g��艽�o�C�g�������v���[���o�C�g�𒴂��Ă���ꍇ
		{
			return 4 - lOverByte;	// 4����u���o�C�g�������v�����Εs�v�ȃf�[�^�̃o�C�g�����Z�o�����
		}

		// ��̏����Ɉ���������Ȃ������Ƃ������Ƃ͕s�v�ȃf�[�^�̓[���o�C�g

		return 0;
	}

	//==========================================
	// �֐� : BGR_to_RGB
	// �ړI : BGR�̏��ɕ���ł���F����RGB�̏��ɕ��בւ���
	// �߂�l: �Ȃ�
	// ���� : unsigned char * pbyRGBDatas RGB��񂪊i�[���ꂽ�������̐擪�A�h���X
	//        unsigned int uPixelNum �摜�̑��s�N�Z����
	//==========================================
	void BGR_to_RGB(unsigned char * pbyRGBDatas, unsigned int uPixelNum)
	{
		// ����BMP�t�@�C���͊e�s�N�Z���̐F���� Blue, Green, Red �̏��ԂɋL�^���Ă���
		// ������OpenGL�̕`��֐��ɓn��RGB���� Red, Green, Blue �̏��łȂ���΂Ȃ�Ȃ�
		// �䂦�ɁA�����ł� BGR �̏�Ԃ��� RGB �̏�Ԃɕϊ����鏈�����s��

		unsigned int uRGBDatasByte = uPixelNum * 3/* R, G, B ���ꂼ��1�o�C�g���ō��v3�o�C�g*/;	// RGB���̃o�C�g��
		unsigned int uPixelIndex;	// ��������s�N�Z��(�z��3��)�̐擪�C���f�b�N�X

		for (uPixelIndex = 0; uPixelIndex < uRGBDatasByte; uPixelIndex += 3)
		{
			unsigned int uTargetIndex = uPixelIndex + 2;	// �l���������鑊��̃C���f�b�N�X�ԍ�

			// Red �� Blue �̈ʒu�����ւ��� ****************************
			unsigned char byWork = pbyRGBDatas[uPixelIndex];
			pbyRGBDatas[uPixelIndex] = pbyRGBDatas[uTargetIndex];
			pbyRGBDatas[uTargetIndex] = byWork;
			// ***********************************************************
		}
	}

}

#pragma warning(pop)