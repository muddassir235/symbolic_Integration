#include<string>
#include<iostream>
#include<math.h>

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

using namespace std;

class Integrator
{
private:
	string variable;
public:
	
	Integrator(){
	}
	~Integrator(){}
	string integrate1(char* integrand, char variable)
	{
		char* _thisIntegrand = integrand;
		//initialize answer as an empty string
		string answer="";
		
		//there is a constant a the beginning of the integrand then 
		if (_thisIntegrand[0] >= '0'&&_thisIntegrand[0] <= '9') {
		
			// the index after the constant ends
			int endOfConstant=0;

			//until the constant ends append it the the answer
			for (int i = 0; (_thisIntegrand[i] >= '0' && _thisIntegrand[i] <= '9') ; i++ ) {
				answer = answer + _thisIntegrand[i];
				endOfConstant = i;
			}
			if (endOfConstant != (strlen(_thisIntegrand)-1)) {
				//integrand should be changed to a new integrand without the constant
				int indexIntegrand = 0;
				char* newIntegrand = new char[strlen(_thisIntegrand - endOfConstant - 1)];
				for (int i = endOfConstant + 1;i < strlen(_thisIntegrand);i++) {
					newIntegrand[indexIntegrand] = _thisIntegrand[i];
					indexIntegrand++;
				}
				newIntegrand[indexIntegrand] = '\0';
				_thisIntegrand = newIntegrand;
				//append the result of the new integrand's integration into the answer
				return answer = answer + integrate1(_thisIntegrand, variable);
			}
			else {
				return answer = answer + "x";
			}
		}

		//a boolean to check whether the string contain an addition or subtration operator
		bool containsPlusOrMinus=false;

		//loop that traverses the integrand character by character
		for (int i = 0;i < strlen(_thisIntegrand);i++) {
			//if we encounter a plus or a minus 
			if (_thisIntegrand[i] == '+'||_thisIntegrand[i]=='-') {
				containsPlusOrMinus = true;
				//a string that stores the characters before the + or - sign
				char* _integrandPart=new char[i];
				int indexIntegrand = 0;
				//storing the character before the + or - sign in the _integrandPart string
				for (int j = 0; j < i;j++) {
					_integrandPart[j] = _thisIntegrand[j];
					indexIntegrand++;
				}
				_integrandPart[indexIntegrand] = '\0';
				//appending the integration of the _integrandPart string into the answer
				answer=answer+integrate1(_integrandPart,variable);

				//appending the + or - symbol into the answer
				answer = answer + _thisIntegrand[i];

				//replacing the integrand string with a new string that contains only the characters after the + or - symbol
				indexIntegrand=0;
				char* newIntegrand = new char[strlen(_thisIntegrand)-i-1];
				for (int j = i+1;j < strlen(_thisIntegrand); j++) {
					newIntegrand[indexIntegrand] = _thisIntegrand[j];
					indexIntegrand++;
				}
				newIntegrand[indexIntegrand] = '\0';
				_thisIntegrand = newIntegrand;
				//append the answer with integation of the new intergrand
				return answer = answer + integrate1(_thisIntegrand, variable);
			}
		}

		//if the string doesn't contain any more plus or minus operators
		if (containsPlusOrMinus == false) {
			for (int i = 0;i < strlen(_thisIntegrand); i++) {
				if (_thisIntegrand[i] == variable) {
					if (_thisIntegrand[i + 1] == '^') {
						int lengthOfConstant = 0;
						for (int j = i + 2;(_thisIntegrand[j] >= '0' && _thisIntegrand[j] <= '9');j++) {
							lengthOfConstant++;
						}
						int power=0;
						for (int j = i + 2;(_thisIntegrand[j] >= '0' && _thisIntegrand[j] <= '9');j++) {
							power = power + (_thisIntegrand[j]-'0')*pow(10, lengthOfConstant-j+i+2-1);
						}
						return answer = answer + "/" + std::to_string(power+1)+variable+"^"+std::to_string(power+1);
					}
					else {
						return answer = answer + "/2" + variable + "^2";
					}
				}
			}
		}
	
	}

	string integrate(char* integrand, char variable) {
		return integrate1(integrand, variable) + "+" + "C";
	}
	

};

#endif // !INTEGRATOR.H
