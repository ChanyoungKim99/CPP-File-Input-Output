#pragma once
#include <fstream>
#include <string>

class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;
public:
	Monster() : mName{}, mLevel{}, mHP{}, mMP{} {}
	Monster(std::string name, int level, int hp, int mp) :
		mName{ name },
		mLevel{ level },
		mHP {hp},
		mMP {mp}
	{}
	std::ifstream& ReadBinary(std::ifstream& istream);
	std::ofstream& WriteBinary(std::ofstream& ostream);
};

// static_cast =  C의 typecast  = static + 엄격한 규칙 [Run time]
// dynamic_cast = 다형성에 사용됨 [Compile Time]
// reinterpret_cast = 규칙없는 자유로운 형변환 + 결과 책임지지 않음

std::ifstream& Monster::ReadBinary(std::ifstream& istream)
{
	// 바이너리는 텍스트와 다르게 구분자가 없으므로 문자열의 길이를 따로 저장
	int strLen{};

	// 바이너리 데이터를 읽거나 쓰기 위해서는 char*로 변환하는 것이 기본
	istream.read(reinterpret_cast<char*>(&strLen), sizeof(int));
	mName.resize(strLen);
	istream.read(&mName[0], strLen);	    // Write와 다르게 읽어오므로 c_str 사용 불가능
	istream.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
	istream.read(reinterpret_cast<char*>(&mHP), sizeof(int));
	istream.read(reinterpret_cast<char*>(&mMP), sizeof(int));
	return istream;
}		

std::ofstream& Monster::WriteBinary(std::ofstream& ostream)
{
	int strLen = static_cast<int>(mName.size());
	ostream.write(reinterpret_cast<char*>(&strLen), sizeof(int));
	ostream.write(mName.c_str(), strLen);	// c_str = const 형의 멤버함수
	ostream.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ostream.write(reinterpret_cast<char*>(&mHP), sizeof(int));
	ostream.write(reinterpret_cast<char*>(&mMP), sizeof(int));
	return ostream;
}

// 스트림 연산자 오버로딩
// 친구가 아닌 이유는 멤버 함수를 각각 준비해 뒀기 떄문
// 필요에 따라 ReadBinary, ReadText 등으로 변경해서 사용 가능
std::ifstream& operator >>(std::ifstream& istream, Monster& monster)
{
	return monster.ReadBinary(istream);
}
std::ofstream& operator <<(std::ofstream& ostream, Monster& monster)
{
	return monster.WriteBinary(ostream);
}