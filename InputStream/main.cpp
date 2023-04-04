#include <iostream>
#include <fstream>

bool LoadFile(const char* filename)
{
	std::ifstream ist(filename);
	if (!ist)	// !ist.good() �� ����
	{
		std::cerr << filename << " ������ ã�� �� �����ϴ�." << std::endl;
		return false;
	}

	char ch;

	while (ist.get(ch))		// >> �����ڿʹ� �ٸ��� �̽������� ����(����, �ٹٲ�) ������ �Ű澲�� �ʴ´�.
	{
		// �ɰ��� ����
		if (ist.bad())
		{
			std::cerr << "������ �ջ�Ǿ����ϴ�." << std::endl;
			ist.close();
			return false;
		}
		// �� ���� (���� ������ �߸� �Ǿ����Ƿ� �����ڿ��� �˷��ݽô�)
		if (ist.fail())
		{
			std::cerr << "�߸��� ���� �����Դϴ�" << std::endl;
			ist.close();
			return false;
		}
		std::cout << ch;
	}

	ist.close();
	return true;
}

int main()
{
	LoadFile("Data/alphabet.txt");
}