#include "thread/task_dispatcher.h"
using namespace melon::thread;

#include "task/print_task.h"
using namespace melon::task;

int main()
{
  Singleton<LogSystem>::getInstance()->open("./../main.log");
  Singleton<LogSystem>::getInstance()->setConsole(false);

  int threads = 4;
  Singleton<TaskDispatcher>::getInstance()->init(threads);

  for (int i = 0; i < 10; ++ i)
  {
    int* num = new int;
    *num = i;

    PrintTask* task = new PrintTask(num);

    Singleton<TaskDispatcher>::getInstance()->push(task);
  }

  std::getchar();

  return 0;
}
