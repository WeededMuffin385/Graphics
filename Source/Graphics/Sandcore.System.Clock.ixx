export module Sandcore.System.Clock;

import std;

export namespace Sandcore {
	class Clock {
	public:
		double getElapsedTime() {
			return std::chrono::duration<double>(end - begin).count();
		}

		void restart() {
			begin = end;
			end = std::chrono::high_resolution_clock::now();
		}
	private:
		std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	};
}