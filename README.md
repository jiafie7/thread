# thread

This project implements a Thread Pool Framework using the C++ Standard Library. It provides an efficient way to manage concurrent task execution by distributing workloads across multiple threads. The system is composed of four core components: Task, WorkerThread, ThreadPool, and TaskDispatcher.

## 🚀 Features

- **Efficient Multithreading**: Leverages std::thread for lightweight thread management.
- **Task Scheduling**: Centralized task queue with dynamic task assignment.
- **Thread Reuse**: Minimizes thread creation overhead by reusing worker threads.
- **Thread-Safe Synchronization**: Uses std::mutex and std::condition_variable for safe data access.
- **Modular Design**: Easy to extend and maintain.

## ⚙️ Workflow

- **Task Creation**: Implement custom tasks by inheriting from the Task class and overriding the run() and destroy() methods.

- **Task Scheduling**: Tasks are added to the TaskDispatcher, which manages the task queue.

- **Task Assignment**: The dispatcher assigns tasks to idle WorkerThread instances from the ThreadPool.

- **Task Execution**: Worker threads execute the assigned tasks and return to the pool upon completion.

## 📄 Getting Started

1. Prerequisites

   - C++ 11 or later

2. Clone the Repository

```c
git clone https://github.com/jiafie7/thread.git
cd thread
```

## 🛠️ Usage

1. Example Code

```c
#include "thread/task_dispatcher.h"
using namespace melon::thread;

#include "task/print_task.h"
using namespace melon::task;

int main()
{
  Singleton<LogSystem>::getInstance()->open("./../main.log");
  Singleton<LogSystem>::getInstance()->setConsole(false);

  int threads = 4;
  Singleton<TaskDispatcher>::getInstance()->init(threads);

  for (int i = 0; i < 10; ++ i)
  {
    int* num = new int;
    *num = i;

    PrintTask* task = new PrintTask(num);

    Singleton<TaskDispatcher>::getInstance()->push(task);
  }

  std::getchar();

  return 0;
}
```

2. Build the Project

```c
mkdir build
cd build
cmake ..
make
./main
```

3. Output

```c
task run.
num: 0
task destroy.
task run.
num: 2
task destroy.
task run.
num: 1
task destroy.
task run.
num: 3
task destroy.
task run.
num: 4
task destroy.
task run.
num: 5
task destroy.
task run.
num: 6
task destroy.
task run.
num: 8
task destroy.
task run.
num: 9
task destroy.
task run.
num: 7
task destroy.
```

## 📦 API Reference

### Task Class

- `void* getData()`: Retrieves task data.
- `void setData(void*)`: Sets task data.
- `virtual void run()`: Pure virtual method to execute the task.
- `virtual void destroy()`: Pure virtual method to clean up resources.

### WorkerThread Class

- `void assign(Task*)`: Assigns a task to the worker thread.
- `void run()`: Continuously waits for tasks and executes them.

### ThreadPool Class

- `void create(int n)`: Initializes the pool with n threads.
- `bool empty()`: Checks if the thread pool is empty.
- `WorkerThread* get()`: Retrieves an idle worker thread.
- `void push(WorkerThread*)`: Returns a worker thread to the pool.
- `void assign(Task*)`: Assigns a task to an available worker.

### TaskDispatcher

- `void init(int threads)`: Initializes the dispatcher and thread pool.
- `bool empty()`: Checks if the task queue is empty.
- `void push(Task*)`: Adds a task to the queue.
- `void dispatch(Task*)`: Sends a task to the thread pool.
- `void run()`: Continuously dispatches queued tasks.

## 📜 License

This project is licensed under the MIT License. See the LICENSE file for more information.

## 🤝 Contributions

Contributions, bug reports, and feature requests are welcome. Feel free to fork the repository, open issues, or submit pull requests.
