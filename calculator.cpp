#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <queue>
#include <tuple>
#include <stack>
#include <string>
#include <locale>

int main(int argc, char* argv[]) {

	// setup the print out format for the precision required.
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(3);

	// open the file for reading
	std::ifstream in;
	in.open(argv[1]);

	// string to be read into
	std::string s;

	//initialise empty stack
	std::stack<std::tuple<double, bool>> st;

	// read the file while we have input.
	while (in >> s) {

		//setup variables to use if digit
		double a;
		std::tuple<double, bool> t;
		std::locale loc;

		//if the number is a double
		if (s.find('.') != std::string::npos) {
			a = std::stod(s);
			t = std::make_tuple(a, true);
			st.push(t);
		}

		//if it is a digit
		else if (std::isdigit(s[0], loc)) {
			a = std::stod(s);
			t = std::make_tuple(a, false);
			st.push(t);
		}

		//otherwise it's a command
		else {
			std::tuple<double, bool> temp, temp2, answer;
			std::string sign;
			if (s.compare("add") == 0) {
				sign = " + ";

				//pulls last 2 values off the stack
				temp = st.top();
				st.pop();
				temp2 = st.top();
				st.pop();

				//makes new tuple
				answer = std::make_tuple(0, false);

				//gives value to the answer
				std::get<0>(answer) = std::get<0>(temp2) + std::get<0>(temp);

				//if either of them are doubles, then the new value must be a double
				if (std::get<1>(temp2) || std::get<1>(temp)) {
					std::get<1>(answer) = true;
				}
				else {
					std::get<0>(answer) = floor(std::get<0>(answer));
				}

				st.push(answer);
				std::cout << std::get<0>(temp2) << sign << std::get<0>(temp) << " = " << std::get<0>(answer) << std::endl;


			}
			else if (s.compare("sub") == 0) {
				sign = " - ";

				//pulls last 2 values off the stack
				temp = st.top();
				st.pop();
				temp2 = st.top();
				st.pop();

				//makes new tuple
				answer = std::make_tuple(0, false);

				//gives value to the answer
				std::get<0>(answer) = std::get<0>(temp2) - std::get<0>(temp);

				//if either of them are doubles, then the new value must be a double
				if (std::get<1>(temp2) || std::get<1>(temp)) {
					std::get<1>(answer) = true;
				}
				else {
					std::get<0>(answer) = floor(std::get<0>(answer));
				}

				st.push(answer);
				if (std::get<1>(answer) == false) {
					std::cout << std::get<0>(temp2) << sign << std::get<0>(temp) << " = " << std::get<0>(answer) << std::endl;
				}
				else {
					std::cout << std::get<0>(temp2) << sign << std::get<0>(temp) << " = " << std::get<0>(answer) << std::endl;
				}
			}
			else if (s.compare("mult") == 0) {
				sign = " * ";

				//pulls last 2 values off the stack
				temp = st.top();
				st.pop();
				temp2 = st.top();
				st.pop();

				//makes new tuple
				answer = std::make_tuple(0, false);

				//gives value to the answer
				std::get<0>(answer) = std::get<0>(temp2) * std::get<0>(temp);

				//if either of them are doubles, then the new value must be a double
				if (std::get<1>(temp2) || std::get<1>(temp)) {
					std::get<1>(answer) = true;
				}
				else {
					std::get<0>(answer) = floor(std::get<0>(answer));
				}

				st.push(answer);
				std::cout << std::get<0>(temp2) << sign << std::get<0>(temp) << " = " << std::get<0>(answer) << std::endl;
			}
			else if (s.compare("div") == 0) {
				sign = " / ";

				//pulls last 2 values off the stack
				temp = st.top();
				st.pop();
				temp2 = st.top();
				st.pop();

				//makes new tuple
				answer = std::make_tuple(0, false);

				//gives value to the answer
				std::get<0>(answer) = std::get<0>(temp2) / std::get<0>(temp);

				//if either of them are doubles, then the new value must be a double
				if (std::get<1>(temp2) || std::get<1>(temp)) {
					std::get<1>(answer) = true;
				}
				else {
					std::get<0>(answer) = floor(std::get<0>(answer));
				}

				st.push(answer);
				std::cout << std::get<0>(temp2) << sign << std::get<0>(temp) << " = " << std::get<0>(answer) << std::endl;
			}
			else if (s.compare("sqrt") == 0) {
				temp = st.top();
				st.pop();

				//makes new tuple
				answer = std::make_tuple(0, false);

				std::get<0>(answer) = sqrt(std::get<0>(temp));
				std::get<1>(answer) = std::get<1>(temp);

				if (std::get<1>(answer) == false) {
					std::get<0>(answer) = floor(std::get<0>(answer));
				}
				st.push(answer);
				std::cout << "sqrt " << std::get<0>(temp) << " = " << std::get<0>(answer) << std::endl;
			}
			else if (s.compare("pop") == 0) {
				st.pop();
			}
			else if (s.compare("reverse") == 0) {
				std::queue<std::tuple<double, bool>> reverser;
				int number = (int)std::get<0>(st.top());
				st.pop();
				for (int x = 0; x < number; x++) {
					reverser.push(st.top());
					st.pop();
				}
				for (int x = 0; x < number; x++) {
					st.push(reverser.front());
					reverser.pop();
				}
			}
		}
	}
	in.close();
	while (1 == 1) {}
}