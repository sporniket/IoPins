/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__IO_DIRECTION__HPP
#define CMSPK__IOPINS__IO_DIRECTION__HPP
namespace cmspk::iopins {
// ================[ CODE BEGINS ]================

/**
 * Encoding of I/O pin direction.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
enum IoDirection {
    /**
     * Pin is enabled for reading.
     */
    READ = 0,
    /**
     * Pin is enabled for writing.
     */
    WRITE,
    /**
     * Pin is disabled.
     */
    HIGH_Z
};
// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
