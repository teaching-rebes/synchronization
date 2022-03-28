#include "BankAccount.h"

BankAccount::BankAccount(double initial_balance) : balance(initial_balance) {
  // constructor
}

void BankAccount::add_money(double value) { 
    mx.lock();    
    balance = balance + value; 
    mx.unlock();
}