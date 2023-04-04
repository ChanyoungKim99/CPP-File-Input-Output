#include <iostream>
#include <fstream>

bool LoadFile(const char* filename)
{
	std::ifstream ist(filename);
	if (!ist)	// !ist.good() 와 같음
	{
		std::cerr << filename << " 파일을 찾을 수 없습니다." << std::endl;
		return false;
	}

	char ch;

	while (ist.get(ch))		// >> 연산자와는 다르게 이스케이프 문자(공백, 줄바꿈) 같은걸 신경쓰지 않는다.
	{
		// 심각한 오류
		if (ist.bad())
		{
			std::cerr << "파일이 손상되었습니다." << std::endl;
			ist.close();
			return false;
		}
		// 논리 오류 (파일 구성이 잘못 되었으므로 개발자에게 알려줍시다)
		if (ist.fail())
		{
			std::cerr << "잘못된 파일 포맷입니다" << std::endl;
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