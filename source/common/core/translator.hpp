#pragma once

namespace apn
{
	//
	// このクラスは翻訳を担当します。
	//
	inline struct translator_t
	{
		//
		// 翻訳必要なaviutl2の変数です。
		//
		CONFIG_HANDLE* config = {};

		//
		// 指定された文字列を翻訳して返します。
		//
		inline LPCWSTR operator()(const std::wstring& text)
		{
			return config->translate(config, text.c_str());
		}

		//
		// 指定された文字列を翻訳して返します。
		//
		inline LPCWSTR operator()(const std::wstring& section, const std::wstring& text)
		{
			return config->get_language_text(config, section.c_str(), text.c_str());
		}
	} tr;
}
