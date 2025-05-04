/* SPDX-License-Identifier: GPL-3.0-or-later */
/****************************************

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
****************************************/
#ifndef CMSPK__IOPINS__IO_FAILURE_REASON__HPP
#define CMSPK__IOPINS__IO_FAILURE_REASON__HPP

#include <expected>

namespace cmspk::iopins {
// ================[ CODE BEGINS ]================

/**
 * Encoding of failure reasons for I/O pin operations.
 */
enum IoFailureReason {
    /**
     * Undefined reason.
     */
    FAILURE = 0,
    FAILURE_PIN_IS_DISABLED,
    FAILURE_PIN_IS_NOT_WRITABLE,
    FAILURE_PIN_IS_NOT_READABLE,
    FAILURE_IMMUTABLE_DIRECTION
    // etc...
};

// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
