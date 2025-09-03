#ifndef IDX2COODINATES_H
#define IDX2COODINATES_H
#include <cmath>

class Idx2Value{
    //シミュレーション空間のインデックスを座標に変換する in Cartesian coordinate system
    private:
    using Value = double;
    using Index = int;
    const Index num_of_grid;
    const Value grid_size;
    const Value start_value;

    public:
    Idx2Value(
        Index num_of_grid,
        Value grid_size,
        Value start_value
    ):
    num_of_grid(num_of_grid),
    grid_size(grid_size),
    start_value(start_value)
    {}

    Value get_value_roll(Index index)const{
        index %= num_of_grid;
        return start_value+grid_size*index;
    }

    Value get_value(Index index)const{
        return start_value+grid_size*index;
    }

    Idx2Value(Idx2Value&)=delete;
    Idx2Value(Idx2Value&&)=delete;
};

class Value2Idx{
    //シミュレーション空間のインデックスを座標に変換する in Cartesian coordinate system
    using Value = double;
    using Index = int;
    private:
    const Index num_of_grid;
    const Value grid_size;

    const Value start_value;

    public:
    Value2Idx(
        Index num_of_grid,
        Value grid_size,
        Value start_value
    ):
    num_of_grid(num_of_grid),
    grid_size(grid_size),
    start_value(start_value)
    {}

    // 非周期
    Index get_index(Value value) const {
        return static_cast<Index>(std::floor((value - start_value) / grid_size));
    }

    // 周期境界
    Index get_index_roll(Value value) const {
        Index idx = static_cast<Index>(std::floor((value - start_value) / grid_size));
        idx %= num_of_grid;
        if (idx < 0) idx += num_of_grid;
        return idx;
    }

    Value2Idx(Value2Idx&)=delete;
    Value2Idx(Value2Idx&&)=delete;

};



#endif