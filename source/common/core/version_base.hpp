#pragma once

namespace apn
{
	//
	// このクラスはバージョンの基本クラスです。
	//
	inline struct version_base_t
	{
		//
		// プラグイン名とプラグイン情報です。
		//
		const std::wstring raw_name;
		const std::wstring raw_information;
		const std::wstring raw_revision;

		//
		// コンストラクタです。
		//
		version_base_t(const std::wstring& raw_name, const std::wstring& raw_information, const std::wstring& raw_revision)
			: raw_name(raw_name), raw_information(raw_information), raw_revision(raw_revision)
		{
			version_base = this;
		}

		//
		// 翻訳済みのプラグイン名を返します。
		//
		inline std::wstring get_name() const { return tr(raw_name); }

		//
		// 翻訳済みのプラグイン情報を返します。
		//
		inline std::wstring get_information() const { return tr(raw_information) + raw_revision; }
	} *version_base = {};
}
