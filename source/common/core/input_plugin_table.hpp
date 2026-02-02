#pragma once

namespace apn
{
	//
	// このクラスは入力プラグインの構造体です。
	//
	struct input_plugin_table_t : INPUT_PLUGIN_TABLE
	{
		//
		// 翻訳されたプラグイン名です。
		//
		const std::wstring name = tr(version_base->name);

		//
		// 翻訳されたプラグイン情報です。
		//
		const std::wstring information = my::format(L"{/}{/}",
			tr(version_base->information), version_base->revision);

		//
		// コンストラクタです。
		//
		input_plugin_table_t()
		{
			__super::name = name.c_str();
			__super::information = information.c_str();
			__super::flag = 0;
			__super::filefilter = L"\0";
			__super::func_config = [](HWND hwnd, HINSTANCE dll_hinst) -> bool
			{
				::ShowWindow(hive_base->plugin_window, SW_SHOW);
				return true;
			};
		}
	};
}
