#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <GSCrossPlatform/CrossPlatform.h>

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
    using GSNodePtr = std::shared_ptr<GS_Node>;

    /**
     * Container with nodes type
     */
    using GSNodePtrArray = std::vector<GSNodePtr>;

}

#endif //GSLANGUAGE_GS_NODE_H
