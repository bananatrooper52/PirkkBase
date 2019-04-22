#pragma once

#include <map>
#include <functional>
#include <atomic>

#include "TickCallback.hpp"

namespace pirkk::ticking {
	class TickManager {
	private:
		std::map<const char *, TickCallback *> callbacks;
		std::atomic_bool running;
		void loop();

	public:
		void start(); // CAREFUL - BLOCKS CALLING THREAD
		void stop();
		void registerCallback(const char *name, TickCallback *callback);
		void unregisterCallback(const char *name); // Remove callback from update list
		TickCallback *getCallback(const char *name);
	};
}