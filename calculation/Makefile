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
            developer_muscl.cpp \
            vlasov_simulator.cpp
OBJS     = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# デフォルトターゲット
all: $(TARGET)

# リンク
$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^

# オブジェクトファイルの生成ルール
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

# お掃除
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
