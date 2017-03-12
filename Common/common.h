#ifndef COMMON_H
#define COMMON_H

#include <memory>

#define DEFINE(classname) \
    class classname; \
    typedef std::shared_ptr<classname> classname##SPtr;

#define MAKE_SHARED_FRIEND(classname) \
    friend std::shared_ptr<classname> std::make_shared<classname>()

#endif // COMMON_H
