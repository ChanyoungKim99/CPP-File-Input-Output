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
	friend std::istream& operator >>(std::istream& inputStream, Monster& monster);
	friend std::ostream& operator <<(std::ostream& ostream, Monster& monster);
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
std::ostream& operator <<(std::ostream& ostream, Monster& monster)
{
	try
	{
		ostream << monster.mName << ","
			<< monster.mLevel << ","
			<< monster.mHP << ","
			<< monster.mMP << std::endl;
	}
	catch (std::exception e)
	{
		std::cerr << "��Ʈ���� �� �� ������ �߻��߽��ϴ�.\n";
	}
	return ostream;
}
bool CreateFromFile(const char* filename, std::vector<Monster>& vector)
{
	std::ifstream ist;

	ist.exceptions(std::istream::badbit);

	try
	{
		ist.open(filename);

		std::string buffer;
		std::vector<std::string> argVector;

		std::getline(ist, buffer);

		while (!ist.eof())
		{
			if (ist.peek() == EOF)			
			{
				break;
			}

			Monster monster;
			ist >> monster;			
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
bool WriteToFile(const char* filename, std::vector<Monster>& vector)
{
	std::ofstream ost;
	ost.exceptions(std::ostream::badbit);
	try
	{
		ost.open(filename);
		// ���
		ost << "--- MONSTER DATA ---\n";
		for (auto monster : vector)
		{
			ost << monster;
		}
		ost.close();
	}
	catch (std::ofstream::failure e)
	{
		std::cerr << "���� ���� ���� ���ܰ� �߻��߽��ϴ�.\n" << e.what() << std::endl;
		ost.close();
		return false;
	}
	return true;
}
int main()
{
	std::vector<Monster> monsterList;	
	CreateFromFile("Data/SimpleData.txt", monsterList);
	WriteToFile("Data/SimpleData.txt", monsterList);
}
// �̷� ���� �б� ���� �ڵ�� csv����(comma seperated values ��ǥ�� ���е� ����) ���� �����͸� �ű�� ���� ���� ����̴�!