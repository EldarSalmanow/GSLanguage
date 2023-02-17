#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::AST {

    /**
     * Base class for all AST nodes
     */
    class GS_Node {
    public:

        /*
         *
         * GS_Node PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Node();

    public:

        /*
         *
         * GS_Node PUBLIC VIRTUAL METHODS
         *
         */

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
     * Custom node ptr type for any node
     */
    template<typename T>
    using NodePtr = std::shared_ptr<T>;

    /**
     * Custom node ptr left value type for any node
     */
    template<typename T>
    using NodePtrLRef = LRef<NodePtr<T>>;

    /**
     * Custom node ptr right value type for any node
     */
    template<typename T>
    using NodePtrRRef = RRef<NodePtr<T>>;

    /**
     * Custom node ptr array type for any node
     */
    template<typename T>
    using NodePtrArray = std::vector<NodePtr<T>>;

    /**
     * Node ptr type
     */
    using GSNodePtr = NodePtr<GS_Node>;

    /**
     * Container with nodes type
     */
    using GSNodePtrArray = std::vector<GSNodePtr>;

}

#endif //GSLANGUAGE_GS_NODE_H
