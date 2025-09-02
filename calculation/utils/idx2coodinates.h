#ifndef IDX2COODINATES_H
#define IDX2COODINATES_H

class Idx2Value{
    //シミュレーション空間のインデックスを座標に変換する in Cartesian coordinate system
    using Value = double;
    using Index = int;
    const Index num_of_grid;
    const Value grid_size;

    const Value start_value;

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
};

class Value2Idx{
    //シミュレーション空間のインデックスを座標に変換する in Cartesian coordinate system
    using Value = double;
    using Index = int;
    const Index num_of_grid;
    const Value grid_size;

    const Value start_value;

    Value2Idx(
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
};



#endif