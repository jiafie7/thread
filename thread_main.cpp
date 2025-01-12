#include <iostream>
#include <string>
#include <thread>

void foo(const std::string& name)
{
  std::cout << "Hello, "  << name << "!" << '\n';
}

int main()
{
  // C style
  std::string name = "Michael";
  std::thread t(foo, name);
  t.join();

  std::getchar();

  return 0;
}
