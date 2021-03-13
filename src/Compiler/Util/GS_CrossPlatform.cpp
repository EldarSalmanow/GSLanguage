#include "../../../include/Compiler/Util/GS_CrossPlatform.h"

namespace Platform {

    void GS_CrossPlatform::setConsoleColor(ConsoleColor background, ConsoleColor text) {
#if defined(OS_WINDOWS)
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(handle, (WORD) ((background << 4) | text));
#endif
    }

}