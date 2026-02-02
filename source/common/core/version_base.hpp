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
		const std::wstring name;
		const std::wstring information;
		const std::wstring revision;

		//
		// コンストラクタです。
		//
		version_base_t(const std::wstring& name, const std::wstring& information, const std::wstring& revision)
			: name(name), information(information), revision(revision)
		{
			version_base = this;
		}
	} *version_base = {};
}
