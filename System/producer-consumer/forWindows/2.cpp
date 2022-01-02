#include <windows.h>
#include <queue>
using namespace std;

#define BUFFER_SIZE 10

queue<char> g_character; 
volatile int g_count = 0; 

CONDITION_VARIABLE g_emptyCond;
CONDITION_VARIABLE g_fullCond;
CRITICAL_SECTION g_bufferMutex;
int g_consumCount;

DWORD WINAPI producer(void* args)
{
    for (int i = 0; i < 52; ++i)
    {
        g_count++;
        EnterCriticalSection(&g_bufferMutex);
        while (BUFFER_SIZE == g_count) 
        {
            SleepConditionVariableCS(&g_fullCond, &g_bufferMutex, INFINITE); 
        }
        fprintf(stdout, "P:%c\n", c);
        g_character.push('A');
        LeaveCriticalSection(&g_bufferMutex);
        WakeConditionVariable(&g_emptyCond);     
    }

    return 0;
}

DWORD WINAPI consumer(void* args)
{
    int index = 0;

    while (g_consumCount <= 52)
    {
        EnterCriticalSection(&g_bufferMutex);
        g_consumCount++;
        if (g_consumCount > 52)
        {
            LeaveCriticalSection(&g_bufferMutex);
            break;
        }
        while (0 == g_count)
        {
            SleepConditionVariableCS(&g_emptyCond, &g_bufferMutex, INFINITE);
        }
        char c= g_character.front();
        g_character.pop();
        fprintf(stdout, "%c\n", c);
        g_count--;
        LeaveCriticalSection(&g_bufferMutex);
        WakeConditionVariable(&g_fullCond);        //如果产品消费了，给g_fullCond发信号，说我们腾空了位置，你又可以放产品了。
    }
    return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
    HANDLE thr[3];
    InitializeCriticalSection(&g_bufferMutex);
    InitializeConditionVariable(&g_fullCond);
    InitializeConditionVariable(&g_emptyCond);

    thr[0] = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    thr[1] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    thr[2] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    WaitForMultipleObjects(3, thr, TRUE, INFINITE);

    DeleteCriticalSection(&g_bufferMutex);
    system("pause");
    return 0;
}
