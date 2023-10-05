export module Sandcore.System.Timer;

import std;

export namespace Sandcore {
	class Timer {
	public:
		double getElapsedTime() {
			return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin).count();
		}

		void restart() {
			begin = std::chrono::high_resolution_clock::now();
		}
	private:
		std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	};
}