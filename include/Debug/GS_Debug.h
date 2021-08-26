#ifndef GSLANGUAGE_GS_DEBUG_H
#define GSLANGUAGE_GS_DEBUG_H

#include <Lexer/GS_Keywords.h>

#include <Parser/Nodes/GS_Node.h>
#include <Parser/Nodes/Visitors/GS_PrintVisitor.h>

//#include <GSBCCodeGen/GS_BCHighDecompiler.h>
//#include <GSBCCodeGen/GS_BCVisitors.h>

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
         static GSVoid printDebugInformation(const GSString &startMessage,
                                           const GSString &endMessage,
                                           GSVoid (*function)(_ElementType &),
                                           _ContType &data) {
             std::cout << startMessage << std::endl;

             for (auto &element : data) {
                 function(element);
             }

             std::cout << endMessage << std::endl;
         }

         static GSVoid printASTDebugInfo(const GSString &startMessage,
                                  const GSString &endMessage,
                                  GSLanguageCompiler::Parser::GSNodePtr &root) {
             std::cout << startMessage << std::endl;

             GSLanguageCompiler::Parser::GS_PrintVisitor printVisitor;

             root->accept(&printVisitor);

             std::cout << endMessage << std::endl;
         }

         /**
          *
          * @param startMessage
          * @param endMessage
          * @param bytecode
          * @return
          */
//         static GSVoid printCodeGeneratorDebugInfo(const GSString &startMessage,
//                                                   const GSString &endMessage,
//                                                   GSByteCode &bytecode) {
//             GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::RED);
//
//             std::cerr << startMessage << std::endl;
//
//             GSBCCodeGen::GS_BCHighDecompiler decompiler(bytecode);
//
//             GSBCCodeGen::GS_BCPrintVisitor visitor;
//
//             visitor.visit(decompiler.decompile());
//
//             std::cerr << endMessage << std::endl;
//
//             GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::WHITE);
//         }
    };

}

#endif //GSLANGUAGE_GS_DEBUG_H
