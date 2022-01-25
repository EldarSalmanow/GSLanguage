#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <AST/GS_Scope.h>

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    /**
     * Base class for all AST nodes
     */
    class GS_Node {
    public:

        explicit GS_Node(GSScopePtr scope);

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
        GSScopePtr getScope() const;

    public:

        /**
         *
         * @return
         */
        virtual Bool isDeclaration() const;

        /**
         *
         * @return
         */
        virtual Bool isStatement() const;

        /**
         *
         * @return
         */
        virtual Bool isExpression() const;

    public:

        /**
         *
         * @param visitor
         * @return
         */
        virtual Any accept(Ptr<GS_Visitor> visitor) = 0;

    private:

        /**
         *
         */
        GSScopePtr _scope;
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
