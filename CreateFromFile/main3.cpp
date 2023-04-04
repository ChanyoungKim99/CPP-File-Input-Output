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
	Monster(std::string name, int level, int hp, int mp) : mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp }
	{
	}
};

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
			// ������ ������ �� �پ� �о� �ɴϴ�.
			std::getline(ist, buffer);
			// �츮�� ����� 4���� �����Ͱ� ��ǥ�� ���еǾ� �ֽ��ϴ�.
			// �� ������ �˻��ؼ� �����Ͱ� �������� Ȯ���մϴ�.
			if (std::count(buffer.begin(), buffer.end(), ',') == 3)
			{
				std::stringstream ss(buffer);
				for (int i = 0; i < 4; i++)
				{
					std::string token;

					// ,�� ������ �ű������ ��ȯ�մϴ�.
					std::getline(ss, token, ',');
					// �о�� ��ū�� ���Ϳ� �ӽ� ����
					argVector.push_back(token);
				}

				vector.push_back ( Monster {
					argVector[0],
					std::stoi(argVector[1]),
					std::stoi(argVector[2]),
					std::stoi(argVector[3]) } );
				
				// �Ű����� ���� �ʱ�ȭ
				argVector.clear();
			}
			else
			{
				if (buffer.length() != 0)
				{
					std::cerr << "���� ������ ����� �߸��Ǿ����ϴ�.\n";
				}
			}
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