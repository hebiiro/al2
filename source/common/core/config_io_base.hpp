#pragma once

namespace apn
{
	//
	// このクラスはコンフィグ入出力の基本クラスです。
	//
	inline struct config_io_base_t : json_config_io_t
	{
		//
		// コンストラクタです。
		//
		config_io_base_t()
		{
			config_io_base = this;
		}
	} *config_io_base = {};
}
