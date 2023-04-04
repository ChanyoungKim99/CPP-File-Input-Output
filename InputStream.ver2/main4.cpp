#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;
public:
	Monster() : mName{}, mLevel{}, mHP{}, mMP{}
	{
	}
	Monster(std::string name, int level, int hp, int mp) : mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp }
	{
	}
	friend std::istream& operator >>(std::istream& inputStream, Monster& monster);	// 연산자 오버로딩
};

std::istream& operator >>(std::istream& inputStream, Monster& monster)
{
	std::string buffer;
	try
	{
		std::getline(inputStream, buffer, ',');
		monster.mName = buffer;
		std::getline(inputStream, buffer, ',');
		monster.mLevel = std::stoi(buffer);
		std::getline(inputStream, buffer, ',');
		monster.mHP = std::stoi(buffer);
		std::getline(inputStream, buffer);			// 여기는 ',' 없음!
		monster.mMP = std::stoi(buffer);
	}
	catch (std::exception e)
	{
		std::cerr << "데이터 형식이 잘못 되었습니다.\n";
	}
	return inputStream;
}

bool CreateFromFile(const char* filename, std::vector<Monster>& vector)
{
	std::ifstream ist;
	// 로직적인 예외는 직접 처리하므로, badbit만 처리했습니다.

	ist.exceptions(std::istream::badbit);

	try
	{
		ist.open(filename);

		std::string buffer;
		std::vector<std::string> argVector;

		// 헤더를 읽어 옵니다.
		std::getline(ist, buffer);

		while (!ist.eof())
		{
			// 다음 읽어 올 것이 EOF면 무시합니다.
			if (ist.peek() == EOF)			// EOF = End Of File
			{
				break;
			}

			Monster monster;
			ist >> monster;			// 입력 스트림에서 monster 객체 하나를 가져오는 표기법
			vector.push_back(monster);
		}
		ist.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "파일 연산 도중 예외가 발생했습니다.\n" << e.what() << std::endl;
		ist.close();
		return false;
	}
	return true;
}

int main()
{
	std::vector<Monster> monsterList;
	CreateFromFile("Data/SimpleData.txt", monsterList);
}

