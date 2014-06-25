
#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <typeinfo>
#include <string>

#include <cxxabi.h>

inline std::string
demangle_name(char const* mangled) {
	std::size_t len = 0;
	int status = 0;

	char* str = abi::__cxa_demangle(mangled, 0, &len, &status);
	std::string demangled{str/*, len*/};
	std::free(str);
	return demangled;
}

template<class T>
inline std::string
demangle(T&& x) {
	return demangle_name(typeid(decltype(x)).name());
}

template<class T>
inline std::string
demangle() {
	return demangle_name(typeid(T).name());
}

