#pragma once

class Account {
private:
	double balance;
public:
	Account() : balance(0) {}
	void deposit(double amt);
	bool withdraw(double amt);
	double getBalance() const;
};
