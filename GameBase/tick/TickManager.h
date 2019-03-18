#pragma once

#include <map>
#include <functional>
#include <atomic>

#include "TickCallback.h"

namespace PirkkBase {
	namespace Ticking {
		class TickManager {
		private:
			std::map<const char *, TickCallback *> callbacks;
			std::atomic_bool running;

		public:
			void start(); // CAREFUL - BLOCKS CALLING THREAD
			void stop();
			void loop();
			void registerCallback(const char *name, TickCallback *callback);
			void unregisterCallback(const char *name); // Remove callback from update list
			TickCallback *getCallback(const char *name);
		};
	}
}

