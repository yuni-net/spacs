#include <manager.h>
#include <key.h>

bool spa::manager::init(int * argc, char ** argv)
{
	return spa::manager::instance().init_(argc, argv);
}

bool spa::manager::ok()		// Do call it before process of each frame
{
	return spa::manager::instance().ok_();
}

void spa::manager::clear()	// Clearing screen data
{
	spa::manager::instance().clear_();
}

void spa::manager::show()		// Screen will be updated
{
	spa::manager::instance().show_();
}





spa::manager & spa::manager::instance()
{
	static spa::manager spamanager;
	return spamanager;
}

GLFWwindow * spa::manager::window()
{
	return instance().window_;
}

spa::manager::~manager()
{
	alutExit();
	glfwTerminate();
}

bool spa::manager::init_(int * argc, char ** argv)
{
	const int windowW = 640;
	const int windowH = 480;

	window_ = nullptr;

	if (glfwInit() == GL_FALSE)
	{
		return false;
	}

	window_ = glfwCreateWindow(windowW, windowH, "OpenGL Window", NULL, NULL);
	if (window_ == NULL)
	{
		return false;
	}

	glfwMakeContextCurrent(window_);
	glfwSwapInterval(1);	// ‚’¼“¯ŠúM†‚ğ1‰ñ‘Ò‚Âİ’è‚É‚·‚é

	// •`‰æ”ÍˆÍ‚Ìw’è
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, windowW, 0.0f, windowH, -1.0f, 1.0f);

	alutInit(argc, argv);


	return true;
}

bool spa::manager::ok_()
{
	glfwPollEvents();
	key::singleton().renew();
	return glfwWindowShouldClose(window_) == 0;
}

void spa::manager::clear_()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void spa::manager::show_()
{
	glfwSwapBuffers(window_);
}
