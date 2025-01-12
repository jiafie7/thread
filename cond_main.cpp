#include <condition_variable>
#include <list>
#include <iostream>
#include <mutex>
#include <unistd.h>

#include "thread/thread.h"

using namespace melon::thread;

class TaskQueue : public Thread
{
public:
  TaskQueue()
  {}

  ~TaskQueue()
  {}

  virtual void run()
  {
    while (true)
    {
      std::unique_lock<std::mutex> lck(m_mutex);
      while (m_tasks.empty())
      {
        std::cout << "waiting for a task ... " << '\n';
        m_cond.wait(lck);
      }
      
      int num = m_tasks.front();
      m_tasks.pop_front();

      lck.unlock();
      
      std::cout << "num: " << num << '\n';
    }
  }

  void push(int num)
  {
    std::unique_lock<std::mutex> lck(m_mutex);
    m_tasks.push_back(num);
    m_cond.notify_one();
  }

private:
  std::mutex                m_mutex;
  std::condition_variable   m_cond;
  std::list<int>            m_tasks;
};

int main()
{
  TaskQueue task;
  task.start();

  for (int i = 0; i < 10; ++ i)
  {
    ::sleep(2);
    task.push(i);
  }

  std::getchar();

  return 0;
}
