#ifndef GSLANGUAGE_GS_SCOPE_H
#define GSLANGUAGE_GS_SCOPE_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

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

            explicit GS_Scope(GSScopePtr parent);

        public:

            Void addScope(GSScopePtr scope);

            Void addNode(GSNodePtr node);

        public:

            GSScopePtr getParent();

            GSScopePtrArray getScopes();

            GSNodePtrArray getNodes();

            Semantic::GSTableOfSymbolsPtr getTableOfSymbols();

        private:

            GSScopePtr _parent;

            GSScopePtrArray _scopes;

            GSNodePtrArray _nodes;

            Semantic::GSTableOfSymbolsPtr _tableOfSymbols;
        };

    }

}

#endif //GSLANGUAGE_GS_SCOPE_H
