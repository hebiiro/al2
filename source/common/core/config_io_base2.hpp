#pragma once

namespace apn
{
	//
	// このクラスはコンフィグ入出力の基本クラスです。
	//
	struct config_io_base2_t : config_io_base_t
	{
		//
		// 更新処理を実行します。
		//
		virtual BOOL update() override
		{
			MY_TRACE_FUNC("");

			return config_dialog_base->to_ui();
		}

		//
		// ノードからコンフィグを読み込みます。
		//
		virtual BOOL read_node(n_json& root) override
		{
			MY_TRACE_FUNC("");

			config_dialog_base->read_node(root, "config_dialog");

			return TRUE;
		}

		//
		// ノードにコンフィグを書き込みます。
		//
		virtual BOOL write_node(n_json& root) override
		{
			MY_TRACE_FUNC("");

			config_dialog_base->write_node(root, "config_dialog");

			return TRUE;
		}
	};
}
