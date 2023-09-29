#ifndef BE_TYPES_H_INCLUDED
#define BE_TYPES_H_INCLUDED

#include <cstdint>
#include <cmath>
#include <vector>
#include <string>

// BASIC TYPES
	typedef bool Bbool;
	typedef std::float_t Bfloat;
	typedef std::double_t Bdouble;
	typedef std::string Bstring;

	typedef std::uint8_t Buint8;
	typedef std::uint16_t Buint16;
	typedef std::uint32_t Buint32;
	typedef std::uint64_t Buint64;
	typedef Buint32 Buint;

	typedef std::int8_t Bint8;
	typedef std::int16_t Bint16;
	typedef std::int32_t Bint32;
	typedef std::int64_t Bint64;
	typedef Bint32 Bint;

// BEntity pointers and maps
	class BEntity;

	typedef std::vector<BEntity*> BEntityVector;

// MACROS

	//if ( hasChildren() ) 

 	#define for_all_children \
		const auto& children_vector = children(); \
		const auto& begin = children_vector.begin(); \
		const auto& end = children_vector.end(); \
		for ( auto child(begin); child != end; ++child )
	
 	// #define for_all_children
	//	const auto& children_vector = children();
	//	for ( auto child(children_vector.begin()); child != children_vector.end(); ++child )

	#define for_all_children_of(e) \
		const auto& children_vector = e->children(); \
		for ( auto child(children_vector.begin()); child != children_vector.end(); ++child )

	#define for_all_children_of2(e) \
		const auto& children_vector2 = e->children(); \
		for ( auto child2(children_vector2.begin()); child2 != children_vector2.end(); ++child2 )

	#define for_all_children_of3(e) \
		const auto& children_vector3 = e->children(); \
		for ( auto child3(children_vector3.begin()); child3 != children_vector3.end(); ++child3 )
			
	// #define for_all_children
	// 	for ( auto child(children().begin()); child != children().end(); ++child )

	// #define for_all_children_reverse
	// 	for ( auto child(m_children.rbegin()); child != m_children.rend(); ++child )

	// #define for_all_children_of(e)
	// 	if ( e->hasChildren() ) for ( auto child(e->children().begin()); child != e->children().end(); ++child )
			
	#define do_times(n) \
		for ( Buint dtc(0); dtc < n; ++dtc )

	// not sure if needed
	#define do_times2(m) \
		for ( Buint d(0); d < m; ++d )
			
			
			
			
			
			

			
#endif
