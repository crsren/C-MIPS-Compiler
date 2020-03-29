#if !defined(TYPE_SPECIFIER)
#define TYPE_SPECIFIER

#include "helpers.h"

#include <list>

// Class of Declaration Specifiers
// class TypeSpecifier
// {
//     const std::string type;
//     // Void,Char,Int,Float,Double,Signed,Unsigned,Enum,Struct,Typename,Typedef -> !! lets only do void int and not much more for now
// public:
//     TypeSpecifier(const std::string t) : type(t){};
// }

//TODO: List of declaration specifiers (RIGHT NOW WE ONLY PASS A SINGLE SPECIFIER STRING)
// class SpecifierList
// {
//     std::list<const std::string *> sList;

// public:
//     SpecifierList(const std::string *stringPtr)
//     {
//         sList.push_back(stringPtr);
//     }

//     void add(const std::string *stringPtr)
//     {
//         sList.push_back(stringPtr);
//     }
// };

#endif // TYPE_SPECIFIER
