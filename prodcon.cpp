/*
EXAMPLE SOLUTION:
Writing an own multi-threaded program with data producers and consumers.
*/

#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>

// number of parallel running producer and consumer threads
#define N_PRODUCERS 10
#define N_CONSUMERS 10

using namespace std;

queue<double> data_values; // store data values produced by the producer threads
mutex mutex_queue;         // synchronize access to data queue
condition_variable data_ready; // indicate that new data is available

thread prod[N_PRODUCERS];
thread cons[N_CONSUMERS];

void produce_data(string name, int random_seed) {
  srand(random_seed); // initialize random number generator
  double result;

  while (true) {
    result = double(rand());
    for (long i = 0; i < 10000000; i++) {
      result = result / 1.000000123456; // some hard work
    }

    { // protected critical section: add value to queue
      std::lock_guard<mutex> guard(
          mutex_queue); // see Kap 2, "Praxis: Lock Guard in C++"
      data_values.push(result);
      cout << "Producer " << name << " added data value " << result
           << std::endl;
    }
    data_ready
        .notify_one(); // notify one of our consumers that new data is available
  }
}

void consume_data(string name) {
  double consumed_data;

  while (true) {
    unique_lock<mutex> consumer_lock{
        mutex_queue}; // need unique_lock for using wait below
    data_ready.wait(consumer_lock, [] {
      return !data_values.empty();
    }); // wait until data is available

    // now we know that data is available, consumer still has the lock
    consumed_data = data_values.front();
    data_values.pop();
    cout << "Consumer " << name << " consumed data value " << consumed_data
         << std::endl;
    consumer_lock.unlock(); // critical part has ended, free lock
  }
}

void start_consumers() {
  for (int i = 0; i < N_CONSUMERS; i++) {
    cons[i] = thread(consume_data, to_string(i + 1));
  }
}

void start_producers() {
  for (int i = 0; i < N_PRODUCERS; i++) {
    prod[i] = thread(produce_data, to_string(i + 1), i);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main method
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  cout << "Starting producers and consumers, hit ENTER to cancel." << endl;

  start_consumers();
  start_producers();

  string line;
  getline(cin, line);
  return 0;
}
