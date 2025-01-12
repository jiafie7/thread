#include <iostream>
#include <string>
#include <thread>

#include "thread/thread.h"

using namespace melon::thread;

void foo(const std::string& name)
{
  std::cout << "Hello, "  << name << "!" << '\n';
}

class TestThread : public Thread
{
public:
  virtual void run()
  {
    std::cout << "This is a test thread." << '\n';
  }
};

int main()
{
  /*********** C style ***********/
  std::string name = "Michael";
  std::thread t1(foo, name);
  t1.join();


  /*********** C++ class Thread ************/
  TestThread t2;
  t2.start();

  std::getchar();

  return 0;
}
