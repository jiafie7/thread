#pragma once

#include <condition_variable>
#include <mutex>

#include "thread/task.h"
#include "thread/thread.h"

#include "utility/log_system.h"
using namespace melon::utility;

namespace melon
{
  namespace thread
  {
    class WorkerThread : public Thread
    {
    public:
      WorkerThread();
      ~WorkerThread();

      void assign(Task* task);

      virtual void run();

    private:
      std::mutex                m_mutex;
      std::condition_variable   m_cond;
      Task*                     m_task;
    };
  }
}
