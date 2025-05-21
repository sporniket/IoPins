/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for input pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__INPUT_PIN__HPP
#define CMSPK__IOPINS__INPUT_PIN__HPP
#include <cstdint>
#include <expected>

#include "cmspk/iopins/IoFailureReason.hpp"
namespace cmspk::iopins {
// ================[ CODE BEGINS ]================
/**
 * An abstraction of input pins, with a value represented by the given type.
 *
 * @param S storage type for the value, typically a `bool` or an `uint8_t`
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
template <typename S>
class InputPin {
  public:
    ~InputPin() noexcept {}

    /**
     * Fully define an input pin.
     *
     * @param id the native identification number of the pin.
     */
    InputPin(uint8_t id) noexcept : id(id) {}

    /**
     * Predicate about the readability of the pin.
     *
     * @returns `true`, always.
     */
    bool isReadable() const noexcept { return true; }

    /**
     * Predicate about the readability of the pin.
     *
     * @returns `false`, always.
     */
    bool isNotReadable() const noexcept { return false; }

    /**
     * Predicate about the writability of the pin.
     *
     * @returns `false`, always.
     */
    bool isWritable() const noexcept { return false; }

    /**
     * Predicate about the writability of the pin.
     *
     * @returns `true`, always.
     */
    bool isNotWritable() const noexcept { return true; }

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

    /**
     * Read operation, the pin MUST have `READ` direction to be able to succeed.
     *
     * @returns the result of the read operation.
     */
    std::expected<S, IoFailureReason> read() noexcept { return doRead(); }

  private:
    /**
     * Extension point to implement for the actual read operation.
     *
     * @returns the result of the read operation.
     */
    virtual std::expected<S, IoFailureReason> doRead() noexcept = 0;

  private:
    uint8_t id;
};

/**
 * Specialization of input pins using a single bit (`bool`) to represent its values.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using BinaryInputPin = InputPin<bool>;

/**
 * Specialization of input pins using an 8 bits wide integer (`uint8_t`) to represent its values.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using AnalogInputPin8 = InputPin<uint8_t>;

/**
 * Specialization of input pins using a 16 bits wide integer (`uint16_t`) to represent its values.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using AnalogInputPin16 = InputPin<uint16_t>;

/**
 * Specialization of input pins using a 32 bits wide integer (`uint32_t`) to represent its values.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using AnalogInputPin32 = InputPin<uint32_t>;
// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
