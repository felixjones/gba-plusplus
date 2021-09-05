Integer Types
=============

The GBA has registers that are 32-bits wide.

Due to limitations in the ``armv4t`` architecture any operations performed on data-types that are not 32-bits wide will require additional instructions to clear the upper bits and propagate any sign-bit for any signed arithmetic.

.. code-block:: cpp

    [[nodiscard]]
    short increment( const short value ) noexcept {
        return value + 1;
    }

    [[nodiscard]]
    int increment( const int value ) noexcept {
        return value + 1;
    }

Notice how the produced assembly code has two additional instructions for the 16-bit short version versus the 32-bit int version.

.. code-block:: asm

    increment(short):
        add     r0, r0, #1
        lsl     r0, r0, #16
        asr     r0, r0, #16
        bx      lr

    increment(int):
        add     r0, r0, #1
        bx      lr

This is even worse for unsigned values:

.. code-block:: cpp

    [[nodiscard]]
    unsigned short increment( const unsigned short value ) noexcept {
        return value + 1u;
    }

    [[nodiscard]]
    unsigned int increment( const unsigned int value ) noexcept {
        return value + 1u;
    }

The 16-bit unsigned short version inserts 3 additional instructions that build a mask to clear the upper 16-bits from the result.

.. code-block:: asm

    increment(unsigned short):
        mov     r1, #255
        add     r0, r0, #1
        orr     r1, r1, #65280
        and     r0, r0, r1
        bx      lr

    increment(unsigned int):
        add     r0, r0, #1
        bx      lr

For these reasons, a good rule to stick by is to always use 32-bit integers for operations, and only use other sizes for loading/storing the values.

gba-plusplus provides 8-bit, 16-bit and 32-bit sized integer types:

.. code-block:: cpp

    [[nodiscard]]
    gba::int32 increment( const gba::int32 value ) noexcept {
        return value + 1;
    }

    [[nodiscard]]
    gba::uint32 increment( const gba::uint32 value ) noexcept {
        return value + 1u;
    }

These are defined by the ``gba::int_type<>`` and ``gba::uint_type<>`` templates, which provides appropriately sized storage for a desired minimum bit-length.

.. doxygenstruct:: gba::int_type
   :project: gba-plusplus
   :members:

.. doxygenstruct:: gba::uint_type
   :project: gba-plusplus
   :members:
