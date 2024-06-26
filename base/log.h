#ifndef TUTORIAL_VULKAN_LOG_H
#define TUTORIAL_VULKAN_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR '\\'
#elif defined(__unix__) || defined(__APPLE__)
#define PATH_SEPARATOR '/'
#elif defined(__VMS)
#define PATH_SEPARATOR ':'
#else
#error Unknown platform
#endif

static inline const char *safe_filename(const char *path) {
  const char *filename = strrchr(path, PATH_SEPARATOR);
  return filename ? filename + 1 : path;
}

#define __FILENAME__ safe_filename(__FILE__)

const int _VERBOSE_ = 0;
const int _DEBUG_ = 1;
const int _INFO_ = 2;
const int _WARN_ = 3;
const int _ERROR_ = 4;
const int _FATAL_ = 5;
const int _OFF_ = 6;

int log_(int priority, const char *fmt, ...);

#define LOG(priority, FMT, ...)                                                \
  log_(priority, "[%s:%d] : " FMT, __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOGV(FMT, ...)                                                         \
  log_(_VERBOSE_, "[%s:%d] : " FMT, __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOGD(FMT, ...)                                                         \
  log_(_DEBUG_, "[%s:%d] : " FMT, __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOGI(FMT, ...)                                                         \
  log_(_INFO_, "[%s:%d] : " FMT, __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOGW(FMT, ...)                                                         \
  log_(_WARN_, "[%s:%d] : " FMT, __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOGE(FMT, ...)                                                         \
  log_(_ERROR_, "[%s:%d] : " FMT, __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOGF(FMT, ...)                                                         \
  log_(_FATAL_, "[%s:%d] : " FMT, __FILENAME__, __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // TUTORIAL_VULKAN_LOG_H
