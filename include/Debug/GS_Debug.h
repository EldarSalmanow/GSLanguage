#ifndef GSLANGUAGE_GS_DEBUG_H
#define GSLANGUAGE_GS_DEBUG_H

#include <iostream>
#include <vector>

#include <Lexer/GS_Keywords.h>

#include <CrossPlatform/GS_CrossPlatform.h>

namespace Debug {

    using namespace Platform;

    /**
     * Class for debugging and testing input and output compilation parameters GSLanguageCompiler
     */
    class GS_Debug {
    public:

         /**
          *
          * @tparam _ContType
          * @tparam _ElementType
          * @param startMessage
          * @param endMessage
          * @param function
          * @param data
          */
         template<typename _ContType, typename _ElementType>
         static void printDebugInformation(const GSString &startMessage,
                                           const GSString &endMessage,
                                           GSVoid (*function)(_ElementType &),
                                           _ContType &data) {
             GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::RED);

             std::cerr << startMessage << std::endl;

             for (auto &element : data) {
                 function(element);
             }

             std::cerr << endMessage << std::endl;

             GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::WHITE);
         }
    };

}

#endif //GSLANGUAGE_GS_DEBUG_H
