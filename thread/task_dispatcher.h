#pragma once

#include "thread/thread_pool.h"

namespace melon
{
  namespace thread
  {
    class TaskDispatcher : public Thread
    {
      SINGLETON(TaskDispatcher);
    public:
      void init(int threads);
      bool empty();

      void push(Task* task);
      void dispatch(Task* task);

      virtual void run();

    private:
      std::mutex                m_mutex;
      std::condition_variable   m_cond;
      std::list<Task*>          m_tasks;
    };
  }
}
