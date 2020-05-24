#ifndef GBAXX_CONST_HPP
#define GBAXX_CONST_HPP

namespace gba {

template <class Type>
constexpr Type make( void( *f )( Type& ) ) noexcept {
	Type value {};
	f( value );
	return value;
}

} // gba

#endif // define GBAXX_CONST_HPP
