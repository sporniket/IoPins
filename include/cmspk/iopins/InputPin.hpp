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

// standard includes
#include <cstdint>
#include <expected>

// dependencies includes
#include "cmspk/ucdev.hpp"

// project includes
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
class InputPin : public cmspk::ucdev::InputValueDevice<S, IoFailureReason>, public cmspk::ucdev::SimpleReadableDeviceAssertions {
  public:
    ~InputPin() noexcept {}

    /**
     * Fully define an input pin.
     *
     * @param id the native identification number of the pin.
     */
    InputPin(uint8_t id) noexcept : id(id) {}

    /**
     * Get the pin id for the underlying microcontroller/board.
     */
    uint8_t getPinId() const noexcept { return id; }

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
