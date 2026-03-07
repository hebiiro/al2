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
	// aviutl2のコンフィグを取得します。
	//
	EXTERN_C void InitializeConfig(CONFIG_HANDLE* config)
	{
		// コアライブラリを初期化します。
		init_core_lib(config);
	}

	//
	// プラグイン初期化関数です。
	//
	EXTERN_C bool InitializePlugin(DWORD version)
	{
		if (version < 2003000) return false;

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
		// プラグインの情報を設定します。
		host->set_plugin_information(version_base->get_name().c_str());

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
