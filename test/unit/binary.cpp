
#include "./../common/traits.hpp"

#include <Cacophony/utility.hpp>
#include <Cacophony/traits.hpp>
#include <Cacophony/BinarySerializer.hpp>
#include <Cacophony/support/std_vector.hpp>

#include <vector>
#include <iomanip>
#include <iostream>

#include <duct/debug.hpp>
#include <duct/IO/dynamic_streambuf.hpp>

using ISer = Cacophony::BinaryInputSerializer;
using OSer = Cacophony::BinaryOutputSerializer;

struct X1 {
	unsigned u;
	signed s;
	std::vector<float> v;

	template<class Ser>
	inline Cacophony::tag_serialize<Ser>
	serialize(Ser& ser) {
		auto& self = Cacophony::const_safe<Ser>(*this);
		ser(
			self.u,
			self.s,
			self.v,
			Cacophony::make_vector_cfg<std::uint64_t>(self.v)
		);
	}

	bool
	operator==(X1 const& other) const noexcept {
		return
			this->u == other.u &&
			this->s == other.s &&
			this->v.size() == other.v.size() &&
			std::equal(
				this->v.cbegin(), this->v.cend(),
				other.v.cbegin()
			)
		;
	}

	bool
	operator!=(X1 const& other) const noexcept {
		return !(*this == other);
	}
};

struct X2Base {
	signed a;

	virtual ~X2Base() = 0;
	X2Base(signed a) : a(a) {}

	bool
	operator==(X2Base const& other) const noexcept {
		return this->a == other.a;
	}

private:
	friend class Cacophony::accessor;

	template<class Ser>
	inline Cacophony::tag_read<Ser>
	read(Ser& ser) {
		auto& self = Cacophony::const_safe<Ser>(*this);
		ser(self.a);
	}

	template<class Ser>
	inline Cacophony::tag_write<Ser>
	write(Ser& ser) const {
		auto& self = Cacophony::const_safe<Ser>(*this);
		ser(self.a);
	}
};

inline
X2Base::~X2Base() = default;

struct X2 : public X2Base {
	unsigned b;

	~X2() override = default;
	X2(signed a, unsigned b) : X2Base(a), b(b) {}

	template<class Ser>
	inline Cacophony::tag_serialize<Ser>
	serialize(Ser& ser) {
		auto& self = Cacophony::const_safe<Ser>(*this);
		ser(
			Cacophony::base_cast<X2Base>(self),
			self.b
		);
	}

	bool
	operator==(X2 const& other) const noexcept {
		return
			X2Base::operator==(other) &&
			this->b == other.b
		;
	}

	bool
	operator!=(X2 const& other) const noexcept {
		return !(*this == other);
	}
};

signed
main() {
	#define trait(t_) \
		<< #t_ << " = " << Cacophony:: t_
	std::cout
		<< std::boolalpha
		trait(is_input_serializer)<ISer>::value << '\n'
		trait(is_output_serializer)<OSer>::value << '\n'
		<< std::endl
	;
	#undef trait

	print_traits<ISer, OSer, X1>();
	print_traits<ISer, OSer, X2Base>();
	print_traits<ISer, OSer, X2>();

	signed x = 42;
	auto& cs1 = Cacophony::const_safe<ISer>(x);
	auto& cs2 = Cacophony::const_safe<OSer>(x);
	std::cout
		<< std::boolalpha
		<< "const_safe: (ref, const)\n"
		<< "ISer: "
		<< std::is_reference<decltype(cs1)>::value << ", "
		<< std::is_const<std::remove_reference<decltype(cs1)>::type>::value << '\n'
		<< "OSer: "
		<< std::is_reference<decltype(cs2)>::value << ", "
		<< std::is_const<std::remove_reference<decltype(cs2)>::type>::value << '\n'
	;

	duct::IO::dynamic_streambuf buf{64u, 0u};

	std::ostream ostream{&buf};
	OSer oser{ostream, duct::Endian::little};

	X1 const x1_out{42, -3, {{1, 2, 3}}};
	oser(x1_out);

	X2 const x2_out{-3, 42};
	oser(x2_out);

	buf.commit();
	std::istream istream{&buf};
	ISer iser{istream, duct::Endian::little};

	X1 x1_in{~0u, signed{~0}, {}};
	DUCT_ASSERTE(x1_out != x1_in);
	iser(x1_in);
	DUCT_ASSERTE(x1_out == x1_in);

	X2 x2_in{signed{~0}, ~0u};
	DUCT_ASSERTE(x2_out != x2_in);
	iser(x2_in);
	DUCT_ASSERTE(x2_out == x2_in);

	return 0;
}
