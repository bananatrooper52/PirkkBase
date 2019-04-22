#pragma once

#include <string>

namespace pirkk::util::registry {
	class RegistryKey {
	private:
		const std::string key;

	public:
		RegistryKey(std::string key) : key(key) {}
		std::string getKey() { return key; }
	};
}