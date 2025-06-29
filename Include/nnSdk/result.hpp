#pragma once

#include "Types.hpp"

namespace nn {

class Result {
public:
    bool isSuccess() { return m_innerValue == 0; }
    bool isCancelled() { return m_innerValue == 671; }

private:
    s32 m_innerValue;

};

}