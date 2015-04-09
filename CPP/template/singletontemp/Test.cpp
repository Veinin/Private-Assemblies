#include <iostream>
#include "Singleton.h"

using namespace std;

class ApplicationImpl
{
public:
	ApplicationImpl()
	{
		cout << "ApplicationImpl ..." << endl;
	}

	~ApplicationImpl()
	{
		cout << "~ApplicationImpl ..." << endl;
	}

	void Run()
	{
		cout << "Run ..." << endl;
	}
};

typedef Singleton<ApplicationImpl> Application;

int main(void)
{
	Application::GetInstance()->Run();

	return 0;
}
