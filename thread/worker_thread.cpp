#include "thread/worker_thread.h"

using namespace melon::thread;

WorkerThread::WorkerThread()
  : Task()
  , m_task(nullptr)
{
}
     
WorkerThread::~WorkerThread()
{
}

void WorkerThread::assign(Task* task);
{
  std::unique_lock<std::mutex> lck(m_mutex);
  m_task = task;
  m_cond.notify_one();
}
 
void WorkerThread::run()
{
  while (true)
  {
    std::unique_lock<std::mutex> lck(m_mutex);
    while (m_task == nullptr)
      m_cond.wait(lck);
    lck.unlock();

    log_debug("worker thread run: thread = %x, task = %x.", this, m_task);
    m_task->run();
    m_task->destroy();
    m_task = nullptr;

    // to do
    // recycle worker thread back to thread pool
  }
}