#include <sound.h>

namespace spa
{
	bool sound::load(const char * path)
	{
		release();
		::spa::sound_data * soundd = new ::spa::sound_data();
		bool result = soundd->load(path);
		this->soundd = soundd;
		ownership = true;
		gen();

		return result;
	}
//	bool sound::load(const std::string & path){ return load(path.c_str()); }

	void sound::sound_data(const ::spa::sound_data & soundd)
	{
		release();
		this->soundd = &soundd;
		gen();
	}

	void sound::play()
	{
		alSourcei(source, AL_LOOPING, AL_FALSE);
		alSourcePlay(source);
	}
	void sound::play(bool LoopFlag){ loop(); }

	void sound::loop()
	{
		alSourcei(source, AL_LOOPING, AL_TRUE);
		alSourcePlay(source);
	}

	void sound::stop()
	{
		alSourceStop(source);
	}
	void sound::pause()
	{
		alSourcePause(source);
	}

	void sound::reset()
	{
		stop();
	}
	void sound::replay()
	{
		play();
	}
	void sound::reloop()
	{
		loop();
	}
	void sound::replay(bool LoopFlag){ reloop(); }



	sound::sound()
	{
		soundd = nullptr;
		ownership = false;
		source = 0;	// this has to be invalid value as source-name. Probably zero is invalid value.
	}
	sound::~sound()
	{
		release();
	}

	void sound::gen()
	{
		alGenSources(1, &source);
		soundd->gen(source);
	}

	void sound::release()
	{
		if (source != 0)
		{
			if (alIsSource(source) == AL_TRUE)
			{
				alDeleteSources(1, &source);
			}
		}

		if (ownership == true)
		{
			delete soundd;
		}

		soundd = nullptr;
		ownership = false;
	}

}