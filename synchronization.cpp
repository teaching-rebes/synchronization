#include "synchronization.h"
#include "BankAccount.h"

#include <iostream>
#include <thread>

using namespace std;

BankAccount account = BankAccount(0.0);

void do_fundraising(int number_of_raisings) {
  for (int i = 0; i < number_of_raisings; i++) {
    account.add_money(1);
  }
}

void run_multiple_fundraising_threads() {

  thread threadA(do_fundraising, 500000);
  thread threadB(do_fundraising, 500000);

  threadA.join();
  threadB.join();
  cout << "all threads have finished - balance: " << account.get_balance()
       << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main method
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  run_multiple_fundraising_threads();
  return 0;
}
