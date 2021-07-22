#ifndef GSLANGUAGE_GS_CLASSUTILITIES_H
#define GSLANGUAGE_GS_CLASSUTILITIES_H

/**
 * Macro for generating getter in class
 */
#define GETTER(type, name, getterVarName) \
    type get##getterVarName() {           \
        return _##name;                   \
    }

/**
 * Macro for generating setter in class
 */
#define SETTER(type, name, setterVarName) \
    void set##setterVarName(type name) {  \
        _##name = name;                   \
    }

/**
 * Macro for generating getter and setter in class
 */
#define GETTER_SETTER(fieldType, fieldName, methodFieldName)              \
    fieldType get##methodFieldName() {                                    \
        return fieldName;                                                 \
    }                                                                     \
                                                                          \
    void set##methodFieldName(const fieldType &input##methodFieldName) {  \
        (fieldName) = input##methodFieldName;                             \
    }

#endif //GSLANGUAGE_GS_CLASSUTILITIES_H
