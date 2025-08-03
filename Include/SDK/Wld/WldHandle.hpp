#pragma once

#include "../Util.hpp"

namespace wld {

template <typename T>
class Handle : public util::Handle<T> {
};

} // namespace wld