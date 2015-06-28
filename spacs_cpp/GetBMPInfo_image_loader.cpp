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
	// 関数 : LoadBMP
	// 目的 : BMPのロード
	// 戻り値: TImageInfo *	※読み込みに失敗した場合はNULLを返す
	// 引数 : const char *pszFName	ファイル名
	//==========================================
	TImageInfo * LoadBMP(const char *pszFName);

	//==========================================
	// 関数 : LoadHeader
	// 目的 : BMPファイルのファイルヘッダ部の読み込み
	// 戻り値: bool 成功...true, 失敗...false
	// 引数 : FILE * pf	ファイルポインタ
	//==========================================
	bool LoadHeader(FILE * pf);

	//==========================================
	// 関数 : LoadInfo
	// 目的 : BMPファイルの情報ヘッダ部の読み込み
	// 戻り値: bool 成功...true, 失敗...false
	// 引数 : FILE * pf	ファイルポインタ
	//        int * pnWidth  横幅を格納したい変数へのアドレス
	//        int * pnHeight 縦幅を格納したい変数へのアドレス
	//        unsigned short * pwBitCount    ビット数を格納したい変数へのアドレス
	//        unsigned long * pdwCompression 圧縮情報を格納したい変数へのアドレス
	//==========================================
	bool LoadInfo(FILE * pf, int * pnWidth, int * pnHeight, unsigned short * pwBitCount, unsigned long * pdwCompression);

	//==========================================
	// 関数 : ComputePaddingByte
	// 目的 : 不要なデータのバイト数を求めてそれを返す
	// 戻り値: long 不要なデータのバイト数
	// 引数 : int nWidth 画像の横幅(ピクセル数)
	//==========================================
	long ComputePaddingByte(int nWidth);

	//==========================================
	// 関数 : BGR_to_RGB
	// 目的 : BGRの順に並んでいる色情報をRGBの順に並べ替える
	// 戻り値: なし
	// 引数 : unsigned char * pbyRGBDatas RGB情報が格納されたメモリの先頭アドレス
	//        unsigned int uPixelNum 画像の総ピクセル数
	//==========================================
	void BGR_to_RGB(unsigned char * pbyRGBDatas, unsigned int uPixelNum);

	//==========================================
	// 関数 : LoadRGB
	// 目的 : RGB情報を読み込む
	// 戻り値: unsigned char * RGB情報が格納されたメモリのアドレス。読み込みに失敗した場合NULLを返す
	// 引数 : FILE * pf   ファイルポインタ
	//        int nWidth  画像の横幅(ピクセル数)
	//        int nHeight 画像の縦幅(ピクセル数)
	//==========================================
	unsigned char * LoadRGB(FILE * pf, int nWidth, int nHeight);

	//==========================================
	// 関数 : LoadBMPFromFilePointer
	// 目的 : 受け取ったファイルポインタが示すBMPファイルのロード
	// 戻り値: TImageInfo	※読み込みに失敗した場合はNULLを返す
	// 引数 : FILE * pf	ファイルポインタ
	//==========================================
	TImageInfo * LoadBMPFromFilePointer(FILE * pf);

	TImageInfo * image_loader::GetBMPInfo(const char * path)
	{
		// BMPを読み込み
		TImageInfo * pImageInfo = LoadBMP(path);

		// BMP読み込めなかった場合のエラー処理
		if (pImageInfo == nullptr)
		{
			return nullptr;
		}

		// BMPファイルの形式に対応していなかった場合のエラー処理
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
	// 関数 : LoadBMP
	// 目的 : BMPのロード
	// 戻り値: TImageInfo *	※読み込みに失敗した場合はNULLを返す
	// 引数 : const char *pszFName	ファイル名
	//==========================================
	TImageInfo * LoadBMP(const char *pszFName)
	{
		TImageInfo * pBmp;		// BMP用構造体のポインタ
		//********************************************************************
		//	ここにBMPの読み込み処理を記述



		FILE * pf = fopen(pszFName, "rb");	// ファイルをオープン
		if (pf == NULL) return NULL;			// ファイルのオープンに失敗した場合、処理を終了して関数から脱出する

		pBmp = LoadBMPFromFilePointer(pf);	// BMP情報を読み込む。内部でメモリが確保される。その先頭アドレスを受け取る

		fclose(pf);							// ファイルをクローズ

		return pBmp;
	}


	//==========================================
	// 関数 : LoadBMPFromFilePointer
	// 目的 : 受け取ったファイルポインタが示すBMPファイルのロード
	// 戻り値: TImageInfo *	※読み込みに失敗した場合はNULLを返す
	// 引数 : FILE * pf	ファイルポインタ
	//==========================================
	TImageInfo * LoadBMPFromFilePointer(FILE * pf)
	{
		TImageInfo * pBmp;				// BMP用構造体のポインタ
		int nWidth;						// 横幅情報受け取り用
		int nHeight;					// 縦幅情報受け取り用
		unsigned short wBitCount;		// ビット数情報受け取り用
		unsigned long dwCompression;	// 圧縮情報受け取り用
		bool nResult;					// 処理結果受け取り用

		nResult = LoadHeader(pf);
		if (nResult == false) return NULL;		// ファイルヘッダ部の読み込みに失敗した場合、処理を終了して関数から脱出する

		// 情報ヘッダ部の読み込みを行い、横幅・縦幅・ビット数・圧縮情報　のデータを受け取る
		nResult = LoadInfo(pf, &nWidth, &nHeight, &wBitCount, &dwCompression);

		if (nResult == false) return NULL;		// 情報ヘッダ部の読み込みに失敗した場合、処理を終了して関数から脱出する

		pBmp = (TImageInfo *)malloc(sizeof(TImageInfo));	// TImageInfo型変数を動的確保する
		pBmp->nWidth = nWidth;							// 先ほど取得した横幅情報を代入する
		pBmp->nHeight = nHeight;						// 先ほど取得した縦幅情報を代入する
		pBmp->pbyPixels = NULL;							// ピクセル情報を入れるポインタはNULLで初期化しておく

		if (wBitCount != 24)	// 24bit形式でなかった場合
		{
			pBmp->bEffective = false;	// 対応できない形式であるため、フラグを折って関数から脱出する
			return pBmp;
		}
		if (dwCompression != 0)	// 圧縮されている場合
		{
			pBmp->bEffective = false;	// 対応できない形式であるため、フラグを折って関数から脱出する
			return pBmp;
		}
		pBmp->bEffective = true;	// 以上の条件をクリアしたということは対応できる形式であるため、フラグを立てておく

		pBmp->pbyPixels = LoadRGB(pf, pBmp->nWidth, pBmp->nHeight);	// RGB情報を読み込む

		if (pBmp->pbyPixels == NULL)	// RGB情報の読み込みに失敗した場合
		{
			free(pBmp);				// TImageInfo用に確保したメモリを解放する
			return NULL;
		}

		return pBmp;
	}


	//==========================================
	// 関数 : LoadHeader
	// 目的 : BMPファイルのファイルヘッダ部の読み込み
	// 戻り値: bool 成功...true, 失敗...false
	// 引数 : FILE * pf	ファイルポインタ
	//==========================================
	bool LoadHeader(FILE * pf)
	{
		typedef struct
		{
			unsigned char byB;			// 文字コード'B'が入るはず
			unsigned char byM;			// 文字コード'M'が入るはず

			// これ以下の変数は今回は関係ない。ファイル読み込みサイズの関係で数合わせをしているだけ ********
			unsigned long  dwSize;
			unsigned short wReserved1;
			unsigned short wReserved2;
			unsigned long  dwOffBits;
			// *********************************************************************************************

		} TBMPHeader;

		TBMPHeader header;	// ファイルヘッダ部データ受け取り用

		// ファイルからファイルヘッダ部を読み込み、失敗した場合はfalseを返して関数から脱出する
		if (fread(&header, FILE_HEADER_BYTE, 1, pf) < 1) return false;

		// ファイルの先頭が BM で始まっていなければBMPファイルでは無いためfalseを返して関数から脱出する
		if (header.byB != 'B' || header.byM != 'M') return false;

		return true;
	}

	//==========================================
	// 関数 : LoadInfo
	// 目的 : BMPファイルの情報ヘッダ部の読み込み
	// 戻り値: bool 成功...true, 失敗...false
	// 引数 : FILE * pf	ファイルポインタ
	//        int * pnWidth  横幅を格納したい変数へのアドレス
	//        int * pnHeight 縦幅を格納したい変数へのアドレス
	//        unsigned short * pwBitCount    ビット数を格納したい変数へのアドレス
	//        unsigned long * pdwCompression 圧縮情報を格納したい変数へのアドレス
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


		unsigned long dwHeaderSize;	// 情報ヘッダ部のサイズ格納用

		// 情報ヘッダ部のサイズ情報を読み込む。失敗した場合falseを返して関数から脱出する
		if (fread(&dwHeaderSize, BYTE_OF_INFO_HEADER_SIZE, 1, pf) < 1) return false;

		// 情報ヘッダ部のサイズが
		if (dwHeaderSize != SIZE_OF_CORE_HEADER && dwHeaderSize != SIZE_OF_INFO_HEADER) return false;

		// 情報ヘッダ部のサイズ情報を読み込む前の場所までファイルカーソルを戻す。失敗した場合falseを返して関数から脱出する
		if (fseek(pf, -BYTE_OF_INFO_HEADER_SIZE, SEEK_CUR) != 0) return false;

		if (dwHeaderSize == SIZE_OF_CORE_HEADER)	// 情報ヘッダ部のサイズがSIZE_OF_CORE_HEADERだった場合
		{
			//このファイルの情報ヘッダ部は core_header 形式で記述されている

			TBMPCoreHeader info;	// 情報ヘッダ部データ受け取り用

			// 情報ヘッダ部を読み込む。失敗した場合はfalseを返して関数から脱出する
			if (fread(&info, SIZE_OF_CORE_HEADER, 1, pf) < 1) return false;

			// 得られた情報を格納すべき場所に格納する
			*pnWidth = info.nWidth;
			*pnHeight = info.nHeight;
			*pwBitCount = info.wBitCount;
			*pdwCompression = 0;
		}

		if (dwHeaderSize == SIZE_OF_INFO_HEADER)	// 情報ヘッダ部のサイズがSIZE_OF_INFO_HEADERだった場合
		{
			//このファイルの情報ヘッダ部は core_header 形式で記述されている

			TBMPInfoHeader info;	// 情報ヘッダ部データ受け取り用

			// 情報ヘッダ部を読み込む。失敗した場合はfalseを返して関数から脱出する
			if (fread(&info, SIZE_OF_INFO_HEADER, 1, pf) < 1) return false;

			// 得られた情報を格納すべき場所に格納する
			*pnWidth = info.lWidth;
			*pnHeight = info.lHeight;
			*pwBitCount = info.wBitCount;
			*pdwCompression = info.dwCompression;
		}


		return true;

	}

	//==========================================
	// 関数 : LoadRGB
	// 目的 : RGB情報を読み込む
	// 戻り値: unsigned char * RGB情報が格納されたメモリのアドレス。読み込みに失敗した場合NULLを返す
	// 引数 : FILE * pf   ファイルポインタ
	//        int nWidth  画像の横幅(ピクセル数)
	//        int nHeight 画像の縦幅(ピクセル数)
	//==========================================
	unsigned char * LoadRGB(FILE * pf, int nWidth, int nHeight)
	{
		unsigned int nSizeOfRGBDatas = nWidth * nHeight * sizeof(unsigned char)* 3/* R, G, B それぞれ1バイトずつで合計3バイト*/;	// RGB情報を格納するメモリのサイズ
		unsigned char * pbyRGBDatas = (unsigned char *)malloc(nSizeOfRGBDatas);		// RGB情報を格納するメモリを動的確保し、その先頭アドレスを保持する
		long lPaddingByte = ComputePaddingByte(nWidth);								// 不要なデータのバイト数
		long lColByte = nWidth * 3/* R, G, B それぞれ1バイトずつで合計3バイト*/;	// 画像の横一列分のデータのバイト数
		int nColIndex;																// 画像の横何列目のデータかを示す。また、今まで横何列分読み込んだかも示す。

		for (nColIndex = 0; nColIndex<nHeight; ++nColIndex)	// 横1列ずつ画像のRGB情報を読み込んでいく
		{
			if (fread(pbyRGBDatas + lColByte * nColIndex, lColByte, 1, pf) == 0)	// 画像の横1列分を読み込む
			{
				free(pbyRGBDatas);	// 読み込みに失敗した場合メモリを解放し、NULLを返して関数から脱出する
				return NULL;
			}

			fseek(pf, lPaddingByte, SEEK_CUR);	// 不要なデータを読み飛ばす
		}

		BGR_to_RGB(pbyRGBDatas, nWidth * nHeight);

		return pbyRGBDatas;
	}

	//==========================================
	// 関数 : ComputePaddingByte
	// 目的 : 不要なデータのバイト数を求めてそれを返す
	// 戻り値: long 不要なデータのバイト数
	// 引数 : int nWidth 画像の横幅(ピクセル数)
	//==========================================
	long ComputePaddingByte(int nWidth)
	{
		// 画像データの横一列分は4バイトの倍数に合わせられている。
		// つまり画像データの横幅が4バイトの倍数でない場合は4バイトの倍数になるように末尾に不要なデータがくっつけられている状態。
		// 読み込みの際、それを読み飛ばす必要がある。
		// そこで、ここでは不要なデータが何バイトなのかを求める。

		long lColByte = nWidth * 3/* R, G, B それぞれ1バイトずつで合計3バイト*/;	// 画像の横一列分のデータのバイト数
		long lOverByte = lColByte % 4;	// 画像の横一列分のデータのバイト数が、4バイトの倍数より何バイト多いか

		if (lOverByte > 0)	// 「4バイトより何バイト多いか」がゼロバイトを超えている場合
		{
			return 4 - lOverByte;	// 4から「何バイト多いか」引けば不要なデータのバイト数が算出される
		}

		// 上の条件に引っかからなかったということは不要なデータはゼロバイト

		return 0;
	}

	//==========================================
	// 関数 : BGR_to_RGB
	// 目的 : BGRの順に並んでいる色情報をRGBの順に並べ替える
	// 戻り値: なし
	// 引数 : unsigned char * pbyRGBDatas RGB情報が格納されたメモリの先頭アドレス
	//        unsigned int uPixelNum 画像の総ピクセル数
	//==========================================
	void BGR_to_RGB(unsigned char * pbyRGBDatas, unsigned int uPixelNum)
	{
		// 実はBMPファイルは各ピクセルの色情報を Blue, Green, Red の順番に記録している
		// しかしOpenGLの描画関数に渡すRGB情報は Red, Green, Blue の順でなければならない
		// ゆえに、ここでは BGR の状態から RGB の状態に変換する処理を行う

		unsigned int uRGBDatasByte = uPixelNum * 3/* R, G, B それぞれ1バイトずつで合計3バイト*/;	// RGB情報のバイト数
		unsigned int uPixelIndex;	// 処理するピクセル(配列3つ分)の先頭インデックス

		for (uPixelIndex = 0; uPixelIndex < uRGBDatasByte; uPixelIndex += 3)
		{
			unsigned int uTargetIndex = uPixelIndex + 2;	// 値を交換する相手のインデックス番号

			// Red と Blue の位置を入れ替える ****************************
			unsigned char byWork = pbyRGBDatas[uPixelIndex];
			pbyRGBDatas[uPixelIndex] = pbyRGBDatas[uTargetIndex];
			pbyRGBDatas[uTargetIndex] = byWork;
			// ***********************************************************
		}
	}

}

#pragma warning(pop)