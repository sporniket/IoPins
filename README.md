# I/O Pins
C++ abstraction layer for I/O pins of micro-controllers.

## LICENSE

GPL v3

## What's new

_Work In Progress_


## Typical application

### InputPin

Depending on the storage type, can be used as a base to implement binary (`bool`) or analog (`uint` of sufficient width) pins.

### LogicInputPin

Binary pin whose physical voltage is interpreted :

* either as **Active High** : voltage under low level threshold is 0/`false`, voltage above high level threshold is 1/`true` ;
* or as **Active Low** : voltage under low level threshold is 1/`true`, voltage above high level threshold is 0/`false`.

### OutputPin

Depending on the storage type, can be used as a base to implement binary (`bool`), analog (`uint` of sufficient width), or PWM (`uint` of sufficient width) pins.

### LogicOutputPin

Binary pin whose value is translated :

* either as **Active High** voltage : low level when false, high level when true ;
* or as **Active Low** voltage : high level when false, low level when true.

### InputPinGroup

When wanting to read the state of a set of coordinated pins in a single operation. Typical implementation will
probe the hardware register containing the immediate state of all the pins.

Typical application : read port of a keyboard matrix.

### OutputPinGroup

When wanting to write the state of a set of coordinated pins in a single operation. Typical implementation will
write the hardware registers allowing to set or clear the relevant pins.

Typical application : write port of a keyboard matrix.
