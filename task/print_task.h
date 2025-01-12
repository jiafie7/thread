#pragma once

#include "thread/task.h"
using namespace melon::thread;

namespace melon
{
  namespace task
  {
    class PrintTask : public Task
    {
    public:
      PrintTask(int* data)
        : Task((void*)data)
      {}

      ~PrintTask()
      {}

      virtual void run()
      { 
        std::cout << "task run." << '\n';
        std::cout << "num: " << *((int*)m_data) << '\n';
      }

      virtual void destroy()
      {
        std::cout << "task destroy." << '\n';
        delete static_cast<int*>(m_data);
        delete this;
      }
    };
  }
}
