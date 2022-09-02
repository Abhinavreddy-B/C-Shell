# OSN Assignment 1
# File structure
```
.
├── main
├── main.c
├── headers.h
├── makefile
├── README.md
├── commands
│   ├── commands.h
│   │
│   ├── cd.c
│   ├── discover.c
│   ├── echo.c
│   ├── history.c
│   ├── ls.c
│   ├── pinfo.c
│   └── pwd.c
│
├── Helpers
│   ├── Helpers.h
│   │
│   ├── check_invalid.c
│   ├── command_helper.c
│   ├── getinfo.c
│   ├── History.c
│   └── process_creation.c
│
├── Linked_list
│   └── Linked list adt
│
└── io_module
    ├── print_error.h
    ├── prompt.h
    │
    ├── print_error.c
    └── prompt.c
```
## folder structure:
 > `commands:` contains implementations of built-in commands

 > `Helpers:` contains some helper functions 

 > `Linked_list:` contains ADT for linked list (used in storing background process data)

 > `io_module:` function for printing errors and prompt

## assumptions:
 * assumed all lengths such as  `Maximum input size`,`Maximum directory path length`,.... to be 1001