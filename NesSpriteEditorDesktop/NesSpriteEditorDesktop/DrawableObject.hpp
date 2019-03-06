#pragma once
#include <Siv3D\Vector2D.hpp>
#include <Siv3D\Point.hpp>

namespace nes
{
	/**
	* �`�撊�ۃN���X
	*/
	class DrawableObject
	{
	protected:
		s3d::Point position;

	public:
		DrawableObject(const s3d::Point& position = s3d::Point()) : position(position) {}

		virtual void Draw() = 0;

		/**
		* ���W���w��
		*/
		void SetPos(const s3d::Point& pos) { position = pos; }
	};
}