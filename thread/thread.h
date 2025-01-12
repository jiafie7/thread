#pragma once

#include <thread>

namespace melon
{
  namespace thread
  {
    class Thread
    {
    public:
      Thread();
      virtual ~Thread();

      void start();
      void stop();

      virtual void run() = 0;

    protected:
      static void* thread_fun(void* ptr);
    
    protected:
      std::thread m_thread;
    };
  }
}
