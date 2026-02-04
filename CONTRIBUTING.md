## 設定

* `al2.props`の`origin_dir`でインクルードの基点となるフォルダを指定してください。
* `al2.props`の`aviutl2_dir`で出力フォルダを指定してください。
* `al2.props`の`aviutl2_plugin_ext`で出力拡張子を指定してください。

```xml
    <aviutl2_dir>ここをaviutl2.exeがあるフォルダのパスに書き換えます</aviutl2_dir>
```

## サブモジュール

1. 開発環境のメニューから`表示`➡`ターミナル`を選択します。
1. `開発者用PowerShell`ウィンドウが開きます。
1. そこで以下のコマンドを実行します。
```
git submodule add https://github.com/hebiiro/my common/my
git submodule add https://github.com/hebiiro/sprintfmt common/sprintfmt
git submodule add https://github.com/oov/aviutl2_plugin_sdk common/aviutl2_plugin_sdk
git submodule add https://github.com/hebiiro/al2_slimming
git submodule add https://github.com/hebiiro/al2_ui_dressing
```

---

1. または、クローンするときに`--recursive`オプションを指定します。
```
git clone --recursive https://github.com/hebiiro/al2
```

### サブモジュールの更新

```
git submodule update --remote
```

## 開発環境

* Windows 11 Home
* Visual Studio Community 2022

## プロジェクトの設定

* x64
* UNICODE文字セット

## 外部ライブラリ

* AviUtl ExEdit2 Plugin SDK `root\source\common\aviutl2_plugin_sdk`
* detours `root\source\common\detours`
* JSON for Modern C++ `root\source\common\nlohmann`

## 内部ライブラリ

* 汎用ライブラリ `root\source\common\my`
* 書式化ライブラリ `root\source\common\sprintfmt`

## 絵文字

* 🎉初版に使用します。
* 🔖バージョン(リビジョン)に付与します。
* 🩹問題に対応したときに使用します。
* 以下は機能や仕様を変更したときに使用します。
	* 💥大規模
	* ♻️小規模
* 以下は機能を追加したときに使用します。
	* 🚀大規模
	* ✨中規模
	* ⚡️小規模
* 🔥機能を削除したときに使用します。
* 🎨UIなどの見た目を変更したときに使用します。
* 📝ドキュメントを変更したときに使用します。
* 🚚フォルダ構造を変えたときに使用します。
* ⬆️サブモジュールの更新を反映したときに使用します。
* 📦️使用パッケージを更新したときに使用します。
* 🔀マージしたときに使用します。

## コーディングパターン

* スネークケースで記述します。
* 定数には`c_`を付けます。
* `class`、`private`、`protected`、`public`は可能な限り使用しないようにします。
* `bool`、`true`、`false`はなるべく使用しないようにします。
* コンストラクタ、デストラクタ、例外処理はなるべく使用しないようにします。
* 初期化と後始末が必要なクラスにはinit()とexit()を定義します。
* `case`の本体が複数行なら`{}`で囲みます。
* `{`はなるべく次の行に書きます。
* `/**/`はなるべく使用しないようにします。
* クラス、関数、変数のコメントは次のように書きます。
ただし、`この関数は`と`この変数は`は省略します。(数が多すぎるので)
```
	//
	// このクラスは〇〇です。
	//
```
* 処理に対するコメントは次のように書きます。
* `win32`や`C++`が分からなくても、そこで何をすればいいのかが分かるのがベストです。
```
	// メッセージボックスを表示します。
	::MessageBoxW(nullptr, L"hoge", L"foo", MB_OK | MB_ICONWARNING);
```
* ソースファイルの拡張子は`cpp`にします。
* ヘッダーファイルの拡張子は`hpp`にします。
* プロジェクトには必ず`main.def`、`main.cpp`を作成します。
* ソースファイルは可能な限り`main.cpp`のみにします。
* ヘッダーファイルでは他のファイルをインクルードしないようにします。
* `main.cpp`で必要なすべてのヘッダーファイルをインクルードするようにします。

## プロジェクトの主な構造

* `hive_t` データを保持します。プロジェクト全体から参照されます。
* `hook_manager_t` フックを管理します。
* `addin_window_t` aviutlプラグインウィンドウのように振る舞います。
* `addin_dialog_t` アドインウィンドウにコントロールを配置するための子ウィンドウです。
* `config_io_t` プロジェクト全体の設定を読み込み・保存します。ほぼプロジェクト全体を参照します。
* `app_t` インターフェイスを実装し、他のクラスから相互参照されます。
* `addin_t` プロジェクト全体を参照する。他のクラスからは参照されることはありません。
* 依存関係は次のようになることが多いです。
`addin_t`->`app_t`->`config_io_t`->`その他のクラス`->`hive_t`

## コンフィグファイル

* コンフィグファイルが存在しない場合が初期値になるようにします。
* ファイル形式はなるべく`json`にします。
