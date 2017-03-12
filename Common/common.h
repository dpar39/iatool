#ifndef COMMON_H
#define COMMON_H

#include <memory>

#define DEFINE(classname) \
    class classname; \
    typedef std::shared_ptr<classname> classname##SPtr;

#define DEFINE_VECTOR(classname) \
    typedef std::vector<classname> classname##Vector; \
    typedef std::vector<std::shared_ptr<classname>> classname##SPtrVec; \
    typedef std::shared_ptr<std::vector<std::shared_ptr<classname>>> classname##SPtrVecSPtr;

#define DEFINE_LIST(classname) \
    typedef std::list<classname> classname##List; \
    typedef std::list<std::shared_ptr<classname>> classname##SPtrList; \
    typedef std::shared_ptr<std::list<std::shared_ptr<classname>>> classname##SPtrListcSPtr;

#define DEFINE_DEQUE(classname) \
    typedef std::deque<classname> classname##Deque; \
    typedef std::deque<std::shared_ptr<classname>> classname##SPtrDeque; \
    typedef std::shared_ptr<std::deque<std::shared_ptr<classname>>> classname##SPtrDequeSPtr;

#define MAKE_SHARED_FRIEND(classname) \
    friend std::shared_ptr<classname> std::make_shared<classname>()

#endif // COMMON_H
