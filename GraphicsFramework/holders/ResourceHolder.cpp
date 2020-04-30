#include "ResourceHolder.h"

namespace GF {

	ResourceHolder& ResourceHolder::get()
	{
		static ResourceHolder holder;
		return holder;
	}

	ResourceHolder::ResourceHolder()
		: fonts("fonts", "ttf")
		, textures("txrs", "png")
		, soundBuffers("sfx", "ogg")
	{

	}
}
