#include "Monster.h"
#include <vector>
#include <fstream>
#include <iostream>

// 헤더 파일
// 주로 버전과 아이템의 갯수를 미리 파일에 저장해 줍니다
struct Header 
{
	int version{ 1 };
	int itemCount{};
};	// 헤더에 POD (Plain Old Data) 사용 [객체 지향 특성이 없고 비트 단위 연산이 가능]
 
bool SaveToFile(const char* filename, std::vector<Monster>& monsters)
{
	std::ofstream ostream;			
	ostream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		ostream.open(filename, std::ofstream::binary);
		// 헤더 쓰기
		Header header{ 1, static_cast<int>(monsters.size()) };
		ostream.write(reinterpret_cast<char*>(&header), sizeof(Header));	// 스트림에 기록
		// header 구조체의 주소를 char*로 변경
		// & (reference type)<참조형 변수> 는 주소(메모리)를 전달 = 직접적인 값 복사 X

		for (auto item : monsters)
		{
			ostream << item;
		}
		ostream.close();
	}
	catch (std::ofstream::failure e)
	{
		std::cerr << "파일 저장 중에 예외가 발생했습니다.\n" << e.what() << std::endl;
		ostream.close();
		return false;
	}
	return true;
}

bool LoadFromFile(const char* filename, std::vector<Monster>& monsters)
{
	std::ifstream istream;		
	istream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		istream.open(filename, std::ifstream::binary);		// 텍스트 형태가 아닌 바이너리 데이터로 접근
		// 헤더 읽기
		Header header;
		istream.read(reinterpret_cast<char*>(&header), sizeof(Header));		// 스트림에서 읽어옴
		for (int i = 0; i < header.itemCount; i++)
		{
			Monster monster;
			istream >> monster;
			monsters.push_back(monster);
		}
		istream.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "파일 저장 중에 예외가 발생했습니다.\n" << e.what() << std::endl;
		istream.close();
		return false;
	}
	return true;
}

int main()
{
	std::vector<Monster> monsterList;
	monsterList.push_back(Monster{ "JELLY", 1, 1, 1 });
	monsterList.push_back(Monster{ "WOLF", 5, 5, 5 });
	monsterList.push_back(Monster{ "DEMON", 10, 10, 10 });
	SaveToFile("Data/SimpleData.dat", monsterList);
	monsterList.clear();
	LoadFromFile("Data/SimpleData.dat", monsterList);
}

