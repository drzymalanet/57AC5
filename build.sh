#! /usr/bin/env sh

# 57AC5 - A simple stack implementation - Marcin Drzymala

gcc status.h status.c stack.h stack.c test.c -o test
chmod a+x test
./test
