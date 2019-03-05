#pragma once
#include <Siv3D\Color.hpp>

namespace nes
{
	class IndexOutOfRangeException : public std::exception {};

	typedef unsigned char PCode;	// ���l�̃p���b�g�R�[�h�^

	/*
	* �p���b�g�R�[�h
	*/
	class PaletteCode
	{
		PCode code;			// �F�ԍ�
		s3d::Color color;	// ���ۂ̐F

	public:
		// �R���X�g���N�^ ---------------------------------------------------

		// @param paletteCode �F�R�[�h
		PaletteCode(const PCode paletteCode)
			: code((PCode)paletteCode), color(GetColor((PCode)paletteCode)) {}

		// �f�t�H���g�R���X�g���N�^
		PaletteCode() : code(0), color(GetColor(0)){}

		// �I�y���[�^ ---------------------------------------------------

		PaletteCode& operator=(const PaletteCode& rhs) { code = rhs.code; color = rhs.color; }

		// �A�N�Z�T ---------------------------------------------------

		const PCode GetCode() const { return code; }

		const s3d::Color& GetColor() const { return color; }

		// �֐��Ȃ� ---------------------------------------------------
		
		/**
		* �F�ԍ��ɏ]�������ۂ̐F���擾����֐�
		*/
		static const s3d::Color& GetColor(const PCode paletteCode)
		{
			static const std::array<s3d::Color, 0x40> ColorMap = {
				s3d::Color(U"#787878"),
				s3d::Color(U"#2000B0"),
				s3d::Color(U"#2800B8"),
				s3d::Color(U"#6010A0"),
				s3d::Color(U"#982078"),
				s3d::Color(U"#B01030"),
				s3d::Color(U"#A03000"),
				s3d::Color(U"#784000"),
				s3d::Color(U"#485800"),
				s3d::Color(U"#386800"),
				s3d::Color(U"#386C00"),
				s3d::Color(U"#306040"),
				s3d::Color(U"#305080"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#B0B0B0"),
				s3d::Color(U"#4060F8"),
				s3d::Color(U"#4040FF"),
				s3d::Color(U"#9040F0"),
				s3d::Color(U"#D840C0"),
				s3d::Color(U"#D84060"),
				s3d::Color(U"#E05000"),
				s3d::Color(U"#C07000"),
				s3d::Color(U"#888800"),
				s3d::Color(U"#50A000"),
				s3d::Color(U"#48A810"),
				s3d::Color(U"#48A068"),
				s3d::Color(U"#4090C0"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#FFFFFF"),
				s3d::Color(U"#60A0FF"),
				s3d::Color(U"#5080FF"),
				s3d::Color(U"#A070FF"),
				s3d::Color(U"#F060FF"),
				s3d::Color(U"#FF60B0"),
				s3d::Color(U"#FF7830"),
				s3d::Color(U"#FFA000"),
				s3d::Color(U"#E8D020"),
				s3d::Color(U"#98E800"),
				s3d::Color(U"#70F040"),
				s3d::Color(U"#70E090"),
				s3d::Color(U"#60D0E0"),
				s3d::Color(U"#787878"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#FFFFFF"),
				s3d::Color(U"#90D0FF"),
				s3d::Color(U"#A0B8FF"),
				s3d::Color(U"#C0B0FF"),
				s3d::Color(U"#E0B0FF"),
				s3d::Color(U"#FFB8E8"),
				s3d::Color(U"#FFC8B8"),
				s3d::Color(U"#FFD8A0"),
				s3d::Color(U"#FFF090"),
				s3d::Color(U"#C8F080"),
				s3d::Color(U"#A0F0A0"),
				s3d::Color(U"#A0FFC8"),
				s3d::Color(U"#A0FFF0"),
				s3d::Color(U"#A0A0A0"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000")
			};

			return ColorMap[paletteCode];
		}
	};

	
}