#include "Account.hh"

int main() {
	Account a1;
	a1.deposit(500);
	a1.withdraw(200);
	cout << a1.getBalance() << '\n';
}
