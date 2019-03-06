#pragma once

#include <vector>
#include <functional>
#include <atomic>

#include "TickCallback.h"

namespace PirkkBase {
	class TickManager {
	private:
		static std::vector<TickCallback> callbacks;
		static std::atomic_bool running;

	public:
		static void start(); // CAREFUL - BLOCKS CALLING THREAD
		static void stop();
		static void loop(); 
		static void registerCallback(TickCallback callback);
	};
}

