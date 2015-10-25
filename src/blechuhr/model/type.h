#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <type_traits>

namespace hypha {
namespace blechuhr {

/**
 * @brief The RTYPE enum
 * Rules Types
 */
enum class RTYPE {
    WORKING,
    PAUSE,
    HOLIDAY,
    SICK,
    OTHER,
    FIRST=WORKING, LAST=OTHER
};

enum class TYPE {
    WORKING,
    PAUSE,
    HOLIDAY,
    SICK,
    OTHER,
    FIRST=WORKING, LAST=OTHER
};

/**
 * @brief The ITYPE enum
 */
enum class ITYPE {
    WORKINGMON,
    WORKINGTUE,
    WORKINGWED,
    WORKINGTHU,
    WORKINGFRI,
    WORKINGSAT,
    WORKINGSUN,
    FIRST=WORKINGMON, LAST=WORKINGSUN
};

inline const std::string TypeToString(TYPE t) {
    switch(t) {
    case TYPE::WORKING:
        return "working";
    case TYPE::PAUSE:
        return "pause";
    case TYPE::HOLIDAY:
        return "holiday";
    case TYPE::SICK:
        return "sick";
    case TYPE::OTHER:
        return "other";
    }
    return "other";
}

inline const std::string RTypeToString(RTYPE t) {
    switch(t) {
    case RTYPE::WORKING:
        return "working";
    case RTYPE::PAUSE:
        return "pause";
    case RTYPE::HOLIDAY:
        return "holiday";
    case RTYPE::SICK:
        return "sick";
    case RTYPE::OTHER:
        return "other";
    }
    return "other";
}

inline const std::string ITypeToString(ITYPE t) {
    switch(t) {
    case ITYPE::WORKINGMON:
        return "workingmon";
    case ITYPE::WORKINGTUE:
        return "workingtue";
    case ITYPE::WORKINGWED:
        return "workingwed";
    case ITYPE::WORKINGTHU:
        return "workingthu";
    case ITYPE::WORKINGFRI:
        return "workingfri";
    case ITYPE::WORKINGSAT:
        return "workingsat";
    case ITYPE::WORKINGSUN:
        return "workingsun";
    }
    return "workingsun";
}

inline const TYPE StringToType(std::string t) {
    if(t == "working")return TYPE::WORKING;
    if(t == "pause") return TYPE::PAUSE;
    if(t == "holiday") return TYPE::HOLIDAY;
    if(t == "sick") return TYPE::SICK;
    if(t == "other") return TYPE::OTHER;
    return TYPE::OTHER;
}

inline const RTYPE StringToRType(std::string t) {
    if(t == "working")return RTYPE::WORKING;
    if(t == "pause")return RTYPE::PAUSE;
    if(t == "holiday") return RTYPE::HOLIDAY;
    if(t == "sick") return RTYPE::SICK;
    if(t == "other") return RTYPE::OTHER;
    return RTYPE::OTHER;
}

inline const ITYPE StringToIType(std::string t) {
    if(t == "workingmon")return ITYPE::WORKINGMON;
    if(t == "workingtue")return ITYPE::WORKINGTUE;
    if(t == "workingwed")return ITYPE::WORKINGWED;
    if(t == "workingthu")return ITYPE::WORKINGTHU;
    if(t == "workingfri")return ITYPE::WORKINGFRI;
    if(t == "workingsat")return ITYPE::WORKINGSAT;
    if(t == "workingsun")return ITYPE::WORKINGSUN;
    return ITYPE::WORKINGSUN;
}

inline TYPE operator++(TYPE& t) {
    return t = (TYPE)(std::underlying_type<TYPE>::type(t) + 1);
}
inline TYPE operator*(TYPE t) {
    return t;
}
inline TYPE begin(TYPE t) {
    return TYPE::FIRST;
}
inline TYPE end(TYPE t)   {
    return TYPE(int(TYPE::LAST) + 1);
}

inline RTYPE operator++(RTYPE& t) {
    return t = (RTYPE)(std::underlying_type<RTYPE>::type(t) + 1);
}
inline RTYPE operator*(RTYPE t) {
    return t;
}
inline RTYPE begin(RTYPE t) {
    return RTYPE::FIRST;
}
inline RTYPE end(RTYPE t)   {
    return RTYPE(int(RTYPE::LAST) + 1);
}

inline ITYPE operator++(ITYPE& t) {
    return t = (ITYPE)(std::underlying_type<ITYPE>::type(t) + 1);
}
inline ITYPE operator*(ITYPE t) {
    return t;
}
inline ITYPE begin(ITYPE t) {
    return ITYPE::FIRST;
}
inline ITYPE end(ITYPE t)   {
    return ITYPE(int(ITYPE::LAST) + 1);
}

}
}



#endif // TYPE_H
