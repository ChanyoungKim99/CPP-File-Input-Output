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
			// 파일의 끝까지 한 줄씩 읽어 옵니다.
			std::getline(ist, buffer);
			// 우리의 양식은 4개의 데이터가 쉼표로 구분되어 있습니다.
			// 이 조건을 검사해서 데이터가 정상인지 확인합니다.
			if (std::count(buffer.begin(), buffer.end(), ',') == 3)
			{
				std::stringstream ss(buffer);
				for (int i = 0; i < 4; i++)
				{
					std::string token;

					// ,를 만나면 거기까지만 반환합니다.
					std::getline(ss, token, ',');
					// 읽어온 토큰을 벡터에 임시 저장
					argVector.push_back(token);
				}

				vector.push_back ( Monster {
					argVector[0],
					std::stoi(argVector[1]),
					std::stoi(argVector[2]),
					std::stoi(argVector[3]) } );
				
				// 매개변수 벡터 초기화
				argVector.clear();
			}
			else
			{
				if (buffer.length() != 0)
				{
					std::cerr << "몬스터 데이터 양식이 잘못되었습니다.\n";
				}
			}
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