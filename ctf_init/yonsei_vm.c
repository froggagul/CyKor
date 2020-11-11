#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

#define RAX_NUM 0xf
#define RDI_NUM 0xe
#define RSI_NUM 0x3
#define RDX_NUM 0x1
#define RCX_NUM 0x9
#define R8_NUM 0x0
#define R9_NUM 0x4

#define OP_ADD 0x0
#define OP_SUB 0x1
#define OP_MUL 0x2
#define OP_DIV 0x3
#define OP_MOV 0x4
#define OP_PUSH 0x6
#define OP_POP 0x7
#define OP_HLT 0xf4
#define OP_NOP 0x90
#define OP_SYSCALL 0xff

typedef unsigned char bool;
typedef unsigned char _BYTE;
typedef unsigned long long int _QWORD;

typedef struct _STACK {
    _QWORD stack[0x20];
    _QWORD *bottom;
    _QWORD *top;
    _QWORD *sp;
    bool (*isEmpty)(struct _STACK *stack);
    bool (*isFull)(struct _STACK *stack);
    void (*push)(struct _STACK *stack, _QWORD value);
    void (*pop)(struct _STACK *stack, _BYTE reg);
} _STACK;

typedef struct REGISTER {
    _BYTE code[0x200];
    _BYTE *rip;
    _QWORD rax;
    _QWORD rdi;
    _QWORD rsi;
    _QWORD rdx;
    _QWORD rcx;
    _QWORD r8;
    _QWORD r9;
} REGISTER;

REGISTER REG;
_STACK STACK;

/*          STACK MANAGEMENT           */
bool isEmpty(_STACK *self);
bool isFull(_STACK *self);
void push(_STACK *self, _QWORD value);
void pop(_STACK *self, _BYTE reg);
/*          STACK MANAGEMENT           */

/*          OP CODE MANAGEMENT          */
void filter();
void exec();
void operAndMov(_BYTE opcode, _BYTE reg, _QWORD value);
void applyRegister();
/*          OP CODE MANAGEMENT          */



void error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(-1);
}

void readBuf(char *buf, size_t size) {
    int er;
    int sum = 0;
    int saved = size;
    do {
        er = read(0, buf, saved - sum);
        sum += er;
        buf += er;
        size -= er;
        if (er < 1) error("read error.");
    } while( size && saved - sum > 1);
}

bool checkRegister(_BYTE reg) {
    switch(reg) {
        case RAX_NUM:
        case RDI_NUM:
        case RSI_NUM:
        case RDX_NUM:
        case RCX_NUM:
        case R8_NUM:
        case R9_NUM: 
            return true;
        default:
            return false;   
    }
}

void initRegister() {
    REG.rip = REG.code;
    REG.rax = 0xc0dec0decafebabe;
    REG.rdi = 0xc0dec0decafebabe;
    REG.rsi = 0xc0dec0decafebabe;
    REG.rdx = 0xc0dec0decafebabe;
    REG.rcx = 0xc0dec0decafebabe;
    REG.r8 = 0xc0dec0decafebabe;
    REG.r9 = 0xc0dec0decafebabe;
}

void initStack() {
    STACK.bottom = STACK.stack;
    STACK.top = (_QWORD*)&STACK.bottom;
    STACK.sp = STACK.bottom;
    STACK.isEmpty = isEmpty;
    STACK.isFull = isFull;
    STACK.push = push;
    STACK.pop = pop;
}

void init() {
    setvbuf(stdin, 0LL, 2, 0LL);
    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stderr, 0LL, 2, 0LL);
    initStack();
    initRegister();
}

void readCode() {
    readBuf(REG.code, 0x201);
}

int main() {
    init();
    readCode();
    filter();
    exec();
    return 0;
}

bool isEmpty(_STACK *self) {
    return self->sp == self->bottom;
}

bool isFull(_STACK *self) {
    return self->sp == self->top;
}

void push(_STACK *self, _QWORD value) {
    if(self->isFull(self)) error("Stack overflow.");
    *self->sp = value;
    self->sp++;
}

