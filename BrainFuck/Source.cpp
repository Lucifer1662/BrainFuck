#include <string>
#include <vector>
#include <iostream>
#include <fstream>

int brackets(const std::string& program, std::vector<int>& goTo, const int initial) {
	for(int i = initial; i < program.size(); i++)
	{
		switch (program[i])	{
			case '[': {
				int result = brackets(program, goTo, i + 1);
				goTo[i] = result;
				i = result;
				break;
			}
			case ']': {
				if (goTo[i] == -1)
					goTo[i] = initial - 1;
				return i;
				break;
			}
		}
	}


}

void BrainFuck(const std::string& program, int maxOutPut = -1) {
	int outputCount = 0;
	int dataPtr = 0;
	int instructionPtr = 0;
	std::vector<char> data = {};

	auto goTo = std::vector<int>(program.size());
	for (auto& index : goTo)
		index = -1;

	brackets(program, goTo, 0);

	while (instructionPtr < program.size()) {
		if (dataPtr >= data.size())
			data.resize((dataPtr + 1) * 2);
		switch (program[instructionPtr]) {
		case '>': {
			dataPtr++;
			break;
		}
		case '<': {
			dataPtr--;
			break;
		}
		case '+': {
			data[dataPtr]++;
			break;
		}
		case '-': {
			data[dataPtr]--;
			break;
		}
		case '.': {
			std::cout << data[dataPtr];
			outputCount++;
			break;
		}
		case ',': {
			std::cin >> data[dataPtr];
			break;
		}
		case '[': {
			if (data[dataPtr] == 0) {
				instructionPtr = goTo[instructionPtr];
			}
			break;
		}
		case ']': {
			if (data[dataPtr] != 0) {
				instructionPtr = goTo[instructionPtr];
			}
			break;
		}
		}
		instructionPtr++;
		if (maxOutPut != -1 && outputCount > maxOutPut)
			return;
	}
}

void main(int argn, char** argv) {
	for (size_t i = 1; i < argn; i++)
	{
		std::ifstream file;
		std::string program;
		file.open(argv[i]);
		std::string line;
		while (std::getline(file, line))
		{
			program += line;
		}
		file.close();
		std::cout << argv[i] << std::endl;

		if (i + 2 < argn && strcmp(argv[i + 1], "-limit") == 0) {
			int maxCharacters = std::stoi(argv[i + 2]);
			std::cout << "Max Characters " << maxCharacters << std::endl;
			BrainFuck(program, maxCharacters);
			i += 2;
		}
		else {
			BrainFuck(program);
		}
		std::cout << std::endl;
	}
}
