#ifndef GBAXX_REGISTERS_HPP
#define GBAXX_REGISTERS_HPP

#include <gba/int.hpp>

namespace gba {
namespace io {

static constexpr uintptr reg_dispcnt = 0x4000000;

static constexpr uintptr reg_dispstat = 0x4000004;
static constexpr uintptr reg_vcount = 0x4000006;

static constexpr uintptr reg_bg0cnt = 0x4000008;
static constexpr uintptr reg_bg1cnt = 0x400000A;
static constexpr uintptr reg_bg2cnt = 0x400000C;
static constexpr uintptr reg_bg3cnt = 0x400000E;

static constexpr uintptr reg_bg0hofs = 0x4000010;
static constexpr uintptr reg_bg0vofs = 0x4000012;
static constexpr uintptr reg_bg1hofs = 0x4000014;
static constexpr uintptr reg_bg1vofs = 0x4000016;
static constexpr uintptr reg_bg2hofs = 0x4000018;
static constexpr uintptr reg_bg2vofs = 0x400001A;
static constexpr uintptr reg_bg3hofs = 0x400001C;
static constexpr uintptr reg_bg3vofs = 0x400001E;

static constexpr uintptr reg_bg2pa = 0x4000020;
static constexpr uintptr reg_bg2pb = 0x4000022;
static constexpr uintptr reg_bg2pc = 0x4000024;
static constexpr uintptr reg_bg2pd = 0x4000026;

static constexpr uintptr reg_bg2x_l = 0x4000028;
static constexpr uintptr reg_bg2x_h = 0x400002A;
static constexpr uintptr reg_bg2y_l = 0x400002C;
static constexpr uintptr reg_bg2y_h = 0x400002E;

static constexpr uintptr reg_bg3pa = 0x4000030;
static constexpr uintptr reg_bg3pb = 0x4000032;
static constexpr uintptr reg_bg3pc = 0x4000034;
static constexpr uintptr reg_bg3pd = 0x4000036;

static constexpr uintptr reg_bg3x_l = 0x4000038;
static constexpr uintptr reg_bg3x_h = 0x400003A;
static constexpr uintptr reg_bg3y_l = 0x400003C;
static constexpr uintptr reg_bg3y_h = 0x400003E;

static constexpr uintptr reg_win0h = 0x4000040;
static constexpr uintptr reg_win1h = 0x4000042;
static constexpr uintptr reg_win0v = 0x4000044;
static constexpr uintptr reg_win1v = 0x4000046;
static constexpr uintptr reg_winin = 0x4000048;
static constexpr uintptr reg_winout = 0x400004A;

static constexpr uintptr reg_mosaic = 0x400004C;

static constexpr uintptr reg_bldcnt = 0x4000050;
static constexpr uintptr reg_bldalpha = 0x4000052;
static constexpr uintptr reg_bldy = 0x4000054;

static constexpr uintptr reg_ime = 0x4000208;

template <typename Type>
volatile Type& register_cast( uintptr address ) {
	return *reinterpret_cast<volatile Type *>( address );
}

/*
static volatile display::control& reg_dispcnt = *reinterpret_cast<volatile display::control *>( 0x4000000 );
static volatile display::status& reg_dispstat = *reinterpret_cast<volatile display::status *>( 0x4000004 );
static volatile uint16& reg_vcount = *reinterpret_cast<volatile uint16 *>( 0x4000006 );

static volatile uint32& reg_ime = *reinterpret_cast<volatile uint32 *>( 0x4000208 );

static volatile uint32& reg_ime = *reinterpret_cast<volatile uint32 *>( 0x4000208 );

struct lcd_control {};

template <class Tag>
using tag_type;

template <>
using tag_type<lcd_control> = decltype( display::control );

template <class Tag, class Register>
volatile Register& registers() {}

template <>
volatile display::control& registers<lcd_control, tag_type<lcd_control>>() {
	return reg_dispcnt;
}
*/

} // io
} // gba

#endif // define GBAXX_REGISTERS_HPP
