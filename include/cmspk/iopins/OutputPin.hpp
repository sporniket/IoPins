/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for output pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__OUTPUT_PIN__HPP
#define CMSPK__IOPINS__OUTPUT_PIN__HPP
// standard includes
#include <cstdint>
#include <expected>

// dependencies includes
#include "cmspk/ucdev.hpp"

// project includes
#include "cmspk/iopins/IoFailureReason.hpp"
#include "cmspk/ucdev/OutputValueDevice.hpp"
namespace cmspk::iopins {
// ================[ CODE BEGINS ]================
/**
 * An abstraction of output pins, with a value represented by the given type.
 *
 * This base output pin has a fixed direction and cannot be reconfigured.
 *
 * @param S storage type for the value, typically a `bool` or an `uint8_t`
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
template <typename S>
class OutputPin : public cmspk::ucdev::OutputValueDevice<S, IoFailureReason> {
  public:
    ~OutputPin() noexcept {}

    /**
     * Fully define an output pin.
     *
     * @param id the native identification number of the pin.
     */
    OutputPin(uint8_t id) noexcept : id(id) {}

    /**
     * Predicate about the readability of the pin.
     *
     * @returns `false`, always.
     */
    bool isReadable() const noexcept { return false; }

    /**
     * Predicate about the readability of the pin.
     *
     * @returns `true`, always.
     */
    bool isNotReadable() const noexcept { return true; }

    /**
     * Predicate about the writability of the pin.
     *
     * @returns `true`, always.
     */
    bool isWritable() const noexcept { return true; }

    /**
     * Predicate about the writability of the pin.
     *
     * @returns `false`, always.
     */
    bool isNotWritable() const noexcept { return false; }

    /**
     * Predicate about the enabling of the pin.
     *
     * @returns `true`, always.
     */
    bool isEnabled() const noexcept { return true; }

    /**
     * Predicate about the enabling of the pin.
     *
     * @returns `false`, always.
     */
    bool isDisabled() const noexcept { return false; }

    /**
     * Get the pin id for the underlying microcontroller/board, usually a 1-based index value.
     */
    uint8_t getPinId() const noexcept { return id; }

  private:
    uint8_t id;
};

/**
 * Specialization of output pins using a single bit (`bool`) to represent its values.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using BinaryOutputPin = OutputPin<bool>;

/**
 * Specialization of output pins using an 8 bits wide integer (`uint8_t`) to represent its values.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using AnalogOutputPin8 = OutputPin<uint8_t>;

/**
 * Specialization of output pins using a 16 bits wide integer (`uint16_t`) to represent its values.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using AnalogOutputPin16 = OutputPin<uint16_t>;

/**
 * Specialization of output pins using a 32 bits wide integer (`uint32_t`) to represent its values.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using AnalogOutputPin32 = OutputPin<uint32_t>;
// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
