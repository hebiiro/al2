#pragma once

namespace apn
{
	//
	// このクラスはコンフィグダイアログの基本クラスです。
	//
	inline struct config_dialog_base_t : my::Dialog, my::lockable_t
	{
		//
		// このダイアログが表示されている場合はTRUEになります。
		//
		BOOL flag_show = FALSE;

		//
		// このダイアログが表示されている座標です。
		//
		POINT show_pos = {};

		//
		// コンストラクタです。
		//
		config_dialog_base_t()
		{
			config_dialog_base = this;
		}

		virtual BOOL on_to_ui() { return TRUE; }
		virtual BOOL on_from_ui() { return TRUE; }
		virtual void on_command(UINT code, UINT control_id, HWND control) {}
		virtual void on_notify(NMHDR* nmhdr) {}

		//
		// 初期化処理を実行します。
		//
		BOOL init(UINT idd)
		{
			MY_TRACE_FUNC("");

			{
				// 初期化中にエディットボックスがコマンドを発行してしまうので、
				// それを防ぐためにロックしておきます。
				my::locker_t locker(this);

				if (!__super::create(hive_base->instance, MAKEINTRESOURCE(idd), hive_base->aviutl2_window))
				{
					hive_base->message_box(L"コンフィグダイアログの作成に失敗しました");

					return FALSE;
				}
			}

			return TRUE;
		}

		//
		// 後始末処理を実行します。
		//
		BOOL exit()
		{
			MY_TRACE_FUNC("");

			return __super::destroy();
		}

		//
		// コンフィグでコントロールを更新します。
		//
		BOOL to_ui()
		{
			MY_TRACE_FUNC("");

			if (is_locked()) return FALSE;

			my::locker_t locker(this);

			return on_to_ui();
		}

		//
		// コントロールでコンフィグを更新します。
		//
		BOOL from_ui()
		{
			MY_TRACE_FUNC("");

			if (is_locked()) return FALSE;

			return on_from_ui();
		}

		//
		// 表示状態をノードから読み込みます。
		//
		void read_node(const n_json& node)
		{
			read_bool(node, "flag_show", flag_show);
			read_point(node, "show_pos", show_pos);

			auto flags = SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE;
			if (flag_show) flags |= SWP_SHOWWINDOW;

			::SetWindowPos(*this, nullptr,
				show_pos.x, show_pos.y, 0, 0, flags);
		}

		//
		// 表示状態をノードから読み込みます。
		//
		void read_node(const n_json& node, const std::string& name)
		{
			return read_node(read_child(node, name));
		}

		//
		// 表示状態をノードに書き込みます。
		//
		void write_node(n_json& node)
		{
			write_bool(node, "flag_show", flag_show);
			write_point(node, "show_pos", show_pos);
		}

		//
		// 表示状態をノードに書き込みます。
		//
		void write_node(n_json& node, const std::string& name)
		{
			return write_node(node[name]);
		}

		//
		// ウィンドウプロシージャです。
		//
		virtual LRESULT on_wnd_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) override
		{
			switch (message)
			{
			case WM_CREATE:
				{
					// このウィンドウをプラグインウィンドウに設定します。
					hive_base->plugin_window = hwnd;

					break;
				}
			case WM_DESTROY:
				{
					// ウィンドウ終了時にコンフィグをファイルに書き込みます。
					config_io_base->write();

					break;
				}
			case WM_INITDIALOG:
				{
					// 翻訳されたダイアログ名をセットします。
					::SetWindowTextW(hwnd, tr(version_base->name));

					// スコープ終了時(デフォルト処理の後)に実行します。
					my::scope_exit scope_exit([&]()
					{
						// 子ウィンドウを列挙します。
						::EnumChildWindows(hwnd, [](HWND child, LPARAM l_param) -> BOOL
						{
							// 子ウィンドウを翻訳します。
							::SetWindowTextW(child, tr(my::get_window_text(child)));

							return TRUE;
						},
						0);
					});

					return __super::on_wnd_proc(hwnd, message, w_param, l_param);
				}
			case WM_COMMAND:
				{
					// ロックされている場合はWM_COMMANDを処理しません。
					if (is_locked()) break;

					auto code = HIWORD(w_param);
					auto control_id = LOWORD(w_param);
					auto control = (HWND)l_param;

					// 派生クラスにWM_COMMANDを処理させます。
					on_command(code, control_id, control);

					break;
				}
			case WM_NOTIFY:
				{
					auto nmhdr = (NMHDR*)l_param;

					// 派生クラスにWM_NOTIFYを処理させます。
					on_notify(nmhdr);

					break;
				}
			case WM_SHOWWINDOW:
				{
					// ダイアログの表示状態を取得しておきます。
					flag_show = !!w_param;

					break;
				}
			case WM_WINDOWPOSCHANGED:
				{
					auto wp = (WINDOWPOS*)l_param;

					if (!(wp->flags & SWP_NOMOVE))
					{
						// ダイアログの表示座標を取得しておきます。
						show_pos.x = wp->x;
						show_pos.y = wp->y;
					}

					break;
				}
			}

			return __super::on_wnd_proc(hwnd, message, w_param, l_param);
		}
	} *config_dialog_base = {};
}
