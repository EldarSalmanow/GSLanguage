#include "../../../include/Compiler/Util/GS_CrossPlatform.h"

namespace Platform {

    void GS_CrossPlatform::setConsoleColor(ConsoleColor background, ConsoleColor text) {
#if defined(__WIN32)
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(handle, (WORD) ((background << 4) | text));
#else
#error Platform not supported!
#endif
    }

}