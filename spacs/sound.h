#pragma once


#include <sound_data.h>

namespace spa
{
	class sound
	{
	public:
		bool load(const char * path);
	//	bool load(const std::string & path);

		void sound_data(const ::spa::sound_data & soundd);

		void play();
		void play(bool LoopFlag);

		void loop();

		void stop();
		void pause();

		void reset();
		void replay();
		void reloop();
		void replay(bool LoopFlag);



		sound();
		~sound();
	private:
		const ::spa::sound_data * soundd;
		bool ownership;
		GLuint source;

		void gen();
		void release();
	};
}