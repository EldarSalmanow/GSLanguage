#ifndef GSLANGUAGE_GS_SCOPE_H
#define GSLANGUAGE_GS_SCOPE_H

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

        using GSScopePtr = SharedPtr<GS_Scope>;

        using GSScopePtrArray = Vector<GSScopePtr>;

        class GS_Scope {
        public:

            /**
             *
             * @param parent
             */
            explicit GS_Scope(GSScopePtr parent);

        public:

            /**
             *
             * @param scope
             * @return
             */
            Void addScope(GSScopePtr scope);

            /**
             *
             * @param node
             * @return
             */
            Void addNode(GSNodePtr node);

            /**
             *
             * @param node
             * @return
             */
            Void removeNode(GSNodePtr node);

        public:

            /**
             *
             * @return
             */
            GSScopePtr getParent() const;

            /**
             *
             * @return
             */
            GSScopePtrArray getScopes() const;

            /**
             *
             * @return
             */
            GSNodePtrArray getNodes() const;

            /**
             *
             * @return
             */
            Semantic::GSTableOfSymbolsPtr getTableOfSymbols() const;

        private:

            /**
             *
             */
            GSScopePtr _parent;

            /**
             *
             */
            GSScopePtrArray _scopes;

            /**
             *
             */
            GSNodePtrArray _nodes;

            /**
             *
             */
            Semantic::GSTableOfSymbolsPtr _tableOfSymbols;
        };

    }

}

#endif //GSLANGUAGE_GS_SCOPE_H
