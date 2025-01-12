#include "thread/thread.h"

using namespace melon::thread;

Thread::Thread()
{
}
      
Thread::~Thread()
{
}

void Thread::start()
{
  m_thread = std::thread(Thread::thread_fun, this);
  m_thread.detach();
}

void Thread::stop()
{
}

void* Thread::thread_fun(void* ptr)
{
  Thread* thread = (Thread*)ptr;

  thread->run();

  return ptr;
}
