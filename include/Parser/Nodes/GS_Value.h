#ifndef GSLANGUAGE_GS_VALUE_H
#define GSLANGUAGE_GS_VALUE_H

#include <memory>
#include <any>

#include <CrossPlatform/GS_PlatformTypes.h>
#include <CrossPlatform/GS_ClassUtilities.h>

namespace GSLanguageCompiler::Parser {

    class GS_Value;

    typedef std::shared_ptr<GS_Value> GSValuePtr;

    /**
     * Base class for values
     */
    class GS_Value {
    public:

        /**
         * Constructor for all values
         * @tparam T Type of value
         * @param type String type
         * @param data Value
         */
        template<typename T>
        GS_Value(GSString type, T data)
                : _type(std::move(type)), _data(std::move(data)) {}

    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Value();

    public:

        /**
         * Getter for data value
         * @tparam T Type for getting
         * @return Value
         */
        template<typename T>
        T getData() {
            return std::any_cast<T>(_data);
        }

        GETTER_SETTER(GSString, _type, Type)

    private:

        /**
         * Container for value
         */
        std::any _data;

        /**
         * String type
         */
        GSString _type;
    };

}

#endif //GSLANGUAGE_GS_VALUE_H
