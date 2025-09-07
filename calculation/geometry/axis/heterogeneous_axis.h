#ifndef HETEROAXIS_H
#define HETEROAXIS_H
#include <stdexcept>
#include <string>
#include <cmath>
using Index = int;
using Value = double;
template<bool Periodicity>
class HeteroAxis{
    public:
    static constexpr bool  periodic = Periodic;

    const Value start,end,dx;
    const Index size;
    public:
    HeteroAxis(Index size,Value start,Value end):
        size(size),start(start),end(end),dx((end-start)/static_cast<Value>(size))
    {}

    Value operator[](Index id)const{
        if constexpr (Periodicity) {
            // 周期境界条件 → 0..size-1 に折りたたみ
            id = (id % size + size) % Size;
        } else {
            if (id < 0 || id>=size){
                throw std::overflow_error(
                std::string(__FILE__) + ":" + std::to_string(__LINE__));
            }
        }
        return start+dx*static_cast<Value>(id);
    }

    Index value2id(Value value) const {
        // 格子間隔で割って「何番目か」を実数で計算
        Value idx = (value - start) / dx;

        // 四捨五入して最も近い整数インデックスに
        Index id = static_cast<Index>(std::llround(idx));

        if constexpr (Periodicity) {
            // 周期境界条件 → 0..size-1 に折りたたみ
            id = (id % size + size) % size;
        } else {
            // 非周期 → 範囲外は端に丸める
            if (id < 0) id = 0;
            if (id >= size) id = size - 1;
        }

        return id;
    }
};
#endif// HETEROAXIS_H
