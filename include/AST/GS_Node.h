#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace GSLanguageCompiler::AST {

    /**
     * Base class for all AST nodes
     */
    class GS_Node {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Node();

    public:

        /**
         *
         * @return
         */
        virtual Bool isDeclaration();

        /**
         *
         * @return
         */
        virtual Bool isStatement();

        /**
         *
         * @return
         */
        virtual Bool isExpression();
    };

    /**
     * Node ptr type
     */
    using GSNodePtr = SharedPtr<GS_Node>;

    /**
     * Container with nodes type
     */
    using GSNodePtrArray = Vector<GSNodePtr>;

}

#endif //GSLANGUAGE_GS_NODE_H
