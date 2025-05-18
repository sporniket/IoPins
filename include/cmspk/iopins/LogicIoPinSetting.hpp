/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__LOGIC_IO_PIN_SETTING__HPP
#define CMSPK__IOPINS__LOGIC_IO_PIN_SETTING__HPP

namespace cmspk::iopins {
// ================[ CODE BEGINS ]================
/**
 * Setting to decide how to translate between a raw value and a logic value.
 */
enum LogicIoPinSetting {
    /**
     * The logic value is `true` when the raw value is low (`false`).
     */
    ACTIVE_LOW = 0,
    /**
     * The logic value is `true` when the raw value is high (`true`).
     */
    ACTIVE_HIGH
};
// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
