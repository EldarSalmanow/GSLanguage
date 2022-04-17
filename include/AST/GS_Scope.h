#ifndef GSLANGUAGE_GS_SCOPE_H
#define GSLANGUAGE_GS_SCOPE_H

#include <algorithm>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler {

    namespace Semantic {

        /**
         * Declaring table of symbols
         */
        class GS_TableOfSymbols;

    }

    namespace AST {

        /**
         * Declaring AST node
         */
        class GS_Node;

        // TODO update scope semantic

        /**
         * Class for representation scope in AST
         */
        class GS_Scope {
        public:

            /**
             * Constructor for scope
             * @param parent Parent scope
             */
            explicit GS_Scope(SharedPtr<GS_Scope> parent);

        public:

            /**
             * Creating scope
             * @param scope Parent scope
             * @return Scope
             */
            static SharedPtr<GS_Scope> Create(SharedPtr<GS_Scope> scope);

            /**
             * Creating global scope
             * @return Global scope
             */
            static SharedPtr<GS_Scope> CreateGlobalScope();

        public:

            /**
             * Add child scope
             * @param scope Child scope
             * @return
             */
            Void AddScope(SharedPtr<GS_Scope> scope);

            /**
             * Add node to scope
             * @param node Node
             * @return
             */
            Void AddNode(SharedPtr<GS_Node> node);

            /**
             * Replace node in scope
             * @param oldNode Old node
             * @param newNode New node
             * @return
             */
            Void ReplaceNode(SharedPtr<GS_Node> oldNode, SharedPtr<GS_Node> newNode);

        public:

            /**
             * Getter for parent scope
             * @return Parent scope
             */
            SharedPtr<GS_Scope> GetParent() const;

            /**
             * Getter for child scopes
             * @return Child scopes
             */
            Vector<SharedPtr<GS_Scope>> GetScopes() const;

            /**
             * Getter for nodes
             * @return Nodes
             */
            Vector<SharedPtr<GS_Node>> GetNodes() const;

            /**
             * Getter for table of symbols
             * @return Table of symbols
             */
            SharedPtr<Semantic::GS_TableOfSymbols> GetTableOfSymbols() const;

        private:

            /**
             * Parent scope
             */
            SharedPtr<GS_Scope> _parent;

            /**
             * Child scopes
             */
            Vector<SharedPtr<GS_Scope>> _scopes;

            /**
             * Nodes in scope
             */
            Vector<SharedPtr<GS_Node>> _nodes;

            /**
             * Scope table of symbols
             */
            SharedPtr<Semantic::GS_TableOfSymbols> _tableOfSymbols;
        };

        /**
         * Scope ptr type
         */
        using GSScopePtr = SharedPtr<GS_Scope>;

        /**
         * Scope ptr array type
         */
        using GSScopePtrArray = Vector<GSScopePtr>;

    }

}

#endif //GSLANGUAGE_GS_SCOPE_H
