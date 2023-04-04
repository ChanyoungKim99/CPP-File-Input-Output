#include <iostream>
#include <fstream>

bool LoadFile(const char* filename)
{
	std::ifstream ist;
	ist.exceptions(std::ifstream::failbit | std::ifstream::badbit);			// ���� ���� ��Ʈ

	try
	{
		ist.open(filename);				// open ��� �Լ��� ���� ���� ������ �θ�
		char ch;
		while (ist.get(ch))
		{
			std::cout << ch;
		}
		ist.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "���� ���� ���� ���ܰ� �߻��߽��ϴ�.\n" << e.what() << std::endl;	
		// what = ���� ������ �´� ���� ���� �޼��� ���� �Լ� (���� �޼��� �����ϹǷ� const char* Ÿ��)
		// std::exception Ŭ������ ��� �ڽ� Ŭ������ virtual ���� �Լ� what()�� �������̵���
		ist.close();
		return false;
	}
	return true;
}

int main()
{

}