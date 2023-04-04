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

// static_cast =  C�� typecast  = static + ������ ��Ģ [Run time]
// dynamic_cast = �������� ���� [Compile Time]
// reinterpret_cast = ��Ģ���� �����ο� ����ȯ + ��� å������ ����

std::ifstream& Monster::ReadBinary(std::ifstream& istream)
{
	// ���̳ʸ��� �ؽ�Ʈ�� �ٸ��� �����ڰ� �����Ƿ� ���ڿ��� ���̸� ���� ����
	int strLen{};

	// ���̳ʸ� �����͸� �аų� ���� ���ؼ��� char*�� ��ȯ�ϴ� ���� �⺻
	istream.read(reinterpret_cast<char*>(&strLen), sizeof(int));
	mName.resize(strLen);
	istream.read(&mName[0], strLen);	    // Write�� �ٸ��� �о���Ƿ� c_str ��� �Ұ���
	istream.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
	istream.read(reinterpret_cast<char*>(&mHP), sizeof(int));
	istream.read(reinterpret_cast<char*>(&mMP), sizeof(int));
	return istream;
}		

std::ofstream& Monster::WriteBinary(std::ofstream& ostream)
{
	int strLen = static_cast<int>(mName.size());
	ostream.write(reinterpret_cast<char*>(&strLen), sizeof(int));
	ostream.write(mName.c_str(), strLen);	// c_str = const ���� ����Լ�
	ostream.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ostream.write(reinterpret_cast<char*>(&mHP), sizeof(int));
	ostream.write(reinterpret_cast<char*>(&mMP), sizeof(int));
	return ostream;
}

// ��Ʈ�� ������ �����ε�
// ģ���� �ƴ� ������ ��� �Լ��� ���� �غ��� �ױ� ����
// �ʿ信 ���� ReadBinary, ReadText ������ �����ؼ� ��� ����
std::ifstream& operator >>(std::ifstream& istream, Monster& monster)
{
	return monster.ReadBinary(istream);
}
std::ofstream& operator <<(std::ofstream& ostream, Monster& monster)
{
	return monster.WriteBinary(ostream);
}