#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <mutex>

class BankAccount {
private:
  double balance;
  mutable std::mutex mx;

public:
  BankAccount(double initial_balance);
  double get_balance() { return balance; };
  void add_money(double value);
};

#endif // BANKACCOUNT_H