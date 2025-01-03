#ifndef COMPILER_H
#define COMPILER_H

#include <stdlib.h>
#include "instruction.h"
//#include "hash.h"
#include "statement.h"
#include "diag.h"

typedef struct {
    Identifier ident;
    const Type* type;
    int depth;
    size_t offset;
} StackElement;

struct Compiler;

typedef struct {
    struct Compiler* compiler;
    Arena* lifetime;
    Diagnostics* diag;
    const FunctionDeclaration* decl;
    Instruction* instructions;
    size_t instructionsLength;
    size_t instructionsCapacity;
    StackElement* stack;
    size_t stackLength;
    size_t stackCapacity;
    size_t currentStackSize;
    size_t maxStackSize;
    int scopeDepth;
} Function;

typedef struct {
    Identifier name;
    Declaration* decl;
} Global;

typedef struct Compiler {
    Arena* lifetime;
    Diagnostics* diag;
    int label;
    //Set globals;
    int globalCount;
    Declaration* const* globals;
} Compiler;

Compiler compilerNew(Arena* staticLifetime, Diagnostics* diag, Declaration* const* declarations);
Function functionNew(Compiler* compiler, const FunctionDeclaration* decl);

void emitImplied(Function* func, Opcode opcode);
void emitReg(Function* func, Opcode opcode, Reg reg);
void emitValue(Function* func, Opcode opcode, Value value, int index);
void emitRegReg(Function* func, Opcode opcode, Reg dest, Reg src);
void emitRegValue(Function* func, Opcode opcode, Reg dest, Value src, int index);
void emitValueReg(Function* func, Opcode opcode, Value dest, int index, Reg src);
void emitRegIndexed(Function* func, Opcode opcode, Reg dest);
void emitIndexedReg(Function* func, Opcode opcode, Reg src);
void emitLabel(Function* func, Value label);

void load(Function* func, Reg reg, Value src, int index);
void store(Function* func, Value dest, int index, Reg reg);
void transfer(Function* func, Reg dest, Reg src);

Value createLabel(Compiler* compiler);

Value pushStack(Function* func, const Type* type, Identifier ident);
Value pushStackAnon(Function* func, const Type* type, Location location);
void popStack(Function* func);

void emitJump(Function* func, Value value);
void conditionalJump(Function* func, Condition condition, Value value);

void enterScope(Function* func);
void leaveScope(Function* func);

const Declaration* lookupGlobal(Compiler* compiler, Identifier ident);
Value lookupSymbol(Function* func, Identifier ident);

Value getFuncReturnValue(Arena* arena, const FunctionDeclaration* decl, Location location);

#endif

