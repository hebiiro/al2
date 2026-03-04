#pragma once

namespace apn
{
	//
	// このクラスはアプリケーションの基本クラスです。
	//
	inline struct app_base_t
	{
		//
		// コンストラクタです。
		//
		app_base_t() { app_base = this; }

		virtual BOOL on_initialize_plugin(DWORD version) { return TRUE; }
		virtual BOOL on_uninitialize_plugin() { return TRUE; }
		virtual BOOL on_register_plugin(HOST_APP_TABLE* host) { return TRUE; }
	} *app_base = nullptr;
}
