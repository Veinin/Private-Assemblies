#include <pthread.h>
#include <stdio.h>

int
makethread(void *(*fn)(void *), void *arg)
{
    int err;
    pthread_t tid;
    pthread_attr_t attr;
    
    err = pthread_attr_init(&attr); //创建线程属性结构
    if(err != 0)
        return err;
    err = pthread_attr_setdetachstate(&attr, PHTREAD_CREATE_DETACHED);  //设置分离属性
    if(err == 0)
        err = pthread_create(&tid, &attr, fn, arg);
    pthread_attr_destroy(&attr);    //销毁线程属性结构
    
    return err;
}