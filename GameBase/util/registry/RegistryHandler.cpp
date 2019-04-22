#include "RegistryHandler.hpp"

using namespace pirkk::util::registry;

std::map<size_t, std::shared_ptr<Registry<void>>> RegistryHandler::registries;