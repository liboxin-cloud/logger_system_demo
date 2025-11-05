#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>

#define COLOR_RESET   "\033[0m"    // 重置为默认
#define COLOR_DEBUG   "\033[36m"   // 青色（DEBUG）
#define COLOR_INFO    "\033[32m"   // 绿色（INFO）
#define COLOR_WARNING "\033[33m"   // 黄色（WARNING）
#define COLOR_ERROR   "\033[31m"   // 红色（ERROR）
#define COLOR_FATAL   "\033[35m"   // 紫色（FATAL）

const std::string default_file_path = "./log_output.txt";

enum class logger_type {
    DEBUG,
    INFO,
    WARNING,
    ERROR, 
    FATAL

};

class Logger {
public:

    Logger() : filePath(default_file_path) {}
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(const Logger&&) = delete;
    
    void set_logger_file_path(const std::string& path);
    void set_level(logger_type level);
    void print_log(logger_type type, const std::string& msg);

private:
    logger_type m_level;
    std::mutex g_mutex;
    std::string get_current_time() const;
    std::string level_to_string(logger_type type);
    std::string filePath;

};

#endif

