#pragma once

#include "Registry.hpp"
#include "../../graphics/Shader.hpp"

#include <type_traits>

namespace Pirkk::Util::Registry {
	class RegistryHandler {
	private:
		static std::map<size_t, std::shared_ptr<Registry<void>>> registries;

		template<typename T>
		void addRegistry(std::shared_ptr<Registry<T>> registry) {
			size_t hash = typeid(T).hash_code();
			if (!registries.count(hash)) registries[hash] = registry;
			else std::cout << "Registry already exists: " << typeid(T).name();
		}

		template<typename T>
		std::shared_ptr<Registry<T>> getRegistry() {
			size_t hash = typeid(T).hash_code();
			auto it = registries.find(hash);
			if (it != registries.end()) return it->second;
			else throw std::exception("Could not find registry: " << typeid(T).name());
		}
	};
}