#pragma once
#include <Siv3D.hpp>

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
			static const std::array<s3d::Color, 0x3F> ColorMap = {
				s3d::Color(U"#BCBCBC"),
				s3d::Color(U"#0073EF"),
				s3d::Color(U"#233BEF"),
				s3d::Color(U"#8300F3"),
				s3d::Color(U"#BF00BF"),
				s3d::Color(U"#E7005B"),
				s3d::Color(U"#DB2B00"),
				s3d::Color(U"#CB4F0F"),
				s3d::Color(U"#8B7300"),
				s3d::Color(U"#009700"),
				s3d::Color(U"#00AB00"),
				s3d::Color(U"#00933B"),
				s3d::Color(U"#00838B"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#FFFFFF"),
				s3d::Color(U"#3FBFFF"),
				s3d::Color(U"#5F73FF"),
				s3d::Color(U"#A78BFD"),
				s3d::Color(U"#F77BFF"),
				s3d::Color(U"#FF77B7"),
				s3d::Color(U"#FF7763"),
				s3d::Color(U"#FF9B3B"),
				s3d::Color(U"#F3BF3F"),
				s3d::Color(U"#83D313"),
				s3d::Color(U"#4FDF4B"),
				s3d::Color(U"#58F898"),
				s3d::Color(U"#00EBDB"),
				s3d::Color(U"#757575"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#FFFFFF"),
				s3d::Color(U"#ABE7FF"),
				s3d::Color(U"#C7D7FF"),
				s3d::Color(U"#D7CBFF"),
				s3d::Color(U"#FFC7FF"),
				s3d::Color(U"#FFC7DB"),
				s3d::Color(U"#FFBFB3"),
				s3d::Color(U"#FFDBAB"),
				s3d::Color(U"#FFE7A3"),
				s3d::Color(U"#E3FFA3"),
				s3d::Color(U"#ABF3BF"),
				s3d::Color(U"#B3FFCF"),
				s3d::Color(U"#9FFFF3"),
				s3d::Color(U"#BCBCBC"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000")
			};

			return ColorMap[paletteCode];
		}
	};

	
}