#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"
#include "../holders/NonCopyable.h"
#include "../holders/NonMoveable.h"

namespace GF {

	class ResourceHolder : public NonCopyable, public NonMovable
	{
	public:
		static ResourceHolder& get();

		ResourceManager<sf::Font>           fonts;
		ResourceManager<sf::Texture>        textures;
		ResourceManager<sf::SoundBuffer>    soundBuffers;

	private:
		ResourceHolder();
	};
}
