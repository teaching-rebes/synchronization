#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

class BankAccount {
private:
  double balance;

public:
  BankAccount(double initial_balance);
  double get_balance() { return balance; };
  void add_money(double value);
};

#endif // BANKACCOUNT_H