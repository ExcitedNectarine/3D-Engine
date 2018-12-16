#pragma once

namespace ENG
{
	class ShaderProgram;

	class Drawable
	{
	public:
		virtual void draw(ShaderProgram& shader) {}
	};
}