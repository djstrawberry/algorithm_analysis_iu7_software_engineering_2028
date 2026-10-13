#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <stdlib.h>
#include "array_utils.h"
#include "menu.h"

void dispatch_menu_choice(int choice, int *arr, const int *sorted, size_t size);

#endif