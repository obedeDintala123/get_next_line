*This project has been created as part of the 42 curriculum by obdintal.*

# GET_NEXT_LINE

## Description

**Get Next Line** is a project focused on reading and returning a single line from a file descriptor at a time.

The main goal of the project is to understand how file descriptors and the `read()` function work in C, while learning how to manage data that may need to persist between multiple function calls.

The function must be capable of reading from a file descriptor and returning the next available line, including the newline character (`\n`) when present.

## New Concepts

### Static Variables

A static variable allows data to persist between function calls.

In **Get Next Line**, this concept is particularly important because `read()` may retrieve more data than is needed for the current line. The remaining data must be preserved so it can be used when the function is called again.

### File Descriptors

A file descriptor (FD) is an integer used by the operating system to identify an open file or another input/output resource.

For this project, file descriptors are used to identify the source from which `get_next_line()` reads data.

Common examples include:

* `0` — Standard input
* `1` — Standard output
* `2` — Standard error

### `open()`

The `open()` function is used to open a file and obtain its file descriptor.

### `read()`

The `read()` function is responsible for reading a specified amount of data from a file descriptor into a buffer.

Understanding how `read()` behaves is essential for implementing `get_next_line()` correctly.

## Function

The main function implemented by this project is:

```c
char *get_next_line(int fd);
```

Each call returns the next line available from the given file descriptor.

For example:

```text
First line
Second line
Third line
```

Successive calls to `get_next_line()` return:

```text
First line\n
Second line\n
Third line\n
```

## BUFFER_SIZE

The project uses the `BUFFER_SIZE` macro to determine how many bytes are read at a time.

For example:

```bash
cc -D BUFFER_SIZE=42 ...
```

## Project Structure

```text
get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── get_next_line_bonus.c
├── get_next_line_utils_bonus.c
├── get_next_line_bonus.h
└── README.md
```

## Instructions

The project can be compiled with a custom `BUFFER_SIZE`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c
```

For the bonus part:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line_bonus.c get_next_line_utils_bonus.c
```

## Resources

* [42 Cursus — Open and Read](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line/open-and-read)
* [Educative — Read Data from a File Using `read()` in C](https://www.educative.io/answers/read-data-from-a-file-using-read-in-c)
* [GeeksforGeeks — Static Variables in C](https://www.geeksforgeeks.org/c/static-variables-in-c/)
* [42 Cursus — File Descriptors](https://42-cursus.gitbook.io/guide/useful-tools/file-descriptors-fd)

---

## AI Usage

This project made use of AI tools (ChatGPT/Claude) for:

* Clarifying documentation and man pages

* Debugging support and explaining error messages

* Reviewing code style and readability

* Creating illustrative guides on specific topics
