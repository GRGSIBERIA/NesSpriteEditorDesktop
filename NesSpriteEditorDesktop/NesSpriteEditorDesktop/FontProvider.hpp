#pragma once
#include <memory>
#include <Siv3D\Font.hpp>

namespace nes
{
	class FontProvider {
		static std::shared_ptr<FontProvider> ptr;

		const s3d::Font font;

		FontProvider() : font(16) {}

	public:
		static const s3d::Font& GetFont() 
		{
			if (ptr == nullptr)
				ptr = std::shared_ptr<FontProvider>(new FontProvider());
			return ptr->font;
		}
	};

	std::shared_ptr<FontProvider> FontProvider::ptr = nullptr;
}