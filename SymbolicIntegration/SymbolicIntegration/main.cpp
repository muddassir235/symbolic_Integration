#include"Integrator.h"
#include<iostream>
#include<string>


using namespace std;

int main(void) {
	char c;
	Integrator integrator('x');
	cout << integrator.integrate("23x+sinx");

	cin >> c;
	return 0;
}