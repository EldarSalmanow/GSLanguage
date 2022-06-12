#include <GS_Node.h>

namespace GSLanguageCompiler::AST {

    GS_NodeLocation::GS_NodeLocation(Lexer::GS_TokenLocation startLocation, Lexer::GS_TokenLocation endLocation)
            : _startLocation(std::move(startLocation)), _endLocation(std::move(endLocation)) {}

    GS_NodeLocation GS_NodeLocation::Create(Lexer::GS_TokenLocation startLocation, Lexer::GS_TokenLocation endLocation) {
        return GS_NodeLocation(std::move(startLocation), std::move(endLocation));
    }

    GS_NodeLocation GS_NodeLocation::Create(Lexer::GS_TokenLocation location) {
        return GS_NodeLocation::Create(location, location);
    }

    GS_NodeLocation GS_NodeLocation::Create() {
        return GS_NodeLocation::Create(Lexer::GS_TokenLocation::Create(). Lexer::GS_TokenLocation::Create());
    }

    Lexer::GS_TokenLocation GS_NodeLocation::GetStartLocation() const {
        return _startLocation;
    }

    Lexer::GS_TokenLocation GS_NodeLocation::GetEndLocation() const {
        return _endLocation;
    }

    // TODO create new node constructor with node location

    GS_Node::GS_Node()
            : GS_Node(GS_NodeLocation::Create()) {}

    GS_Node::GS_Node(GS_NodeLocation location)
            : _location(std::move(location)) {}

    GS_Node::~GS_Node() = default;

    GS_NodeLocation GS_Node::GetLocation() const {
        return _location;
    }

    Bool GS_Node::IsDeclaration() const {
        return false;
    }

    Bool GS_Node::IsStatement() const {
        return false;
    }

    Bool GS_Node::IsExpression() const {
        return false;
    }

}
