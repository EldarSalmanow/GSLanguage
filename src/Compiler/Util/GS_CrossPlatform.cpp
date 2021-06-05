#include <GS_CrossPlatform.h>

namespace Platform {

    void GS_CrossPlatform::setConsoleColor(ConsoleColor background, ConsoleColor text) {
#if defined(OS_WINDOWS)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD) ((background << 4) | text));
#endif

#if defined(OS_LINUX)
        std::cout << "\x1b[" << text + 30 << ";" << background + 40 << "m";
#endif
    }

}