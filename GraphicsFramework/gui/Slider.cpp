#include "Slider.h"

namespace GF {
	template<>
	void Slider<GF::Circle>::CircleSlider(float size, const sf::Vector2f pos, const Orientation o, const double mmax, const double mmin) {
		orientation = o;
		slider.setup(7 * SW, pos, sf::Color(150, 150, 150), sf::Color::White, 1);
		size *= SW;

		if (orientation == GF::HORIZONTAL)
		{
			line = GF::Line(sf::Vector2f(pos.x - size / 2, pos.y), sf::Vector2f(pos.x + size / 2, pos.y));
			box = GF::Rectangle(sf::Vector2f(size, 40 * SH), pos, CENTERED);
		}
		if (orientation == GF::VERTICAL)
		{
			line = GF::Line(sf::Vector2f(pos.x, pos.y - size / 2), sf::Vector2f(pos.x, pos.y + size / 2));
			box = GF::Rectangle(sf::Vector2f(40 * SW, size), pos, CENTERED);
		}
		max = mmax;
		min = mmin;
	}

	template<>
	void Slider<GF::Rectangle>::RectSlider(sf::Vector2f size, const sf::Vector2f pos, const Orientation o, const double mmax, const double mmin) {
		orientation = o;
		max = mmax;
		min = mmin;

		size.x *= SW;
		size.y *= SH;

		box = GF::Rectangle(size, pos, CENTERED, sf::Color::Transparent, sf::Color::White, 1);

		static const float side = 10.f * SW;

		if (orientation == GF::HORIZONTAL)
		{
			slider.setup(sf::Vector2f(side, size.y), pos, sf::Vector2f(side / 2, size.y / 2), sf::Color::White, sf::Color::Transparent, 0);
		}
		if (orientation == GF::VERTICAL)
		{
			slider.setup(sf::Vector2f(size.x, side), pos, sf::Vector2f(size.x / 2, side / 2), sf::Color::White, sf::Color::Transparent, 0);
		}
	}

	template<>
	bool Slider<GF::Circle>::draw()
	{
		m_target->draw(line);
		m_target->draw(slider);
		return true;
	}
	template<>
	bool Slider<GF::Rectangle>::draw()
	{
		m_target->draw(slider);
		m_target->draw(box);
		return true;
	}

	template<>
	GF::Slider<GF::Circle>* GF::Slider<GF::Circle>::makeRandom(sf::RenderTarget * renderer) {
		return new GF::Slider<>(
			(float)Rand.getU(50 * SW, SCREENWIDTH / 2.f),
			sf::Vector2f(Rand.getU(SCREENWIDTH / 4.f, SCREENWIDTH * 3.f / 4.f), Rand.getU(SCREENHEIGHT / 4.f, SCREENHEIGHT * 3.f / 4.f)),
			(GF::Orientation)Rand.getU(0, 1),
			Rand.getI(50, 100),
			Rand(0, 50),
			renderer);
	}
	template<>
	GF::Slider<GF::Rectangle> * GF::Slider<GF::Rectangle>::makeRandom(sf::RenderTarget * renderer) {
		unsigned o = Rand.getU(0, 1);
		if (o == 0)
			return new GF::Slider<GF::Rectangle>(
				sf::Vector2f(Rand.getU(10 * SW, 50 * SW), Rand.getU(20 * SH, SCREENHEIGHT / 2)),
				sf::Vector2f(Rand.getU(SCREENWIDTH / 4.f, SCREENWIDTH * 3.f / 4.f), Rand.getU(SCREENHEIGHT / 4.f, SCREENHEIGHT * 3.f / 4.f)),
				GF::Orientation::VERTICAL,
				Rand.getI(50, 100),
				Rand(0, 50),
				renderer);
		else
			return new GF::Slider<GF::Rectangle>(
				sf::Vector2f(Rand.getU(20 * SW, SCREENWIDTH / 2), Rand.getU(10 * SH, 50 * SH)),
				sf::Vector2f(Rand.getU(SCREENWIDTH / 4.f, SCREENWIDTH * 3.f / 4.f), Rand.getU(SCREENHEIGHT / 4.f, SCREENHEIGHT * 3.f / 4.f)),
				GF::Orientation::HORIZONTAL,
				Rand.getI(50, 100),
				Rand(0, 50),
				renderer);
	}
}