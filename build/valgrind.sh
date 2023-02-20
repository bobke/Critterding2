#!/usr/bin/bash
valgrind --suppressions=valgrind.supr "$@"
