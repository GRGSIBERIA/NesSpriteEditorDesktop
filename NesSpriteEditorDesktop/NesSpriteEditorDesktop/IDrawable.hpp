#pragma once
#include <Siv3D\Vector2D.hpp>

namespace nes
{
	/**
	* 描画インターフェース
	*/
	class IDrawable
	{
	public:
		virtual void Draw(const s3d::Point& position) = 0;
	};
}