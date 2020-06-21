#ifndef GBAXX_DMA_HPP
#define GBAXX_DMA_HPP

#include <gba/dma_control.hpp>
#include <gba/memmap.hpp>

namespace gba {
namespace dma {

namespace detail {

	template <unsigned Channel>
	class transfer {
	protected:
		struct count_control {
			uint16				count;
			const dma_control	control;
		};
	public:
		constexpr transfer( const dma_control& control ) noexcept : m_control { 0, control } {}

		template <typename Dest, typename Source>
		auto& invoke( Dest * dst, const Source * src, const uint32 count ) const noexcept {
			using address_destination = omemmap<Dest, 0x040000B4 + ( 12 * Channel )>;
			using address_source = omemmap<Source, 0x040000B0 + ( 12 * Channel )>;
			using count_control = omemmap<count_control, 0x040000B8 + ( 12 * Channel )>;

			address_destination::write( dst );
			address_source::write( src );
			count_control::write( m_control );
			return *this;
		}

		bool ready() noexcept {
			using control = imemmap<dma_control, 0x040000BA + ( 12 * Channel )>;

			return control::read().enable_transfer;
		}

	protected:
		count_control	m_control;

	};

} // detail

} // dma
} // gba

#endif // define GBAXX_DMA_HPP