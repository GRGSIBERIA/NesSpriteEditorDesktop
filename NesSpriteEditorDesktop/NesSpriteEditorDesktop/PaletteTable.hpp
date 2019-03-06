#pragma once
#include <Siv3D\Rectangle.hpp>
#include "SingletonProvider.hpp"
#include "Palette.hpp"
#include "DrawableObject.hpp"
#include "FontProvider.hpp"

namespace nes
{
	/**
	* �p���b�g�̃e�[�u���N���X
	*/
	class PaletteTable : public DrawableObject
	{
		friend SingletonProvider<PaletteTable>;
		typedef unsigned int SelectionID;

		std::array<Palette, 4> palettes;
		std::array<s3d::Rect, 4> paletteRects;
		s3d::Size patchSize;

		SelectionID selection;

		PaletteTable() : selection(0), patchSize(s3d::Size(24, 24)), DrawableObject() {}

	public:

		void Draw() override
		{
			for (int i = 0; i < 4; ++i)
			{
				paletteRects[i]
					.setPos(position.x + patchSize.x * (i + 1), position.y)
					.setSize(patchSize)
					.draw(palettes[i].GetCode(i).GetColor());

				FontProvider::GetFont()(i).draw(position.x, position.y, s3d::Palette::Black);

				/*
				Palette��DrawableObject�ɕς��āApalettes[i].draw()�ŌĂяo�����ق���������������Ȃ�
				*/
			}
		}
	};

	/**
	* �p���b�g�̃e�[�u����񋟂���N���X
	*/
	class PaletteTableProvider : public SingletonProvider<PaletteTable> {};
}