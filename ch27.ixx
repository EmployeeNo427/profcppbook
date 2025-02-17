export module ch27;

import std;

export namespace ch27 {
	namespace exercises {
		namespace ex1 {
			namespace myanswer {
				using namespace std;

				void threadFunction(chrono::seconds duration) {
					while (true) {
						print("\a");
						this_thread::sleep_for(duration);
					}
				}
				void test() {
					jthread job1{ threadFunction, 3s };
					/*while (true) {
						this_thread::sleep_for(20min);
					}*/
				}
			}
		}
		namespace ex2 {
			namespace myanswer {
				using namespace std;

				void threadFunction(stop_token token, chrono::seconds duration) {
					while (!token.stop_requested()) {
						print("\a");
						this_thread::sleep_for(duration);
					}
				}
				void test() {
					jthread job1{ threadFunction, 3s };
					cin.ignore();
					println("stop requested by enter");
				}
			}
		}
		namespace ex3 {
			namespace myanswer {
				using namespace std;
				atomic<bool> wait_needed{ false };

				void threadFunction(chrono::seconds duration) {
					while (true) {
						if (wait_needed) {
							wait_needed.wait(true);
						}
						print("\a");
						this_thread::sleep_for(duration);
					}
				}
				void test() {
					jthread job1{ threadFunction, 3s };
					while (true) {
						//Press entered for pause
						cin.ignore();
						wait_needed = true;
						println("paused");

						//Press entered for continue
						cin.ignore();
						wait_needed = false;
						wait_needed.notify_one();
						println("continue");
					}
				}
			}
			namespace textbook {
				using namespace std;
				using namespace std::chrono;

				atomic<bool> isBeepingEnabled{ true };

				void beeper(duration<int> delay)
				{
					while (true) {
						if (isBeepingEnabled) {
							print("\a");
						}
						this_thread::sleep_for(delay);
					}
				}

				void test() {
					jthread beepThread{ beeper, 3s };

					while (true) {
						print("Press enter to pause beeping");
						cin.ignore();
						isBeepingEnabled = !isBeepingEnabled;

						print("Press enter to resume beeping");
						cin.ignore();
						isBeepingEnabled = !isBeepingEnabled;
					}
				}
			}
		}
	}
}