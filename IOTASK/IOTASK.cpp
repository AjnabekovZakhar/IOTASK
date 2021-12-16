
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>

int main()
{
	std::vector<std::string> names;
	std::vector<std::vector<double>> values;
	std::vector<double> temp_values;
	std::string input_str,temp_str;

	//test - Correct
	//test1 - Couldn't open file
	//test2 - Wrong number of items in row(one is missing)
	//test3 - Wrong number of items in row(4 extra elements)
	//test4 - stod exception

	std::ifstream input_file("test.txt");


	try {
		if (!input_file.is_open()) {
			throw std::runtime_error("Couldn't open file");
		}

		std::getline(input_file, input_str);

		std::stringstream ss;

		ss.str(input_str);
		while (std::getline(ss, temp_str, '\t')) {
			names.push_back(temp_str);
		}

		while (std::getline(input_file, input_str)) {
			ss.clear();
			ss.str(input_str);
			temp_str.clear();
			try {
				while (std::getline(ss, temp_str, '\t')) {
					temp_values.push_back(stod(temp_str));
				}
			}
			catch (const std::invalid_argument& exept) {
				throw std::invalid_argument("Row number  " + std::to_string(values.size() + 1) + " is containing non-double item in colunm number "+std::to_string(temp_values.size()+1));
			}
			
			if (temp_values.size() < names.size())
				throw std::length_error("Row number "+std::to_string(values.size() + 1)+ " is missing " +std::to_string( names.size() - temp_values.size() )+ " item(s) ");
			if (temp_values.size() > names.size())
				throw std::length_error("Row number " + std::to_string(values.size() + 1) + " is containing " + std::to_string(temp_values.size() - names.size()) + " extra item(s) ");
		
			values.push_back(temp_values);
			temp_values.clear();
		}
		for (int i = 0; i < names.size(); ++i)
			std::cout << names[i] << '\t';
		std::cout << std::endl;


		for (int i = 0; i < values.size(); ++i) {
			for (int j = 0; j < values[i].size(); ++j)
				std::cout << values[i][j] << '\t';
			std::cout << std::endl;
		}
	}
	catch (const std::exception& exept) {
		std::cout << "Exception: "<< ' ' << exept.what() << std::endl;
	}

	return 0;
}