void pop(_STACK *self, _BYTE reg) {
    if(self->isEmpty(self)) error("Stack is empty.");
    _QWORD value;
    self->sp--;
    value = *self->sp;
    switch(reg) {
        case RAX_NUM: 
            REG.rax = value;
            break;
        case RDI_NUM: 
            REG.rdi = value;
            break;
        case RSI_NUM: 
            REG.rsi = value;
            break;
        case RDX_NUM: 
            REG.rdx = value;
            break;
        case RCX_NUM: 
            REG.rcx = value;
            break;
        case R8_NUM: 
            REG.r8 = value;
            break;
        case R9_NUM: 
            REG.r9 = value;
            break;
        default: error("Invalid register");
    }
}

void filter() {
    _BYTE *ptr = REG.code;
    while(true) {
        if(ptr >= REG.code + 0x1f0) break;
        if(*ptr == OP_HLT) break;
        else if(*ptr == OP_ADD || *ptr == OP_SUB || *ptr == OP_MUL || *ptr == OP_DIV || *ptr == OP_MOV) {
            ptr += 1;
            if(checkRegister(*ptr)) ptr += 9;
            else error("Invalid register.");
        }
        else if(*ptr == OP_PUSH) ptr += 9;
        else if(*ptr == OP_POP) {
            ptr += 1;
            if(checkRegister(*ptr)) ptr += 1;
            else error("Invalid register.");
        }
        else if(*ptr == OP_NOP) ptr += 1;
        else if(*ptr == OP_SYSCALL) error("Syscall is not allow.");
        else error("Invalid instruction.");
    }
}

void exec() {
    _BYTE reg, opcode;
    _QWORD value;
    applyRegister();
    while(true) {
        if(REG.rip >= REG.code + 0x1f0) break;
        opcode = *REG.rip;
        if(opcode == OP_HLT) break;
        else if(opcode == OP_ADD || opcode == OP_SUB || opcode == OP_MUL || opcode == OP_DIV || opcode == OP_MOV) {
            REG.rip += 1;
            reg = *REG.rip;
            if(checkRegister(reg)) {
                REG.rip += 1;
                value = *(_QWORD*)REG.rip;
                REG.rip += 8;
                operAndMov(opcode, reg, value);
            }
            else error("Invalid register.");
        }
        else if(opcode == OP_PUSH) {
            REG.rip += 1;
            value = *(_QWORD*)REG.rip; 
            REG.rip += 8;
            STACK.push(&STACK, value);
        }
        else if(opcode == OP_POP) {
            REG.rip += 1;
            reg = *REG.rip;
            if(checkRegister(reg)) { 
                REG.rip += 1;
                STACK.pop(&STACK, reg);
            }
            else error("Invalid register.");
        }
        else if(opcode == OP_NOP) REG.rip += 1;
        else if(opcode == OP_SYSCALL) {
            REG.rip += 1;
            applyRegister();
            asm("syscall");
        }
        else error("Invalid instruction.");
    }
}

void operAndMov(_BYTE opcode, _BYTE reg, _QWORD value) {
    _QWORD *reg_ptr;
    if(reg == RAX_NUM) reg_ptr = &REG.rax;
    else if(reg == RDI_NUM) reg_ptr = &REG.rdi;
    else if(reg == RSI_NUM) reg_ptr = &REG.rsi;
    else if(reg == RDX_NUM) reg_ptr = &REG.rdx;
    else if(reg == RCX_NUM) reg_ptr = &REG.rcx;
    else if(reg == R8_NUM) reg_ptr = &REG.r8;
    else if(reg == R9_NUM) reg_ptr = &REG.r9;
    else error("Invalid register.");

    if(opcode == OP_ADD) *reg_ptr += value;
    else if(opcode == OP_SUB) *reg_ptr -= value;
    else if(opcode == OP_MUL) *reg_ptr *= value;
    else if(opcode == OP_DIV) *reg_ptr /= value;
    else if(opcode == OP_MOV) *reg_ptr = value;
    else error("Invalid instruction.");
}

void applyRegister() {
    __asm__ volatile ("mov %0, %%rax;" : "=m" ( REG.rax ));
    __asm__ volatile ("mov %0, %%rdi;" : "=m" ( REG.rdi ));
    __asm__ volatile ("mov %0, %%rsi;" : "=m" ( REG.rsi ));
    __asm__ volatile ("mov %0, %%rdx;" : "=m" ( REG.rdx ));
    __asm__ volatile ("mov %0, %%rcx;" : "=m" ( REG.rcx ));
    __asm__ volatile ("mov %0, %%r8;" : "=m" ( REG.r8 ));
    __asm__ volatile ("mov %0, %%r9;" : "=m" ( REG.r9 ));
}