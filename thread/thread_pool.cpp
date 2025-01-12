#include "thread/thread_pool.h"

using namespace melon::thread;

void ThreadPool::create(int threads)
{
  std::unique_lock<std::mutex> lck(m_mutex);
  for (int i = 0; i < threads; ++ i)
  {
    WorkerThread* thread = new WorkerThread();
    thread->start();
    m_pool.push_back(thread);
  }
  m_threads = threads;
  log_debug("thread pool create worker threads: %d", threads);
}

bool ThreadPool::empty()
{
  std::unique_lock<std::mutex> lck(m_mutex);
  return m_pool.empty();
}
 
WorkerThread* ThreadPool::get()
{
  std::unique_lock<std::mutex> lck(m_mutex);
  while (m_pool.empty())
    m_cond.wait(lck);

  WorkerThread* thread = m_pool.front();
  m_pool.pop_front();

  return thread;
}

void ThreadPool::push(WorkerThread* thread)
{
  std::unique_lock<std::mutex> lck(m_mutex);
  m_pool.push_back(thread);

  m_cond.notify_one();
}
 
void ThreadPool::assign(Task* task)
{
  WorkerThread* thread = get();
  thread->assign(task);
}
