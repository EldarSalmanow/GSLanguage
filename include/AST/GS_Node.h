#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for containing information about node location
     */
    class GS_NodeLocation {
    public:

        /**
         * Constructor for node location
         * @param startLocation Start token location
         * @param endLocation End token location
         */
        GS_NodeLocation(Lexer::GS_TokenLocation startLocation, Lexer::GS_TokenLocation endLocation);

    public:

        /**
         * Creating node location
         * @param startLocation Start token location
         * @param endLocation End token location
         * @return Node location
         */
        static GS_NodeLocation Create(Lexer::GS_TokenLocation startLocation, Lexer::GS_TokenLocation endLocation);

        /**
         * Creating node location
         * @param location Token location
         * @return Node location
         */
        static GS_NodeLocation Create(Lexer::GS_TokenLocation location);

        /**
         * Creating node location
         * @return Node location
         */
        static GS_NodeLocation Create();

    public:

        /**
         * Getter for start token location
         * @return Start token location
         */
        Lexer::GS_TokenLocation GetStartLocation() const;

        /**
         * Getter for end token location
         * @return End token location
         */
        Lexer::GS_TokenLocation GetEndLocation() const;

    private:

        /**
         * Start token location
         */
        Lexer::GS_TokenLocation _startLocation;

        /**
         * End token location
         */
        Lexer::GS_TokenLocation _endLocation;
    };

    /**
     * Base class for all AST nodes
     */
    class GS_Node {
    public:

        /**
         * Constructor for node
         */
        GS_Node();

        /**
         * Constructor for node
         * @param location Node location
         */
        explicit GS_Node(GS_NodeLocation location);

    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Node();

    public:

        /**
         * Getter for node location
         * @return Node location
         */
        GS_NodeLocation GetLocation() const;

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

    private:

        /**
         * Node location
         */
        GS_NodeLocation _location;
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
