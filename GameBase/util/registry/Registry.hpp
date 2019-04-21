#pragma once

#include "RegistryKey.hpp"

#include <map>
#include <memory>
#include <iostream>

namespace Pirkk::Util::Registry {

	template<typename T>
	class Registry {
	private:
		std::map<std::string, std::shared_ptr<T>> entries;

	public:
		void registerEntry(std::string key, std::shared_ptr<T> value) {
			if (!entries.count(key)) entries[key] = value;
			else std::cout << "Cannot register entry with duplicate key: " << key << std::endl;
		}

		void unregisterEntry(std::string key) {
			auto it = entries.find(key);
			if (it != entries.end()) entries.erase(it);
			else std::cout << "Cannot unregister an entry that doesn't exist: " << key << std::endl;
		}

		std::shared_ptr<T> getEntryValue(std::string key) {
			auto it = entries.find(key);
			if (it == entries.end()) return nullptr;
			return it->second;
		}
	};
}