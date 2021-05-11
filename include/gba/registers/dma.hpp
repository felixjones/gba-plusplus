#ifndef GBAXX_REGISTERS_DMA_HPP
#define GBAXX_REGISTERS_DMA_HPP

#include <gba/dma/dma_control.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using dma0sad = omemmap<uint32, 0x40000B0>;
using dma0dad = omemmap<uint32, 0x40000B4>;
using dma0cnt_l = omemmap<uint16, 0x40000B8>;
using dma0cnt_h = iomemmap<dma_control, 0x40000Ba>;
using dma0cnt = iomemmap<dma_transfer_control, 0x40000B8>;

using dma1sad = omemmap<uint32, 0x40000Bc>;
using dma1dad = omemmap<uint32, 0x40000c0>;
using dma1cnt_l = omemmap<uint16, 0x40000c4>;
using dma1cnt_h = iomemmap<dma_control, 0x40000c6>;
using dma1cnt = iomemmap<dma_transfer_control, 0x40000c4>;

using dma2sad = omemmap<uint32, 0x40000c8>;
using dma2dad = omemmap<uint32, 0x40000cc>;
using dma2cnt_l = omemmap<uint16, 0x40000d0>;
using dma2cnt_h = iomemmap<dma_control, 0x40000d2>;
using dma2cnt = iomemmap<dma_transfer_control, 0x40000d0>;

using dma3sad = omemmap<uint32, 0x40000d4>;
using dma3dad = omemmap<uint32, 0x40000d8>;
using dma3cnt_l = omemmap<uint16, 0x40000dc>;
using dma3cnt_h = iomemmap<dma_control, 0x40000de>;
using dma3cnt = iomemmap<dma_transfer_control, 0x40000dc>;

} // reg
} // gba

#endif // define GBAXX_REGISTERS_DMA_HPP
