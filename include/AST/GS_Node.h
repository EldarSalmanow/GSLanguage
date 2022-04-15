#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <AST/GS_Scope.h>

namespace GSLanguageCompiler::AST {

    /**
     * Base class for all AST nodes
     */
    class GS_Node {
    public:

        /**
         * Constructor for node
         */
        GS_Node();

    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Node();

    public:

        /**
         * Is declaration node
         * @return Is declaration
         */
        virtual Bool IsDeclaration() const;

        /**
         * Is statement node
         * @return Is statement
         */
        virtual Bool IsStatement() const;

        /**
         * Is expression node
         * @return Is expression
         */
        virtual Bool IsExpression() const;
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
