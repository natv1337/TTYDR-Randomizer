#pragma once

#include "Types.hpp"

typedef u32 Result;

// namespace nn {

// class Result {
// public:
//     bool isSuccess() { return m_innerValue == 0; }

//     /**
//      * @brief 
//      *   I'm unsure if this "cancelled" value applies to all cancel operations, but this does specficially apply
//      *   to the software keyboard's cancel operation.
//      * 
//      * @return
//      *   True if the prompt is cancelled.
//      */
//     bool isCancelled() { return m_innerValue == 671; }

//     bool fileDoesNotExit() { return m_innerValue == 0x202; }

// private:
//     s32 m_innerValue;

// };

// } // namespace nn