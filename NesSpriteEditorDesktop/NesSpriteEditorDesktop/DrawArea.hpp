#pragma once
#include <Siv3D\Rectangle.hpp>
#include "SingletonProvider.hpp"
#include "DrawableObject.hpp"
#include "Character.hpp"

namespace nes
{
	class DrawArea : public DrawableObject
	{
		friend SingletonProvider<DrawArea>;

		Character character;

	public:
		DrawArea() : character(true), DrawableObject() 
		{
			character.SetPos(position);
		}

		void Draw() override
		{
			// 描画エリアの描画
			character.Draw();
		}

		void Update() override
		{
			character.Update();
		}

		DrawableObject& SetPos(const s3d::Point& pos) override 
		{ 
			position = pos;
			character.SetPos(pos);
			return *this; 
		}
	};

	class DrawAreaProvider : public SingletonProvider<DrawArea> {};
}