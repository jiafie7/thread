#include "thread/task_dispatcher.h"

using namespace melon::thread;

void TaskDispatcher::init(int threads)
{
  Singleton<ThreadPool>::getInstance()->create(threads);
  start();
}
      
bool TaskDispatcher::empty()
{
  std::unique_lock<std::mutex> lck(m_mutex);
  return m_tasks.empty();
}

void TaskDispatcher::push(Task* task)
{
  log_debug("task dispatcher get a task: %x.", task);
  std::unique_lock<std::mutex> lck(m_mutex);
  m_tasks.push_back(task);
  m_cond.notify_one();
}

void TaskDispatcher::dispatch(Task* task)
{
  ThreadPool* pool = Singleton<ThreadPool>::getInstance();

  if (pool->empty())
  {
    std::unique_lock<std::mutex> lck(m_mutex);
    m_tasks.push_back(task);
    log_warn("all worker threads are busy!");
  }
  else
    pool->assign(task);
}

void TaskDispatcher::run()
{
  while (true)
  {
    std::unique_lock<std::mutex> lck(m_mutex);
    while (m_tasks.empty())
      m_cond.wait(lck);

    Task* task = m_tasks.front();
    m_tasks.pop_front();

    lck.unlock();

    dispatch(task);
  }
}
