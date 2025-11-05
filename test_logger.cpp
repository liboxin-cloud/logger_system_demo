#include "logger.h"
#include <thread>
#include <vector>
#include <iostream>

// 线程函数：每个线程输出多条日志
void thread_log_func(int thread_id, Logger* logger) {
    for (int i = 0; i < 5; ++i) {  // 每个线程输出5条日志
        // 构造日志内容（包含线程ID和序号）
        std::string msg = "Thread " + std::to_string(thread_id) + " log " + std::to_string(i);
        // 随机使用不同的日志级别
        logger_type level;
        switch (i % 5) {
            case 0: level = logger_type::DEBUG; break;
            case 1: level = logger_type::INFO; break;
            case 2: level = logger_type::WARNING; break;
            case 3: level = logger_type::ERROR; break;
            case 4: level = logger_type::FATAL; break;
        }
        // 输出日志到文件"multi_thread_log.txt"
        logger->print_log(level, msg);
    }
}

int main() {
    // 创建日志器实例
    Logger* logger = new Logger();
    // 可选：设置日志级别（默认DEBUG，这里输出所有级别）
    logger->set_level(logger_type::DEBUG);

    // 创建5个线程同时写日志
    const int thread_count = 5;
    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    std::cout << "开始多线程日志测试，共" << thread_count << "个线程..." << std::endl;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(thread_log_func, i, logger);  // 传递线程ID和日志器
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "多线程日志测试完成，日志已写入 multi_thread_log.txt" << std::endl;
    delete logger;
    return 0;
}
