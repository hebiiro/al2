#pragma once

namespace apn
{
	//
	// このクラスはロギングを担当します。
	//
	inline struct logger_t
	{
		//
		// ロギングに必要なaviutl2の変数です。
		//
		LOG_HANDLE* handle = {};

		void log_format(auto... args) { return handle->log(handle, my::format(args...).c_str()); }
		void info_format(auto... args) { return handle->info(handle, my::format(args...).c_str()); }
		void warn_format(auto... args) { return handle->warn(handle, my::format(args...).c_str()); }
		void error_format(auto... args) { return handle->error(handle, my::format(args...).c_str()); }
		void verbose_format(auto... args) { return handle->verbose(handle, my::format(args...).c_str()); }
	} logger;
}
