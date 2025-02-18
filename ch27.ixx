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
		namespace ex4 {
			namespace myanswer {
				using namespace std;

				unsigned long long fibonacci(unsigned int n) {
					unsigned long long a{ 0 };
					unsigned long long b{ 1 };

					unsigned long long temp{ 0 };

					for (unsigned long long ull{ 0 }; ull < n; ++ull) {
						temp = a + b;
						swap(a, b);
						swap(b, temp);
					}
					return a;
				}

				void fibonacci_concurrent(unsigned int n) {
					unsigned numberOfWorkerThreads{ n };
					latch latch{ numberOfWorkerThreads };
					vector<jthread> threads;
					vector<unsigned long long> sequence;
					mutex mut;

					for (unsigned long long ull{ 0 }; ull < n; ++ull) {
						threads.emplace_back([&latch, &sequence, &mut, ull] {
							{
								lock_guard lock{ mut };
								sequence.push_back(fibonacci(static_cast<unsigned int>(ull)));
							}
							latch.count_down();
						});
					}
					latch.wait();
					ranges::sort(sequence);
					println("Sequence: {:n}", sequence);
					auto sum{ ranges::fold_left_first(sequence, plus<>{}) };
					println("sum: {}", sum.value_or(0));
				}

				void test() {
					fibonacci_concurrent(0);
					fibonacci_concurrent(1);
					fibonacci_concurrent(2);
					fibonacci_concurrent(3);
					fibonacci_concurrent(4);
					fibonacci_concurrent(5);
					fibonacci_concurrent(6);
					fibonacci_concurrent(7);
					fibonacci_concurrent(8);
					fibonacci_concurrent(9);
					fibonacci_concurrent(10);
					fibonacci_concurrent(11);
					fibonacci_concurrent(12);
				}
			}
			namespace myanswer2 {
				using namespace std;

				unsigned long long fibonacci(unsigned int n) {
					unsigned long long a{ 0 };
					unsigned long long b{ 1 };

					unsigned long long temp{ 0 };

					for (unsigned long long ull{ 0 }; ull < n; ++ull) {
						temp = a + b;
						swap(a, b);
						swap(b, temp);
					}
					return a;
				}

				void test() {
					vector fibonacci_inputs{ 0,1,2,3,4,5,6,7,8,9,10,11,12 };

					vector<future<unsigned long long>> futures;
					for (auto& input : fibonacci_inputs) {
						futures.push_back(async(launch::async, fibonacci, input));
					}

					vector<unsigned long long> sequence;
					for (auto& future : futures) {
						sequence.push_back(future.get());
					}

					println("Take2:\nSequence: {:n}", sequence);
					auto sum{ ranges::fold_left_first(sequence, plus<>{}) };
					println("sum: {}", sum.value_or(0));
				}

			}
			namespace textbook {
				using namespace std;

				unsigned long long fibonacci(unsigned int n)
				{
					if (n == 0) { return 0; }
					else if (n == 1) { return 1; }

					unsigned long long a{ 0 };
					unsigned long long b{ 1 };

					unsigned long long result{ 0 };
					for (unsigned int i{ 1 }; i < n; ++i) {
						result = a + b;
						a = b;
						b = result;
					}
					return result;
				}

				void test()
				{
					// Indices of Fibonacci numbers to calculate.
					vector fibonacciNumbersToCalculate{ 0,1,2,3,4,5,6,7,8,9,10,11,12 };

					// Launch threads to calculate the required numbers concurrently.
					vector<future<unsigned long long>> futures;
					for (auto& index : fibonacciNumbersToCalculate) {
						futures.push_back(async(launch::async, fibonacci, index));
					}

					// Wait for all threads to finish and collect results.
					vector<unsigned long long> fibonacciNumbers;
					for (auto& f : futures) {
						fibonacciNumbers.push_back(f.get());
					}

					// Print the calculated numbers.
					println("Textbook:\nFibonacci numbers: {}", fibonacciNumbers);

					// Calculate their sum.
					println("Their sum: {}", ranges::fold_left(fibonacciNumbers, 0ull, std::plus<>{}));
				}
			}
		}
		namespace ex5 {
			namespace myanswer {
				using namespace std;
				void test()
				{
					constexpr unsigned numberOfRobots{ 2 };
					constexpr unsigned numberOfIterations{ 3 };
					unsigned iterationCount{ 1 };
					latch waitForPreperationLatch{ 1 };
					latch waitForRobotsLatch{ numberOfRobots };

					vector<jthread> robots;

					auto completionCallback{ [&]() noexcept {
						if (iterationCount == numberOfIterations) {
							println("Finished {} iterations, stopping robots.", numberOfIterations);
							for (auto& robot : robots) { robot.request_stop(); }
						}
						else {
							++iterationCount;
							println("All robots finished. Preparing iteration {}.", iterationCount);
							this_thread::sleep_for(1s);
							println("Iteration {} ready to start. Waking up robots.", iterationCount);
						}
					}};

					barrier robotSynchronization{ numberOfRobots, completionCallback };

					auto robotThreadFunction{ [&](stop_token token, string_view name) {
						this_thread::sleep_for(20s);
						println("   Thread for robot {} started.", name);
						waitForRobotsLatch.count_down();
						waitForPreperationLatch.wait();
						println("   Thread for robot {} wait is over, starts working.", name);
						while (!token.stop_requested()) {
							this_thread::sleep_for(1s);
							println("   {} finished.", name);
							robotSynchronization.arrive_and_wait();
						}
						println("   {} shutting down.", name);
					} };

					println("Creating {} robot threads.", numberOfRobots);

					for (unsigned i{ 0 }; i < numberOfRobots; ++i) {
						robots.emplace_back(robotThreadFunction, format("Robot_{}", i));
					}

					println("Waiting for all the robots to get started");
					waitForRobotsLatch.wait();
					println("Preparing first iteration.");
					this_thread::sleep_for(5s);
					println("first iteration preparation finished.");
					waitForPreperationLatch.count_down();

					for (auto& robot : robots) { robot.join(); }
					println("Done with all work.");
				}
			}
		}
		namespace ex6 {
			namespace myanswer {
				using namespace std;
				void atomicMin(atomic<int>& a, int b) {
					int expected{ a.load() };
					int desired{ min(expected,b) };
					while (!a.compare_exchange_strong(expected, desired)) {
						desired = min(expected, b);
					}
				}
				void test() {
					atomic<int> value{ 10 };
					println("Value = {}", value.load());
					atomicMin(value, 3);
					println("Result = {}", value.load());

					atomic<int> value1{ 10 };
					atomicMin(value1, 42);
					println("Min(10, 42) = {}", value1.load());

					atomic<int> value2{ 84 };
					atomicMin(value2, 42);
					println("Min(84, 42) = {}", value2.load());
				}
			}
		}
	}
}