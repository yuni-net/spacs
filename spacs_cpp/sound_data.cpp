#include <sound_data.h>

namespace spa
{
	bool sound_data::load(const char * path)
	{
		release();
		buffer = alutCreateBufferFromFile(path);
		return alIsBuffer(buffer) == AL_TRUE;
	}
//	bool sound_data::load(const std::string & path){ return load(path.c_str()); }

	sound_data::sound_data()
	{
		buffer = 0;	// this has to be invalid value as buffer-name. Probably zero is invalid value.
	}

	void sound_data::gen(GLuint source) const
	{
		alSourcei(source, AL_BUFFER, buffer);
	}

	void sound_data::release()
	{
		if (buffer != 0)
		{
			if (alIsBuffer(buffer) == AL_TRUE)
			{
				alDeleteBuffers(1, &buffer);
			}
		}
	}

	sound_data::~sound_data()
	{
		release();
	}
}