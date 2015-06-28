#pragma once

namespace spa
{
	struct TImageInfo
	{
		int nWidth;					// 画像の横幅(ピクセル数)をここに格納してください
		int nHeight;				// 画像の縦幅(ピクセル数)をここに格納してください。マイナス値を格納すると、RGB情報が上から下に向かって格納されていると判断されます
		unsigned char * pbyPixels;	// RGB情報を格納するメモリ領域をmallocで確保し、その先頭アドレスをここに格納してください
		/*
		 * R,G,Bはそれぞれ1バイトです
		 * R→G→B→R→G→B→R…となるようにデータを格納してください
		 * 気を使って2次元配列にする必要はありません
		 */
		bool bEffective;			// true...対応可能ファイル形式　false...対応不可ファイル形式
	};
}