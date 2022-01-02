#ifndef CLONE_H
#define CLONE_H

long clone(unsigned long flags, void *stack, int *parent_tid, int *child_tid, unsigned long tls);

#endif