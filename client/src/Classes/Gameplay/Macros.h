#ifndef __BOMBER_MACROS
#define __BOMBER_MACROS

#define SYNTHESIZE(varType, varName, funName)\
public: inline varType get##funName(void) const { return varName; }\
public: inline void set##funName(varType var){ varName = var; }\
protected: varType varName;

#define SYNTHESIZE_READONLY(varType, varName, funName)\
public: inline varType get##funName(void) const { return varName; }\
protected: varType varName;

#endif
