# (1) コンパイラ
CC       = g++
CXXFLAGS = -Wall -O2 -std=c++17

# (2) ディレクトリ
SRC_DIR  = .
OBJ_DIR  = obj

# (3) 実行ファイル
TARGET   = app

# (4) ソースファイル
SRCS     = main.cpp \
           developer.cpp \
           developer_Lax-Wendroff.cpp \
           vlasov_simulator.cpp \
           utils/Timer.cpp

# (5) オブジェクトファイル（元の階層を維持してobj以下に出力）
OBJS     = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# (6) オブジェクト用ディレクトリをすべて作成（重複を除く）
DIRS     = $(sort $(dir $(OBJS)))

# デフォルトターゲット
all: $(DIRS) $(TARGET)

# objディレクトリ階層の作成
$(DIRS):
	mkdir -p $@

# リンク
$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^

# オブジェクトファイル生成ルール
$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

# クリーン
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
