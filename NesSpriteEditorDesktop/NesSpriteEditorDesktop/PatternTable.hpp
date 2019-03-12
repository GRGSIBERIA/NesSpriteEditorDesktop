#pragma once
#include "DrawableObject.hpp"
#include "SingletonProvider.hpp"

namespace nes
{
	/**
	* キャラクターを格納するためのテーブル
	* 256個格納できる
	*/
	class PatternTable : public DrawableObject
	{
		

	public:
		PatternTable() : DrawableObject() {}

		void Draw() override
		{

		}

		void Update() override
		{

		}
	};

	class BGPatternTable : public PatternTable
	{
		friend SingletonProvider<BGPatternTable>;
	};

	class SpritePatternTable : public PatternTable
	{
		friend SingletonProvider<SpritePatternTable>;
	};

	class BGPatternProvider : public SingletonProvider<BGPatternTable> {};

	class SpritePatternProvider : public SingletonProvider<SpritePatternTable> {};
}