Memory Mapped IO
================

.. code-block:: cpp

    using reg_dispcnt = gba::iomemmap<short, 0x4000000>;

    reg_dispcnt::emplace( 1 << 8 ); // BG0 on
    short value = reg_dispcnt::read();
    if ( value & ( 1 << 8 ) ) {
        // BG0 is on
    }

    reg_dispcnt::generate( []() {
        return 1 << 10; // BG2 on
    } );

    reg_dispcnt::transform( []( short& dispcnt ) {
        if ( dispcnt & ( 1 << 10 ) ) {
            dispcnt |= 3; // Enable mode 3
        }
    } );

.. doxygenfile:: gba/types/memmap.hpp
   :project: gba-plusplus
