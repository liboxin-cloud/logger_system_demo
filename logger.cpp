#include "logger.h"

std::string Logger::level_to_string(logger_type type) {

    switch (type)
    {
        case logger_type::DEBUG: { return "DEBUG"; }
        case logger_type::INFO: { return "INFO"; }
        case logger_type::WARNING: { return "WARNING"; }
        case logger_type::ERROR: { return "ERROR"; }
        case logger_type::FATAL: { return "FATAL"; }
        default: { return "UNKNOWN"; }
    }

    return {};
}

std::string Logger::get_current_time() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch() % std::chrono::seconds(1)
    );

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
       << "." << std::setw(3) << std::setfill('0') << ms.count();
    return ss.str();
}

void Logger::print_log(logger_type type, const std::string& msg) {

    std::stringstream ss;
        ss << "[" << get_current_time() << "] "
       << "[" << level_to_string(type) << "] "
       << msg;

    std::string logLine_base = ss.str();
    std::string color_log_str;

    switch (type) {
        case logger_type::DEBUG: { color_log_str = COLOR_DEBUG; break; }  
        case logger_type::FATAL: { color_log_str = COLOR_FATAL; break; }  
        case logger_type::INFO: { color_log_str = COLOR_INFO; break; }  
        case logger_type::WARNING: { color_log_str = COLOR_WARNING; break; }  
        case logger_type::ERROR: { color_log_str = COLOR_ERROR; break; }  
    }

    color_log_str += logLine_base + COLOR_RESET;
    std::unique_lock<std::mutex> lock(g_mutex);
    std::cout << color_log_str << std::endl;
    lock.unlock();

    
    set_logger_file_path(filePath);

    if (!filePath.empty()) {
        std::ofstream ofs(filePath, std::ios::app);
        if (ofs.is_open()) {
            ofs << logLine_base << std::endl;
        }
    }
}

void Logger::set_level(logger_type level) {
    this->m_level = level;
}


void Logger::set_logger_file_path(const std::string& path) {
    this->filePath = path;
}
