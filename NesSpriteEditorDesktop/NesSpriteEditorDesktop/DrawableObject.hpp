#pragma once
#include <Siv3D\Vector2D.hpp>
#include <Siv3D\Point.hpp>

namespace nes
{
	/**
	* 描画抽象クラス
	*/
	class DrawableObject
	{
	protected:
		s3d::Point position;

	public:
		DrawableObject(const s3d::Point& position = s3d::Point()) : position(position) {}

		virtual void Draw() = 0;

		/**
		* 座標を指定
		*/
		void SetPos(const s3d::Point& pos) { position = pos; }
	};
}