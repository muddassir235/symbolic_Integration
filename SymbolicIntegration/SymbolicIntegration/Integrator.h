#include<string>
#include<iostream>
#include<math.h>

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

using namespace std;

class Integrator
{
private:
	char variable;
public:

	Integrator(char variable) {
		this->variable = variable;
	}
	~Integrator() {}
	string integrate1(char* integrand)
	{
		char* _thisIntegrand = integrand;
		//initialize answer as an empty string
		string answer = "";

		//there is a constant a the beginning of the integrand then 
		if (isANumber(_thisIntegrand[0]) || isAnAlphabet(_thisIntegrand[0])) {

			// the index after the constant ends
			int endOfConstant = 0;
			string constantString = "";
			
			//until the constant ends append it the the answer
			for (int i = 0; isANumber(_thisIntegrand[i]) || isAnAlphabet(_thisIntegrand[i]); i++) {
				constantString = constantString + _thisIntegrand[i];
				endOfConstant = i;
			}
			char* constant = getCharArrayFromString(constantString);
			//whether the constant contains any sort of Trignometric exponential or logrithmic function symobol
			if (containsTrigExpLog(constant)) {
				//if the constant string start from the function
				if (startingIndexTrigExpLog(constant) == 0) {
					//if the constant string contains only the function and nothing else
					if (endingIndexTrigExpLog(constant) == (strlen(constant) - 1)) {
						//set the function equal to the constant string
						string function =constantString;
						//if we have a sin funtion on our hands and the character after the function is the variable itself
						if (function == "sin"&&(_thisIntegrand[endOfConstant+1]==variable)) {
							//if after the variable the integrand ends or there is a plus or minus sign after the variable
							if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))||(_thisIntegrand[endOfConstant+2]=='+'||_thisIntegrand[endOfConstant+2]=='-')) {
								//if after the variable the integrand ends
								if (((strlen(_thisIntegrand) - 1) == (endOfConstant + 1))) {
									return answer = answer + "-" + "cos" + variable;
								}//if after the variable we have a plus or minus sign
								else {
									//integrating the sin function and appending the plus or minus symbol after it
									answer = answer + "-" + "cos" + variable+_thisIntegrand[endOfConstant+2];
									int indexIntegrand = 0;
									char* newIntegrand = new char[strlen(_thisIntegrand)-endOfConstant+1];
									for (int i = endOfConstant + 3;i < strlen(_thisIntegrand);i++) {
										newIntegrand[indexIntegrand] = _thisIntegrand[i];
										indexIntegrand++;
									}
									newIntegrand[indexIntegrand] = '\0';
									//made a new integrand containg all the characters after the plus or minus sign
									_thisIntegrand = newIntegrand;
									//append the integral of this new integrand into the answer
									return answer = answer + integrate1(_thisIntegrand);
								}
							}
						}
					}
					else {
						//handle this case later $$$$$$$$$$$$$$$$
					}
				}
				else {
					int start = startingIndexTrigExpLog(constant);
					for (int i = 0;i < start;i++) {
						answer = answer + constant[i];
					}
					char* function = "";
					for (int i = start;i < strlen(constant);i++) {
						function = function + constant[i];
					}
					if (endingIndexTrigExpLog(constant) == (strlen(constant) - 1)) {

					}
					else {
						//handle this case later $$$$$$$$$$$$$$$$$$$$
					}
				}
			}// if the constant doesn't contain any Trg, exp, or logrithmic function
			else {
				//append the constant in the answer
				answer = answer + constant;

				//if the constant is not the end of the integrand
				if (endOfConstant != (strlen(_thisIntegrand) - 1)) {

					//integrand should be changed to a new integrand without the constant
					int indexIntegrand = 0;
					char* newIntegrand = new char[strlen(_thisIntegrand) - endOfConstant - 1];
					for (int i = endOfConstant + 1;i < strlen(_thisIntegrand);i++) {
						newIntegrand[indexIntegrand] = _thisIntegrand[i];
						indexIntegrand++;
					}
					newIntegrand[indexIntegrand] = '\0';
					
					//made a new integrand with the constant excluded
					_thisIntegrand = newIntegrand;

					//append the result of the new integrand's integration into the answer
					return answer = answer + integrate1(_thisIntegrand);

				}//if the constant is the end of the integrand
				else {
					//append the variable at the end of the answer and we're done
					return answer = answer + variable;

				}
			}
		}

		//a boolean to check whether the string contain an addition or subtration operator
		bool containsPlusOrMinus = false;

		//loop that traverses the integrand character by character
		for (int i = 0;i < strlen(_thisIntegrand);i++) {
			//if we encounter a plus or a minus 
			if ((_thisIntegrand[i] == '+' || _thisIntegrand[i] == '-') && (_thisIntegrand[i - 1] != '^')) {
				containsPlusOrMinus = true;
				//a string that stores the characters before the + or - sign
				char* _integrandPart = new char[i];
				int indexIntegrand = 0;
				//storing the character before the + or - sign in the _integrandPart string
				for (int j = 0; j < i;j++) {
					_integrandPart[j] = _thisIntegrand[j];
					indexIntegrand++;
				}
				_integrandPart[indexIntegrand] = '\0';
				//appending the integration of the _integrandPart string into the answer
				answer = answer + integrate1(_integrandPart);

				//appending the + or - symbol into the answer
				answer = answer + _thisIntegrand[i];

				//replacing the integrand string with a new string that contains only the characters after the + or - symbol
				indexIntegrand = 0;
				char* newIntegrand = new char[strlen(_thisIntegrand) - i - 1];
				for (int j = i + 1;j < strlen(_thisIntegrand); j++) {
					newIntegrand[indexIntegrand] = _thisIntegrand[j];
					indexIntegrand++;
				}
				newIntegrand[indexIntegrand] = '\0';
				_thisIntegrand = newIntegrand;
				//append the answer with integation of the new intergrand
				return answer = answer + integrate1(_thisIntegrand);
			}
		}

		//if the string doesn't contain any more plus or minus operators
		if (containsPlusOrMinus == false) {
			if (!containsProductOfFunctions(_thisIntegrand)) {
				if (_thisIntegrand[0] == variable&&_thisIntegrand[1] == '^') {
					return answer = answer + integratePolynomial(_thisIntegrand);
				}//if the integrand is just the variable
				else if ((strlen(_thisIntegrand) == 1) && (_thisIntegrand[0] == variable)) {
					return answer = answer + "/2" + variable + "^" + "2";
				}
			}


		}

	}

	//If the said integrand is a polynomial (GOOD)
	string integratePolynomial(char* integrand) {
		string answer = "";
		//iterating from the start to the end of the string
		for (int i = 0;i < strlen(integrand); i++) {

			//when we encounter the variable
			if (integrand[i] == variable) {

				//if the next is the raised to the power " ^ " operator ? ? 
				if (integrand[i + 1] == '^') {

					string power = getPower(integrand);

					//if the power contains the variable itself
					if (power == "Not Integrable") {

						return power;

					}//if the power is not just numbers or just constants
					else if (power == "is Currently Not Integrable") {

						return power;

					}//if the power contains "just numbers"! or "just constants"!
					else {
						//if the power contains just numbers
						if (power[0] == '#') {
							if (power[1] == '-') {
								if (getNumber(power) != 1) {
									return answer = answer + "/" + "-" + std::to_string(getNumber(power) - 1) + variable + "^" + "-" + std::to_string(getNumber(power) - 1);
								}
								else {
									return answer = answer + "ln" + variable;
								}
							}
							else {
								return answer = answer + "/" + std::to_string(getNumber(power) + 1) + variable + "^" + std::to_string(getNumber(power) + 1);
							}
						}//if the power contains just constants
						else {
							return answer = answer + "/" + '(' + power + '+' + '1' + ')' + variable + "^" + '(' + power + "+" + "1" + ')';
						}
					}
				}//if there was no raised to the power operator " ^ " after the variable
				else {
					return answer = answer + "/2" + variable + "^2";
				}
			}
		}
	}

	//In order to add a constant " C " at the end of the answer
	string integrate(char* integrand) {
		return integrate1(integrand) + "+" + "C";
	}

	//get the power of the variable form the polynomial integarnd (GOOD)
	string getPower(char* integrand) {
		int start = 0;

		for (int i = 0; i < strlen(integrand);i++) {
			bool isJustANumber = true;
			bool isJustAlphabets = true;
			if (integrand[i] == '^'&&integrand[i - 1] == variable) {
				for (int c = i + 1;c < strlen(integrand);c++) {
					if (integrand[c] == variable) {

						return "Not Integrable";

					}
					else if (!isANumber(integrand[c])) {
						if (c == (i + 1)) {
							if (integrand[c] == '+' || integrand[c] == '-') {
								//do nothing
							}
							else {
								isJustANumber = false;
							}
						}
						else {
							isJustANumber = false;
						}
					}
					else if (!isAnAlphabet(integrand[c])) {
						if (c == (i + 1)) {
							if (integrand[c] == '+' || integrand[c] == '-') {
								//do nothing
							}
							else {
								isJustAlphabets = false;
							}
						}
						else {
							isJustAlphabets = false;
						}
					}
				}
			}
			if (isJustANumber) {
				if (integrand[i] == '^'&&integrand[i - 1] == variable&&isANumber(integrand[i + 1])) {
					start = i + 1;
					int lengthOfConstant = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						lengthOfConstant++;
					}
					int power = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						power = power + (integrand[j] - '0')*pow(10, lengthOfConstant - j + start - 1);
					}
					return "#" + std::to_string(power);
				}
				else if (integrand[i] == '^'&&integrand[i - 1] == variable&&integrand[i + 1] == '+') {
					start = i + 2;


					int lengthOfConstant = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						lengthOfConstant++;
					}
					int power = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						power = power + (integrand[j] - '0')*pow(10, lengthOfConstant - j + start - 1);
					}
					return "#" + std::to_string(power);
				}
				else if (integrand[i] == '^'&&integrand[i - 1] == variable && integrand[i + 1] == '-') {
					start = i + 2;

					int lengthOfConstant = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						lengthOfConstant++;
					}
					int power = 0;
					for (int j = start; isANumber(integrand[j]);j++) {
						power = power + (integrand[j] - '0')*pow(10, lengthOfConstant - j + start - 1);
					}
					return "#" + std::to_string(-1 * power);
				}
			}
			else if (isJustAlphabets) {
				if (isAnAlphabet(integrand[i + 1]) && integrand[i] == '^'&&integrand[i - 1] == variable) {
					start = i + 1;

					string power = "";
					for (int j = start;isAnAlphabet(integrand[j]);j++) {
						power = power + integrand[j];
					}
					return power;
				}
				else if (integrand[i + 1] == '+'&&integrand[i] == '^'&&integrand[i - 1] == variable) {
					start = i + 2;

					string power = "";
					for (int j = start;isAnAlphabet(integrand[j]);j++) {
						power = power + integrand[j];
					}
					return power;
				}
				else if (integrand[i + 1] == '-'&&integrand[i] == '^'&&integrand[i - 1] == variable) {
					start = i + 1;

					string power = "";
					for (int j = start;j < strlen(integrand);j++) {
						power = power + integrand[j];
					}
					return power;
				}
			}// if the power is not just alphabets or just numbers but is a complicated power
			else {
				//make this function later
				return "is Currently Not Integrable";
			}


		}
	}

	//get the magnitude of the power from the power string (GOOD)
	int getNumber(string power) {
		int number = 0;
		int length = 0;
		for (int i = 0;power[i] != '\0';i++) {
			length++;
		}
		if (power[1] == '-') {
			for (int i = 2;i < length;i++) {
				number = number + (power[i] - '0') * pow(10, length - i - 1);
			}
			return number;
		}
		else {
			for (int i = 1;i < length;i++) {
				number = number + (power[i] - '0')*pow(10, length - i - 1);
			}
			return number;
		}
	}

	//check whether the character is a number or not (GOOD)
	bool isANumber(char x) {
		if (x >= '0'&&x <= '9') {
			return true;
		}
		else {
			return false;
		}
	}

	//check whether the charachter is an alphabet or not (GOOD)
	bool isAnAlphabet(char x) {
		if (((x >= 'a'&&x <= 'z') || (x >= 'A'&&x <= 'Z')) && x != variable) {
			return true;
		}
		else {
			return false;
		}
	}

	//does the the given integrand contain a product of functions of the variable (GOOD UPTIL NOW)
	bool containsProductOfFunctions(char* integrand) {
		int ocuuranceOfVar = 0;
		int occuranceProductSymbol = 0;
		bool containsPowerOperator = false;
		for (int i = 0;i < strlen(integrand);i++) {
			if (integrand[i] == variable) {
				ocuuranceOfVar++;
			}
			if (integrand[i] == '*') {
				occuranceProductSymbol++;
			}
			if (integrand[i] == '^') {
				containsPowerOperator = true;
			}
		}
		if (ocuuranceOfVar <= 1) {
			return false;
		}
		else {
			if (occuranceProductSymbol == 0) {
				return false;
			}
			else {
				if (ocuuranceOfVar == 2 && occuranceProductSymbol == 1 && !containsPowerOperator) {
					int productIndex = 0;
					bool isAProduct = false;
					for (int i = 0;i < strlen(integrand);i++)
					{
						if (integrand[i] == '*') {
							productIndex = i;
						}
					}
					for (int i = 0;i < productIndex;i++) {
						if (integrand[i] == variable) {
							isAProduct = true;
						}
					}
					if (isAProduct) {
						isAProduct = false;
						for (int i = productIndex + 1;i < strlen(integrand);i++) {
							if (integrand[i] == variable) {
								isAProduct = true;
							}
						}
					}
					return isAProduct;

				}
				else if (ocuuranceOfVar == 2 && occuranceProductSymbol == 1) {
					int powerIndex = 0;
					int productIndex = 0;
					bool isAProduct = false;
					for (int i = 0;i < strlen(integrand);i++) {
						if (integrand[i] == '*') {
							productIndex = i;
						}
						else if (integrand[i] == '^') {
							powerIndex = i;
						}
					}
					for (int i = 0;i < productIndex;i++) {
						if (integrand[i] == variable) {
							isAProduct = true;
						}
					}
					if (isAProduct) {
						isAProduct = false;
						for (int i = productIndex + 1;i < strlen(integrand);i++) {
							if (integrand[i] == variable) {
								isAProduct = true;
							}
						}
					}
					if (isAProduct) {
						for (int i = powerIndex + 1;i < strlen(integrand);i++) {
							if (integrand[i] == variable) {
								isAProduct = false;
							}
						}
					}
					return isAProduct;
				}
				else {
					//work on this needs to be done
					return true;
				}
			}
		}
	}

	//does the constant contain the string "str" (GOOD)
	bool itContains(char* constant, char* str) {
		if (strlen(constant) < strlen(str)) { return false; }
		for (int i = 0;i <= (strlen(constant) - strlen(str));i++) {
			bool contains = true;
			for (int j = i;j < (strlen(str) + i);j++) {
				if (constant[j] != str[j - i]) {
					contains = false;
				}
			}
			if (contains) {
				return true;
			}
		}
		return false;
	}
	
	//starting index of the string "str" (GOOD)
	int startIndexOf(char* constant, char* str) {
		if (itContains(constant, str)) {
			for (int i = 0;i <= (strlen(constant) - strlen(str));i++) {
				bool starts = true;
				for (int j = i;j < (strlen(str) + i);j++) {
					if (constant[j] != str[j - i]) {
						starts = false;
					}
				}
				if (starts) {
					return i;
				}
			}
		}
		else {
			return -1;
		}
	}

	//ending index of the string "str" (GOOD)
	int endIndexOf(char* constant, char* str) {
		if (itContains(constant, str)) {
			for (int i = 0;i <= (strlen(constant) - strlen(str));i++) {
				bool ends = true;
				for (int j = i;j < (strlen(str) + i);j++) {
					if (constant[j] != str[j - i]) {
						ends = false;
					}
				}
				if (ends) {
					return i + strlen(str) - 1;
				}
			}
		}
		else {
			return -1;
		}
	}
	
	//does the constant contain any trig exponential or log functions (GOOD)
	bool containsTrigExpLog(char* constant) {
		return itContains(constant, "sin") || itContains(constant, "cos") || itContains(constant, "tan")
			|| itContains(constant, "cosec") || itContains(constant, "sec") || itContains(constant, "cot")
			|| itContains(constant, "e") || itContains(constant, "ln") || itContains(constant, "log")
			|| itContains(constant, "logbase");
	}

	//starting index of the trig exponential or log function (GOOD)
	int startingIndexTrigExpLog(char* constant) {
		if (itContains(constant, "sin")) {
			return startIndexOf(constant, "sin");
		}
		else if (itContains(constant, "cos")) {
			return startIndexOf(constant, "cos");
		}
		else if (itContains(constant, "tan")) {
			return startIndexOf(constant, "tan");
		}
		else if (itContains(constant, "cosec")) {
			return startIndexOf(constant, "cosec");
		}
		else if (itContains(constant, "sec")) {
			return startIndexOf(constant, "sec");
		}
		else if (itContains(constant, "cot")) {
			return startIndexOf(constant, "cot");
		}
		else if (itContains(constant, "e")) {
			return startIndexOf(constant, "e");
		}
		else if (itContains(constant, "ln")) {
			return startIndexOf(constant, "ln");
		}
		else if (itContains(constant, "log")) {
			return startIndexOf(constant, "log");
		}
		else if (itContains(constant, "logbase") ){
			return startIndexOf(constant, "logbase");
		}
		else {
			return -1;
		}
	}

	//ending index of the trig exponential or log function (GOOD)
	int endingIndexTrigExpLog(char* constant) {
		if (itContains(constant, "sin")) {
			return endIndexOf(constant, "sin");
		}
		else if (itContains(constant, "cos")) {
			return endIndexOf(constant, "cos");
		}
		else if (itContains(constant, "tan")) {
			return endIndexOf(constant, "tan");
		}
		else if (itContains(constant, "cosec")) {
			return endIndexOf(constant, "cosec");
		}
		else if (itContains(constant, "sec")) {
			return endIndexOf(constant, "sec");
		}
		else if (itContains(constant, "cot")) {
			return endIndexOf(constant, "cot");
		}
		else if (itContains(constant, "e")) {
			return endIndexOf(constant, "e");
		}
		else if (itContains(constant, "ln")) {
			return endIndexOf(constant, "ln");
		}
		else if (itContains(constant, "log")) {
			return endIndexOf(constant, "log");
		}
		else if (itContains(constant, "logbase") ){
			return endIndexOf(constant, "logbase");
		}
		else {
			return -1;
		}
	}

	//get a character array from a String (GOOD)
	char* getCharArrayFromString(string s) {
		int length = 0;
		for (int i = 0;(s[i] != '\0');i++) {
			length++;
		}
		char* cArray = new char[length];
		for (int i = 0;i < length;i++) {
			cArray[i] = s[i];
		}
		cArray[length] = '\0';
		return cArray;
	}

};

#endif // !INTEGRATOR.H
