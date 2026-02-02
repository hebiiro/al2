#pragma once

namespace apn
{
	//
	// このクラスはハイブの基本クラスです。
	//
	inline struct hive_base_t
	{
		//
		// このdllのインスタンスハンドルです。
		//
		HINSTANCE instance = nullptr;

		//
		// プラグインウィンドウです。
		//
		HWND plugin_window = nullptr;

		//
		// aviutl2ウィンドウです。
		//
		HWND aviutl2_window = nullptr;

		//
		// コンフィグのファイル名です。
		//
		std::wstring config_file_name;

		//
		// このクラスはaviutl2関連の変数を保持します。
		//
		struct aviutl2_t {
			CONFIG_HANDLE* config = {};
		} aviutl2;

		//
		// コンストラクタです。
		//
		hive_base_t()
		{
			hive_base = this;
		}

		//
		// メッセージボックスを表示します。
		//
		int32_t message_box(const std::wstring& text, HWND hwnd = nullptr, int32_t type = MB_OK | MB_ICONWARNING) {
			if (!hwnd) hwnd = plugin_window;
			return ::MessageBoxW(hwnd, text.c_str(), version_base->information.c_str(), type);
		}
	} *hive_base = {};
}
