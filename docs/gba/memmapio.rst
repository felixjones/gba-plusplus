Memory Mapped IO
================

The GBA hardware features are accessed by reading and writing to addresses mapped as memory. This is known as "Memory Mapped Input/Output".

Addresses from ``4000000h`` to ``40003FEh`` are mapped to the various I/O registers of the GBA.

gba-plusplus provides the ``gba::*memmap<>`` accessor types for memory mapped IO.

These accessor types provide volatile read/write operations that can also bit-cast the IO registers into non-fundamental types.

.. doxygenclass:: gba::memmap
   :project: gba-plusplus
   :members:

Input (read only)
-----------------

.. code-block:: cpp

    using reg_vcount = gba::imemmap<short, 0x4000006>;

    // Wait for vblank
    while ( reg_vcount::read() < 160 );

.. doxygenclass:: gba::imemmap
   :project: gba-plusplus
   :members:

Output (write only)
-------------------

.. code-block:: cpp

    struct mosaic {
        int bg_hsize : 4;
        int bg_vsize : 4;
        int obj_hsize : 4;
        int obj_vsize : 4;
    };

    using reg_mosaic = gba::omemmap<mosaic, 0x400004C>;

    // Copy into IO register
    auto m = mosaic { 2, 2, 0, 0 };
    reg_mosaic::write( m );

    // Move into IO register
    reg_mosaic::write( mosaic { 2, 2, 0, 0 } );

    // Initialize from generator
    reg_mosaic::generate( []() {
        return mosaic { 2, 2, 0, 0 };
    } );

    // Emplace struct into IO register
    reg_mosaic::emplace( 2, 2, 0, 0 );

.. doxygenclass:: gba::omemmap
   :project: gba-plusplus
   :members:

Input & output (read & write)
-----------------------------

.. code-block:: cpp

    struct ie {
        bool vblank : 1;
        bool hblank : 1;
        // ...
    };

    using reg_ie = gba::iomemmap<ie, 0x4000200>;

    // Read & modify IO register
    reg_ie::transform( []( ie& irqs ) {
        irqs.vblank = true;
        irqs.hlank = false;
    } );

.. doxygenclass:: gba::iomemmap
   :project: gba-plusplus
   :members:

Hardware Registers
------------------

.. toctree::
   :maxdepth: 4
   :glob:

   registers/*
