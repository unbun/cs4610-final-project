#include <string>
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

// The function we want to execute on the new thread.
void task1(string msg)
{
	usleep(100);
    cout << "task1 says: " << msg << endl;
    usleep(1000);
    cout << "task1 says: hello 3" << endl;
}

int main()
{
    // Constructs the new thread and runs it. Does not block execution.
    thread t1(task1, "hello 1");
	usleep(500);
	cout << "main says: hello 2" << endl;

    // Do other things..
    t1.join();
}