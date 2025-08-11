/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__HPP
#define CMSPK__IOPINS__HPP
// ================[ CODE BEGINS ]================
// ...your includes...

// ...your code...

/**
 * `com.sporniket` namespace.
 */
namespace cmspk {};

/**
 * An abstraction layer for I/O pins of micro-controllers.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
namespace cmspk::iopins {};

#include "cmspk/iopins/InputPin.hpp"
#include "cmspk/iopins/InputPinGroup.hpp"
#include "cmspk/iopins/IoDirection.hpp"
#include "cmspk/iopins/IoFailureReason.hpp"
#include "cmspk/iopins/LogicInputPin.hpp"
#include "cmspk/iopins/LogicIoPinSetting.hpp"
#include "cmspk/iopins/LogicOutputPin.hpp"
#include "cmspk/iopins/OutputPin.hpp"
#include "cmspk/iopins/OutputPinGroup.hpp"
// ================[ END OF CODE ]================
#endif
