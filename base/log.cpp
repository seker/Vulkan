#include <chrono>
#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>

#include "log.h"

static std::unordered_map<int, std::string> priority2str = {
    {_VERBOSE_, "V"}, {_DEBUG_, "D"}, {_INFO_, "I"},
    {_WARN_, "W"},    {_ERROR_, "E"}, {_FATAL_, "F"},
};

static inline std::string getCurrentTimeInMilliseconds() {
  // 获取自 epoch (1970-01-01 00:00:00) 以来的时间点
  auto now = std::chrono::system_clock::now();

  // 获取自最近的整秒开始以来的毫秒数
  auto fraction = now - std::chrono::time_point_cast<std::chrono::seconds>(now);

  // 用毫秒表示的时间段
  auto milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(fraction);

  // 将 time_t 对象转换为 tm 结构体以便以字符串形式打印
  std::time_t cnow = std::chrono::system_clock::to_time_t(now);
  std::tm *tm = std::localtime(&cnow);

  std::ostringstream oss;

  oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S"); // 输出 YYYY-MM-DD hh:mm:ss
  oss << '.' << std::setfill('0') << std::setw(3)
      << milliseconds.count(); // 输出 毫秒

  return oss.str();
}

static inline size_t getThreadId() {
  // 模以一个大的质数，以减少哈希冲突的可能性
  return std::hash<std::thread::id>()(std::this_thread::get_id()) % 1000000007;
}

int log_(const int priority, const char *const fmt, ...) {
  std::string now = getCurrentTimeInMilliseconds();

  // https://mp.weixin.qq.com/s?__biz=MzU4OTQyODI0Mw==&mid=2247484310&idx=1&sn=1df96021d9bcdbc3fbedcf8b333befd6&chksm=fdcce0eacabb69fc3061611ba087ee0192209fa8301814974111bc4f1aaef60eb72184ee6787&scene=27
  va_list args;
  va_start(args, fmt);
  const auto size = static_cast<size_t>(vsnprintf(nullptr, 0, fmt, args));
  va_end(args);

  std::string msg;
  msg.resize(size + 1);
  va_start(args, fmt);
  vsnprintf(&msg.front(), size + 1, fmt, args);
  va_end(args);
  msg.resize(size);

  if (priority >= _ERROR_) {
    std::cerr << now << " [" << priority2str[priority]
              << "][tid=" << getThreadId() << "]" << msg << std::endl;
  } else {
    std::cout << now << " [" << priority2str[priority]
              << "][tid=" << getThreadId() << "]" << msg << std::endl;
  }
  fflush(stdout);

  return 0;
}