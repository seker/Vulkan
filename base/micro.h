#ifndef TUTORIAL_VULKAN_MICRO_H
#define TUTORIAL_VULKAN_MICRO_H

#include <sstream>
static inline std::string ptr_to_str(const void *const p) {
  if (p == nullptr) {
    return "nullptr";
  } else {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase
        << reinterpret_cast<std::uintptr_t>(p);
    return oss.str();
  }
}

#define P2S(p) (ptr_to_str(p).c_str())
#define B2S(b) (b ? "true" : "false")
#define S2S(b) (b ? b : "null")

#define SAFE_DELETE(ptr)                                                       \
  {                                                                            \
    if (ptr) {                                                                 \
      delete (ptr);                                                            \
      (ptr) = nullptr;                                                         \
    }                                                                          \
  }
#define SAFE_DELETE_ARRAY(arr)                                                 \
  {                                                                            \
    if ((arr) != nullptr) {                                                    \
      delete[] (arr);                                                          \
      (arr) = nullptr;                                                         \
    }                                                                          \
  }
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    __debugbreak();
#elif __APPLE__
#include <signal.h>
#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    raise(SIGTRAP);
#elif __linux__
#include <signal.h>
#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    raise(SIGTRAP);
#else
#define ASSERT(x)
#endif

#ifdef __cplusplus
}
#endif
#endif // TUTORIAL_VULKAN_MICRO_H