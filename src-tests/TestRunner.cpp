/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers..
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include <cstdint>
// FIXME includes your hpp files from ../include
// e.g. #include "whatever.hpp"
#include "cmspk/iopins.hpp"

// FIXME write actual tests

using cmspk::iopins::BinaryInputPin;
using cmspk::iopins::BinaryOutputPin;
using cmspk::iopins::IoDirection;
using cmspk::iopins::IoFailureReason;
using cmspk::iopins::LogicInputPin;
using cmspk::iopins::LogicIoPinSetting;
using cmspk::iopins::LogicOutputPin;

// common helper classes
struct BoolValue {
    bool value;
};

#include "UT-InputPin.hpp"
#include "UT-LogicInputPin.hpp"
#include "UT-LogicOutputPin.hpp"
#include "UT-OutputPin.hpp"
