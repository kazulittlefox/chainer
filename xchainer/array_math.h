#pragma once

#include "xchainer/array.h"

namespace xchainer {

void Add(const Array& lhs, const Array& rhs, Array& out);
void Mul(const Array& lhs, const Array& rhs, Array& out);

}  // namespace xchainer
