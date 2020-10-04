# Boost.log動作確認メモ
- ここではboost.logのローテート設定、open,closeのハンドルなどを調査したので、ソースを格納します。

```
# ファイル配置
tree ./*
./README.md 
./build
./src
├── CMakeLists.txt
└── set_filter.cpp
```



- 参照元
    - https://github.com/termoshtt/boost_log_sample

- ビルド方法
```
cd cpp_boost;
mkdir build;
cd build;
cmake ../src;
make;
```

