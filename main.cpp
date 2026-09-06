// main.cpp — tự chọn bản Windows hoặc macOS khi biên dịch
#ifdef _WIN32
#include "snake_windows.cpp"
#else
#include "snake_macos.cpp"
#endif
