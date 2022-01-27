#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <AST/GS_Scope.h>

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
         * Getter for scope
         * @return Scope
         */
        LRef<GSScopePtr> getScope();

    public:

        /**
         * Is declaration node
         * @return Is declaration
         */
        virtual Bool isDeclaration() const;

        /**
         * Is statement node
         * @return Is statement
         */
        virtual Bool isStatement() const;

        /**
         * Is expression node
         * @return Is expression
         */
        virtual Bool isExpression() const;

    private:

        /**
         * Scope
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
