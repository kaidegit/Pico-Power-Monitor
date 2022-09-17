//
// Created by yekai on 2022/9/17.
//

#ifndef PICO_POWER_MONITOR_FILTER_H
#define PICO_POWER_MONITOR_FILTER_H

#include <cstdint>

class Filter {
public:
    Filter(int32_t _weight_n = 7, int32_t _weight_p = 2, int32_t _weight_pp = 1,
           int32_t _data_p = 5, int32_t _data_pp = 5) :
            weight_n(_weight_n), weight_p(_weight_p), weight_pp(_weight_pp),
            data_p(_data_p), data_pp(_data_pp) {};

    int32_t out_10x(int32_t data) {
        auto ret = weight_n * data + weight_p * data_p + weight_pp * data_pp;
        data_pp = data_p;
        data_p = data;
        return ret;
    }

private:
    int32_t weight_n, weight_p, weight_pp;
    int32_t data_p, data_pp;
};

#endif //PICO_POWER_MONITOR_FILTER_H
