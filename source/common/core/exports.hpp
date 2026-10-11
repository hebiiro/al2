#pragma once

namespace apn
{
	//
	// エントリポイントです。
	//
	EXTERN_C BOOL APIENTRY DllMain(HMODULE instance, DWORD reason, LPVOID reserved)
	{
		switch (reason)
		{
		case DLL_PROCESS_ATTACH:
			{
				::DisableThreadLibraryCalls(hive_base->instance = instance);

				// このdllがアンロードされないようにします。
				// こうした方が安全ですが、
				// aviutl2からアンインストールできなくなるのでコメントアウトしています。
//				::LoadLibrary(my::get_module_file_name(instance).c_str());

				break;
			}
		case DLL_PROCESS_DETACH:
			{
				break;
			}
		}

		return TRUE;
	}

	//
	// 対応バージョンを返します。
	//
	EXTERN_C DWORD RequiredVersion()
	{
		return 2003000;
	}

	//
	// ロガー初期化関数です。
	//
	EXTERN_C void InitializeLogger(LOG_HANDLE* handle)
	{
		// ログハンドルを取得します。
		logger.handle = handle;
	}

	//
	// コンフィグ初期化関数です。
	//
	EXTERN_C void InitializeConfig(CONFIG_HANDLE* config)
	{
		// コンフィグハンドルを取得します。
		tr.config = config;

		// このタイミングでコアライブラリを初期化します。

		// プラグイン名をセットします。
//		hive_base->plugin_name = version_base->get_name();
		hive_base->plugin_name = version_base->get_information();

		// カレントスレッドのウィンドウを列挙します。
		::EnumThreadWindows(::GetCurrentThreadId(), [](HWND hwnd, LPARAM l_param)
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
	// プラグイン初期化関数です。
	//
	EXTERN_C bool InitializePlugin(DWORD version)
	{
		return !!app_base->on_initialize_plugin(version);
	}

	//
	// プラグイン終了関数です。
	//
	EXTERN_C void UninitializePlugin()
	{
		return (void)app_base->on_uninitialize_plugin();
	}

	//
	// 汎用プラグイン情報を登録します。
	//
	EXTERN_C void RegisterPlugin(HOST_APP_TABLE* host)
	{
		// 編集ハンドルを取得します。
		editor.handle = host->create_edit_handle();

		// プラグインの情報を設定します。
		host->set_plugin_information(version_base->get_information().c_str());

		return (void)app_base->on_register_plugin(host);
	}

	//
	// 入力プラグインの構造体を返します。
	//
	EXTERN_C INPUT_PLUGIN_TABLE* GetInputPluginTable()
	{
		// 入力プラグインの構造体を自動的に構築します。
		static input_plugin_table_t input_plugin_table;

		return &input_plugin_table;
	}
}
