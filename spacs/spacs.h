#pragma once

#include "manager.h"
#include "image_data.h"
#include "image.h"
#include "sound.h"
#include "key.h"

#ifndef LIB_DEBUG
#ifdef _DEBUG
#pragma comment(lib, "spacsd.lib")
#else
#pragma comment(lib, "spacs.lib")
#endif
#endif