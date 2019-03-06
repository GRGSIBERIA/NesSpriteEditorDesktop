#pragma once
#include <memory>

namespace nes
{
	// シングルトンクラスのインターフェース
	template <class T>
	class SingletonProvider
	{
		static std::shared_ptr<T> ptr;	//!< シングルトンのインスタンス

	public:

		/**
		* インスタンスを取得
		* @return シングルトンのインスタンス
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