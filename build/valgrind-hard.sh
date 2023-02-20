#!/usr/bin/bash
valgrind -s --track-origins=yes --leak-check=full --suppressions=valgrind.supr "$@"
