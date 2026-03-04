- [Major Projects](#major-projects)
  - [Learning Approach](#learning-approach)
  - [HOT: Newly Added Projects](#hot-newly-added-projects)
    - [Thread Pool](#thread-pool)
  - [Writing a Simple Mutex in 100 Lines, Step by Step](#writing-a-simple-mutex-in-100-lines-step-by-step)
    - [Content](#content)
    - [Topics Covered](#topics-covered)
  - [Seven Ways to Master condition\_variable](#seven-ways-to-master-condition_variable)
    - [Content](#content-1)
    - [Topics Covered](#topics-covered-1)
  - [DuckDB + LevelDB](#duckdb--leveldb)
  - [C++那些事 Ten‑Day Intensive Practice (Upgraded Version)](#c那些事-tenday-intensive-practice-upgraded-version)


# Major Projects

## Learning Approach

To dive deep into the following projects, you can scan the QR code to join the knowledge community (membership), or add my WeChat: **gcxzhang**, and mark: “Join the community”.


<img src="../img/cpp.jpg" alt="Knowledge Community" width="400" height="300">


## HOT: Newly Added Projects


### Thread Pool


A step‑by‑step tutorial shows how this thread pool works. You can click the link below for video + text tutorials; it guarantees you’ll understand it.

[https://mp.weixin.qq.com/s/ceQoyHVMVmaXL3BNt25O4g](https://mp.weixin.qq.com/s/ceQoyHVMVmaXL3BNt25O4g)

This thread‑pool project is derived from the Apache Arrow project. We completely extracted Arrow’s complex core thread‑pool component and turned it into an independent project. Because the original thread pool was tightly coupled with Arrow’s own tooling, we deeply simplified and refactored it here, while keeping its basic functionality aligned with the original Arrow thread pool. Changes include:


- Replaced Arrow’s `Future` with `std::future`.
- Replaced Arrow’s `Result` with `std::optional`.
- Refactored the `Submit` interface to be implemented using `std::promise`.


Our goals are:


- Make the thread pool easier to use as a dependency library in other projects.
- Provide a simple way to link this project’s `.so` library and headers to use the thread‑pool functionality.


In addition, this project can also serve as a resource for in‑depth learning of thread‑pool design and implementation. You are welcome to explore and use this carefully improved thread pool.

[Thread Pool – Lark Doc](https://hmpy6adnp5.feishu.cn/docx/BEKBdq0egoxmxNx3X3ZcHzkUnwd)


## Writing a Simple Mutex in 100 Lines, Step by Step
### Content


Project name: SimpleMutex (Simple Mutex)


Project description: SimpleMutex is a mutex implementation based on atomic variables and POSIX semaphores. It protects and manages access to shared resources in a multi‑threaded environment. It provides a simple but effective way to ensure that, during concurrent multi‑thread access, only one thread can access the protected resource at any time, thus avoiding data races and inconsistencies. This implementation is based on the POSIX semaphore library, includes Catch2 unit tests, and uses Bazel as the build system and follows the Google C++ style guide.

[https://mp.weixin.qq.com/s/SqtdadmCaJNSK10fScFlUw](https://mp.weixin.qq.com/s/SqtdadmCaJNSK10fScFlUw)


### Topics Covered


This project covers the following C++ concepts (RAII, semaphores, `lock_guard`, thread‑safe programming) and also lets you learn the following topics:

1. **Bazel build system**: Learn how to use Bazel to manage and build C++ projects. Bazel is an efficient, scalable build tool that helps manage complex project structures, dependencies, and build workflows.

2. **Catch2 test framework**: Learn how to use Catch2 to write unit tests. Catch2 is a powerful and easy‑to‑use C++ testing framework that helps you write clear, readable test cases and improves code quality and reliability.

3. **Atomic operations**: Learn the concept and usage of atomic operations. Atomic operations are a concurrency technique that ensures operations on shared variables are indivisible, avoiding race conditions and data inconsistency.

4. **fetch_add function**: Learn how to use the `fetch_add` function for atomic addition. `fetch_add` is an atomic operation that safely performs atomic addition on shared variables in a concurrent environment, preventing data races.

5. **Memory order**: Understand the impact of different memory orders (memory order) on multi‑threaded programs.

6. **Automatic lock management**: Introduce the `lock_guard` class to automatically acquire and release locks. `lock_guard` is a lock‑management tool provided by the C++ standard library: it acquires the lock in the constructor and releases it in the destructor, ensuring the lock is always properly released even in the presence of exceptions or early returns.

7. **RAII (Resource Acquisition Is Initialization)**: Learn how to manage resource acquisition and release through object lifetimes, ensuring resources are correctly acquired and released and avoiding resource leaks.


## Seven Ways to Master condition_variable

[https://mp.weixin.qq.com/s/33ZXOA-tzhbBKMFWS26kCw](https://mp.weixin.qq.com/s/33ZXOA-tzhbBKMFWS26kCw)


### Content


1. **CPU‑polling‑based single‑producer single‑consumer**:

   This version uses a simple polling mechanism where the producer repeatedly checks whether the consumer has finished consuming data. The pattern is simple and straightforward, but inefficient because the producer keeps busy‑waiting when there is no data.

2. **Wait‑and‑notify based single‑producer single‑consumer**:

   This version introduces a wait‑and‑notify mechanism: the producer waits for notification from the consumer when there is no data. This avoids busy‑waiting, improves efficiency, and reduces resource consumption.

3. **Wait‑and‑notify based single‑producer multiple‑consumer**:

   In this version multiple consumers share the producer’s data. After the producer produces data, it notifies all consumers to process it.

4. **Wait‑and‑notify based multiple‑producer multiple‑consumer**:

   This version supports multiple producers and multiple consumers. Producers share data with consumers, and after producing data the producers notify all consumers to process it.

5. **Single‑producer multiple‑consumer parallel version**:

   This version introduces a parallel‑processing mechanism where multiple consumers can process data simultaneously. After the producer generates data, several consumers handle it in parallel, increasing overall throughput.

6. **Multiple‑producer multiple‑consumer parallel version**:

   This version supports multiple producers and multiple consumers, and allows parallel processing. Multiple producers generate data in parallel and multiple consumers process data in parallel, improving overall concurrency.

7. **Graceful‑shutdown version with Lambda callbacks**:

   In this version, Lambda callback functions are introduced to gracefully stop concurrent processing. By calling the callback function, you can stop the producers and consumers and perform cleanup.


### Topics Covered

1. **Multi‑threading and concurrent programming**: By studying these versions, you will learn how to use multi‑threading and concurrency in C++ to handle parallel tasks. You will learn how to create threads, control thread execution, and share and synchronize data among threads.

2. **Synchronization mechanisms**: These versions introduce different synchronization mechanisms, including polling, wait‑and‑notify, and callbacks. You will learn how to use mutexes, condition variables, and semaphores to achieve thread synchronization and coordination.

3. **Lambda expressions**: In the Lambda‑callback version you will learn how to use C++11 lambda expressions to write concise and flexible callback functions that implement a graceful‑shutdown mechanism.

4. **Code organization and build tools**: The tutorial mentions support for Bazel compilation, which lets you learn how to use build tools to organize and manage complex C++ projects.

5. **`condition_variable`, `mutex`, `unique_lock`**

## DuckDB + LevelDB

LevelDB source‑code analysis is complete.

DuckDB content is being continuously updated.

## C++那些事 Ten‑Day Intensive Practice (Upgraded Version)

This upgrade is complete.