#include "BankAccount.h"

BankAccount::BankAccount(double initial_balance) : balance(initial_balance) {
  // constructor
}

/* primitive solution using mutex directly

void BankAccount::add_money(double value) {
    mx.lock();
    balance = balance + value;
    mx.unlock();
}
*/

/* better solution: use lock guard */

void BankAccount::add_money(double value) {
  std::lock_guard<std::mutex> lockGuard(mx); // protects until end of method
  balance = balance + value;
}
