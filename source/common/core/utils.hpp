#pragma once

namespace apn
{
	//
	// コアライブラリを初期化します。
	//
	inline BOOL init_core_lib(CONFIG_HANDLE* config)
	{
		tr.config = config;
//		hive_base->plugin_name = version_base->get_name();
		hive_base->plugin_name = version_base->get_information();

		// カレントスレッドのウィンドウを列挙します。
		return ::EnumThreadWindows(::GetCurrentThreadId(), [](HWND hwnd, LPARAM l_param)
		{
			// クラス名を取得します。
			auto class_name = my::get_class_name(hwnd);
			MY_TRACE_STR(class_name);

			// クラス名が一致しない場合は除外します。
			if (class_name != L"aviutl2Manager") return TRUE;

			// トップレベルウィンドウではない場合は除外します。
			if (::GetWindow(hwnd, GW_OWNER)) return TRUE;

			// aviutl2ウィンドウをセットします。
			hive_base->aviutl2_window = hwnd;

			// 列挙を終了します。
			return FALSE;
		}, 0);
	}

	//
	// よく使うファイルパスを管理します。
	//
	struct base_path_t
	{
		//
		// 基準となるパスです。
		//
		std::filesystem::path path;

		//
		// 基準となるフォルダのパスです。
		//
		std::filesystem::path dir;

		//
		// アセットフォルダのパスです。
		//
		std::filesystem::path assets_dir;

		//
		// コンフィグフォルダのパスです。
		//
		std::filesystem::path config_dir;

		//
		// コンストラクタです。
		//
		base_path_t()
		{
			// 基準となるパスを取得します。
			path = my::get_module_file_name(hive_base->instance);

			// 基準となるフォルダのパスを取得します。
			dir = path, dir.replace_extension();

			// アセットフォルダのパスを取得します。
			assets_dir = dir  / L"assets";

			// コンフィグフォルダのパスを取得します。
			config_dir = dir  / L"config";
		}
	};
}
