# Boost.log動作確認メモ
- ここではboost.logのローテート設定、open,closeのハンドルなどを調査したので、ソースを格納します。

- 参照ソース
    - https://github.com/termoshtt/boost_log_sample

## 調査内容
    1. ログファイル設定方法
    2. フィルターの設定
    3. open/close ハンドリング
    4. ローテート設定(インターバル設定,サイズ、ファイル数、ファイル名の命名方法)
    5. その他諸々


```
# ファイル配置
tree ./*
./README.md 
./build
./src
├── CMakeLists.txt
└── set_filter.cpp
```

- ビルド方法
```
cd cpp_boost;
mkdir build;
cd build;
cmake ../src;
make;
```

