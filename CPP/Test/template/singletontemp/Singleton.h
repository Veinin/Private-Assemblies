#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <pthread.h>
#include <cstdlib>

template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		pthread_once(&ponce, Singleton::Init);
		return instance_;
	}

private:
	Singleton(const Singleton& other);
	Singleton& operator=(const Singleton& other);
	Singleton();
	~Singleton();

	static void Init() 
	{
		if(instance_ == 0) 
		{
			instance_ = new T;
			atexit(Destroy);
		}
	}

	static void Destroy()
	{
		delete instance_;
	}

	static pthread_once_t ponce;
	static T* instance_;
};

template <typename T>
T* Singleton<T>::instance_ = 0;

template <typename T>
pthread_once_t Singleton<T>::ponce = PTHREAD_ONCE_INIT;

#endif
