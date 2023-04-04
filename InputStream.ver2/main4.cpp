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
	friend std::istream& operator >>(std::istream& inputStream, Monster& monster);	// ������ �����ε�
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
		std::getline(inputStream, buffer);			// ����� ',' ����!
		monster.mMP = std::stoi(buffer);
	}
	catch (std::exception e)
	{
		std::cerr << "������ ������ �߸� �Ǿ����ϴ�.\n";
	}
	return inputStream;
}

bool CreateFromFile(const char* filename, std::vector<Monster>& vector)
{
	std::ifstream ist;
	// �������� ���ܴ� ���� ó���ϹǷ�, badbit�� ó���߽��ϴ�.

	ist.exceptions(std::istream::badbit);

	try
	{
		ist.open(filename);

		std::string buffer;
		std::vector<std::string> argVector;

		// ����� �о� �ɴϴ�.
		std::getline(ist, buffer);

		while (!ist.eof())
		{
			// ���� �о� �� ���� EOF�� �����մϴ�.
			if (ist.peek() == EOF)			// EOF = End Of File
			{
				break;
			}

			Monster monster;
			ist >> monster;			// �Է� ��Ʈ������ monster ��ü �ϳ��� �������� ǥ���
			vector.push_back(monster);
		}
		ist.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "���� ���� ���� ���ܰ� �߻��߽��ϴ�.\n" << e.what() << std::endl;
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

