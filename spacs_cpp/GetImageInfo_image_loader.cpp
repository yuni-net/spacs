#include "image_loader.h"

namespace spa
{
	TImageInfo * image_loader::GetImageInfo(const char * path)
	{
		// todo　拡張子によって適切なファイル解析関数を呼ぶ実装にすること。開いてみて違った場合、全通り試す。
		return GetBMPInfo(path);	// 暫定的にBMPファイルで決め打ち
	}
}