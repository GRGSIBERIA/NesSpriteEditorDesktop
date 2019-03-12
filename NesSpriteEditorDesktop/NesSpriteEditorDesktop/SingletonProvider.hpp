#pragma once
#include <memory>

namespace nes
{
	// �V���O���g���N���X�̃C���^�[�t�F�[�X
	template <class T>
	class SingletonProvider
	{
		static std::shared_ptr<T> ptr;	//!< �V���O���g���̃C���X�^���X

	public:

		/**
		* �C���X�^���X���擾
		* @return �V���O���g���̃C���X�^���X
		*/
		static T& GetInstance()
		{
			if (ptr.get() == nullptr)
				ptr = std::shared_ptr<T>(new T());
			return *(ptr.get());
		}
	};

	template <class T>
	std::shared_ptr<T> SingletonProvider<T>::ptr = nullptr;
}