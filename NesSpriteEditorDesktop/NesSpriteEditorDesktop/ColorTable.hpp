#pragma once
#include <Siv3D.hpp>
#include "IDrawable.hpp"
#include "PaletteCode.hpp"
#include "SingletonProvider.hpp"

namespace nes
{
	/// �V���O���g���̂��߂̃v���g�^�C�v�錾
	class ColorTableProvider;

	/**
	* �F�̃e�[�u���N���X
	*/
	class ColorTable : public IDrawable
	{
		friend SingletonProvider<ColorTable>;

		s3d::Size patchSize;
		std::array<Rect, 0x40> paletteRects;

		// �R���X�g���N�^ ---------------------------------------------------

		ColorTable(const s3d::Size& patchSize = s3d::Size(24, 24)) : patchSize(patchSize)
		{
			for (PCode i = 0; i < 4; ++i)
			{
				for (PCode j = 0; j < 16; ++j)
				{
					const PCode index = (i << 4) | j;
					paletteRects[index] = Rect(patchSize);
				}
			}
		}

	public:

		// ���\�b�h ---------------------------------------------------

		void Draw(const s3d::Point& position) override
		{
			for (PCode i = 0; i < 4; ++i)
			{
				for (PCode j = 0; j < 16; ++j)
				{
					const PCode index = (i << 4) | j;
					const auto& color = PaletteCode::GetColor(index);
					auto& palette = paletteRects[index];

					palette
						.setPos(Point(patchSize.x * j, patchSize.y * i) + Point(position))
						.draw(color)
						.drawFrame(1, Palette::Gray);

					if (palette.leftClicked())
					{
						// �I�𒆂̃p���b�g�ɑ΂��ă��b�Z�[�W��ʒm
						Logger << U"Message: leftClicked -> palette" << index;
					}
				}
			}
		}
	};

	/**
	* �F�̃e�[�u����񋟂���N���X
	*/
	class ColorTableProvider : public SingletonProvider<ColorTable>	{};
}