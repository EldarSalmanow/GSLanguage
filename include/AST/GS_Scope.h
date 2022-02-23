#ifndef GSLANGUAGE_GS_SCOPE_H
#define GSLANGUAGE_GS_SCOPE_H

#include <algorithm>

#include <GSCrossPlatform/GS_CrossPlatform.h>

namespace GSLanguageCompiler {

    namespace Semantic {

        class GS_TableOfSymbols;

        using GSTableOfSymbolsPtr = SharedPtr<GS_TableOfSymbols>;

    }

    namespace AST {

        class GS_Node;

        using GSNodePtr = SharedPtr<GS_Node>;

        using GSNodePtrArray = Vector<GSNodePtr>;

        class GS_Scope;

        /**
         * Scope ptr type
         */
        using GSScopePtr = SharedPtr<GS_Scope>;

        /**
         * Scope ptr array type
         */
        using GSScopePtrArray = Vector<GSScopePtr>;

        class GS_Scope {
        public:

            /**
             * Constructor for scope
             * @param parent Parent scope
             */
            explicit GS_Scope(GSScopePtr parent);

        public:

            /**
             * Add child scope
             * @param scope Child scope
             * @return
             */
            Void addScope(GSScopePtr scope);

            /**
             * Add node to scope
             * @param node Node
             * @return
             */
            Void addNode(GSNodePtr node);

            /**
             * Replace node in scope
             * @param oldNode Old node
             * @param newNode New node
             * @return
             */
            Void replaceNode(GSNodePtr oldNode, GSNodePtr newNode);

        public:

            /**
             * Getter for parent scope
             * @return Parent scope
             */
            GSScopePtr getParent() const;

            /**
             * Getter for child scopes
             * @return Child scopes
             */
            GSScopePtrArray getScopes() const;

            /**
             * Getter for nodes
             * @return Nodes
             */
            GSNodePtrArray getNodes() const;

            /**
             * Getter for table of symbols
             * @return Table of symbols
             */
            Semantic::GSTableOfSymbolsPtr getTableOfSymbols() const;

        private:

            /**
             * Parent scope
             */
            GSScopePtr _parent;

            /**
             * Child scopes
             */
            GSScopePtrArray _scopes;

            /**
             * Nodes in scope
             */
            GSNodePtrArray _nodes;

            /**
             * Scope table of symbols
             */
            Semantic::GSTableOfSymbolsPtr _tableOfSymbols;
        };

    }

}

#endif //GSLANGUAGE_GS_SCOPE_H
