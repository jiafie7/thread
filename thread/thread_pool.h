#pragma once

#include <list>
#include "thread/worker_thread.h"

namespace melon
{
  namespace thread
  {
    class ThreadPool
    {
      SINGLETON(ThreadPool);
    public:
      void create(int threads);
      bool empty();

      WorkerThread* get();
      void push(WorkerThread* thread);
      
      void assign(Task* task);

    private:
      int                       m_threads;
      std::mutex                m_mutex;
      std::condition_variable   m_cond;
      std::list<WorkerThread*>  m_pool;
    };
  }
}
