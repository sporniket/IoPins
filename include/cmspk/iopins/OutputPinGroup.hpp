/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for input pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__OUTPUT_PIN_GROUP__HPP
#define CMSPK__IOPINS__OUTPUT_PIN_GROUP__HPP

// standard includes
#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <expected>

// dependencies includes
#include "cmspk/ucdev.hpp"

// project includes
#include "cmspk/iopins/IoFailureReason.hpp"
#include "cmspk/ucdev/ReadWriteAssertions.hpp"
namespace cmspk::iopins {
// ================[ CODE BEGINS ]================
/**
 * An abstraction of a group of digital (true/false) input pins of a given size, that is read all at once.
 *
 * @param N the size of the group.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
template <std::size_t N>
class OutputPinGroup : public cmspk::ucdev::OutputValueDevice<std::bitset<N>, IoFailureReason>, public cmspk::ucdev::SimpleWritableDeviceAssertions {
  public:
    ~OutputPinGroup() noexcept {}

    /**
     * Fully define an input pin.
     *
     * @param ids the N native identification numbers of the pins.
     */
    OutputPinGroup(std::array<uint8_t, N> ids) noexcept : ids(ids) {}

    /**
     * Get the pin ids for the underlying microcontroller/board.
     */
    std::array<uint8_t, N> getPinIds() const noexcept { return ids; }

  private:
    std::array<uint8_t, N> ids;
};

/**
 * Alias for a group of pins with 2 members.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using OutputPinPair = OutputPinGroup<2>;

/**
 * Alias for a group of pins with 3 members.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using OutputPinTrio = OutputPinGroup<3>;

/**
 * Alias for a group of pins with 4 members.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using OutputPinQuartet = OutputPinGroup<4>;

/**
 * Alias for a group of pins with 5 members.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using OutputPinQuintet = OutputPinGroup<5>;

/**
 * Alias for a group of pins with 6 members.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using OutputPinSextet = OutputPinGroup<6>;

/**
 * Alias for a group of pins with 7 members.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using OutputPinSeptet = OutputPinGroup<7>;

/**
 * Alias for a group of pins with 8 members.
 *
 * > This is part of **I/O pins**.
 * >
 * > **Copyright** (C) 2025~2025 David SPORN.
 * > **Licence** GPL 3.0 or later.
 */
using OutputPinOctet = OutputPinGroup<8>;
// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
