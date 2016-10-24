//
// Created by moslab on 10/24/16.
//

#ifndef STUBAPP_SYSCALLS_H
#define SYSCALL_MAXARGS 6
enum argtype {
    ARG_INT,
    ARG_PTR,
    ARG_STR
};

struct syscall_entry {
    const char *name;
    int nargs;
    int args[SYSCALL_MAXARGS];
};
#define STUBAPP_SYSCALLS_H

#endif //STUBAPP_SYSCALLS_H
