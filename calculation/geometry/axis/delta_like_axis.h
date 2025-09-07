#ifndef DELTA_LIKE_AXIS_H
#define DELTA_LIKE_AXIS_H

class DeltaLikeAxis{
    using Value = double;
    using Index = int;

    private:
    const Value place_of_peak;
    public:
    DeltaLikeAxis(Value place_of_peak):
        place_of_peak(place_of_peak)
    {}
};
#endif// DELTA_LIKE_AXIS_H