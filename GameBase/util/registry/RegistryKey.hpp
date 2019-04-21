#pragma once

#include <string>

namespace Pirkk::Util::Registry {
	class RegistryKey {
	private:
		const std::string key;

	public:
		RegistryKey(std::string key) : key(key) {}
		std::string getKey() { return key; }
	};
}