
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>

void split(const std::string& s, char delim, std::vector<std::string>& elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}
void split_to_double(const std::string& s, char delim, std::vector<double>& elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(stod(item));
	}
}
int main()
{
	std::vector<std::string> names;
	std::vector<std::vector<double>> values;
	std::vector<double> temp_values;
	std::string input_str,temp_str;

	setlocale(LC_ALL, "Russian");
	//�������� ����, ���� �������� ������� ����, �� stod ����� ������������ ',' ��� �����������, � �� '.'
	std::ifstream input_file("test.txt");
	try {
		if (!input_file.is_open()) {
			throw std::runtime_error("�� ���� ������� ����");
		}

		std::getline(input_file, input_str);

		split(input_str, '\t', names);

		while (std::getline(input_file, input_str)) {
			split_to_double(input_str, '\t',temp_values);
			if(temp_values.size()!=names.size())
				throw std::length_error("- ������ � ������������ ����������� ���������");
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
	catch (const std::runtime_error& exept) {
		std::cout << "����������: " << values.size() + 1 << ' ' << exept.what() << std::endl;
	}
	catch(const std::invalid_argument& exept){//��� stod
		std::cout << "����������: " << values.size() + 1 << ' ' << exept.what() << std::endl;
	}
	catch (const std::length_error& exept) {
		std::cout << "����������: " <<values.size()+1 <<' '<< exept.what() << std::endl;
	}
	return 0;
}

