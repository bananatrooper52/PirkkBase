#pragma once

#include "Registry.hpp"
#include "../../graphics/Shader.hpp"

#include <type_traits>
#include <exception>
#include <map>

namespace pirkk::util::registry {
	class RegistryHandler {
	private:
		static std::map<size_t, std::shared_ptr<Registry<void>>> registries;

	public:
		template<typename T>
		static std::shared_ptr<Registry<T>> addRegistry() {
			size_t hash = typeid(T).hash_code();
			std::shared_ptr<Registry<T>> registry = std::make_shared<Registry<T>>();
			if (!registries.count(hash)) registries[hash] = std::reinterpret_pointer_cast<Registry<void>>(registry);
			else std::cout << "Registry already exists: " << typeid(T).name();
			return registry;
		}

		template<typename T>
		static void removeRegistry() {
			size_t hash = typeid(T).hash_code();
			auto it = registries.find(hash);
			if (it != registries.end()) registries.erase(it);
			else std::cout << "Cannot remove a registry that does not exist: " << typeid(T).name();
		}

		template<typename T>
		static std::shared_ptr<Registry<T>> getRegistry() {
			size_t hash = typeid(T).hash_code();
			auto it = registries.find(hash);
			if (it != registries.end()) return std::reinterpret_pointer_cast<Registry<T>>(it->second);
			else throw std::runtime_error(std::string("Could not find registry: ") + std::string(typeid(T).name()));
		}
	};
}