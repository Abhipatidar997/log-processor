# Multi-Threaded Log Processing Service

## Overview
This project is a Linux-based multi-threaded log processing service written in C++.  
It continuously monitors a log file, processes log entries in real time, and
provides periodic summaries. The application is designed with production
thinking, focusing on thread safety, graceful shutdown, and error handling.

---

## Log Format
Each log entry must follow the format:

[TIMESTAMP] [LEVEL] Message

Example:
[2025-01-10 10:25:30] ERROR Database connection failed

Supported log levels:
- INFO
- WARNING
- ERROR
- DEBUG

---

## Architecture
The application follows a **Producer–Consumer model**:

- **LogReader (Producer Thread)**  
  Continuously monitors `app.log` and pushes new log lines into a thread-safe queue.

- **LogProcessor (Consumer Thread)**  
  Reads logs from the queue, categorizes them by log level, updates counters,
  and writes ERROR logs to a separate file.

This design ensures separation of concerns and safe concurrent execution.

---

## Thread Model
- Uses **two threads**:
  - Thread 1: LogReader
  - Thread 2: LogProcessor
- Synchronization is handled using:
  - `std::mutex`
  - `std::condition_variable`
- A custom **thread-safe queue** is used to share data between threads.

This prevents race conditions and ensures safe communication.

---

## Log Processing Logic
- Counts logs by type: INFO, WARNING, ERROR, DEBUG
- Prints a real-time summary every **10 seconds**
- Writes all ERROR logs to `error.log`
- Detects and reports invalid log formats without crashing the application

---

## Linux Features Used
- Compiled using **g++** with C++17 standard
- Build automation using **Makefile**
- File handling for reading and writing logs
- Signal handling:
  - `SIGINT (Ctrl + C)` is handled to allow **graceful shutdown**

---

## Execution Environment
The application was built and tested on **Ubuntu Linux using WSL2**.
WSL2 provides a native Linux environment on Windows and is suitable for
developing and testing Linux-based applications.

---

## Docker Usage
A Dockerfile is provided to containerize the application.

### Build Image
```bash
docker build -t log-processor .


## Run Container
docker run -v $(pwd):/app log-processor


## Docker Note
The Dockerfile is included for containerized deployment.
Local Docker execution could not be demonstrated due to system
virtualization constraints.


## Project Structure

```
log-processor/
├── src/
│   ├── main.cpp
│   ├── LogReader.cpp
│   ├── LogReader.h
│   ├── LogProcessor.cpp
│   ├── LogProcessor.h
│   ├── ThreadSafeQueue.h
├── app.log
├── error.log
├── Makefile
├── Dockerfile
└── README.md
```

