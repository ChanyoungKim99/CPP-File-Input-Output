#include <iostream>
#include <fstream>

bool LoadFile(const char* filename)
{
	std::ifstream ist;
	ist.exceptions(std::ifstream::failbit | std::ifstream::badbit);			// 에러 상태 비트

	try
	{
		ist.open(filename);				// open 멤버 함수를 통해 직접 파일을 부름
		char ch;
		while (ist.get(ch))
		{
			std::cout << ch;
		}
		ist.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "파일 연산 도중 예외가 발생했습니다.\n" << e.what() << std::endl;	
		// what = 예외 종류에 맞는 에러 원인 메세지 리턴 함수 (에러 메세지 리턴하므로 const char* 타입)
		// std::exception 클래스의 모든 자식 클래스는 virtual 가상 함수 what()을 오버라이딩함
		ist.close();
		return false;
	}
	return true;
}

int main()
{

}