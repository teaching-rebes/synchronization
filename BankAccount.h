#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <mutex>
#include <semaphore>

class BankAccount {
private:
  double balance;
  mutable std::mutex mx;              // for all solutions except semaphore
  std::counting_semaphore<1> sema{1}; // for semaphore solution only

public:
  BankAccount(double initial_balance);
  double get_balance() { return balance; };
  void add_money(double value);
};

#endif // BANKACCOUNT_H