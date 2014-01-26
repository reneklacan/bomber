#ifndef __BOMBER_MACROS
#define __BOMBER_MACROS

#define SYNTHESIZE(varType, varName, funName)\
public: inline varType get##funName(void) const { return varName; }\
public: inline void set##funName(varType var){ varName = var; }\
protected: varType varName;

#define SYNTHESIZE_READONLY(varType, varName, funName)\
public: inline varType get##funName(void) const { return varName; }\
protected: varType varName;

#define SYNTHESIZE_STATS(varType, varName, funName)\
public: inline varType get##funName##s(void) const { return varName; }\
public: inline void note##funName(void){ varName += 1; }\
protected: varType varName;

#endif
