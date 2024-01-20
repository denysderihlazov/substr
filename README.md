# Multifunctional Substring Finder

This program searches for a given substring within a file or standard input (stdin) and prints the line where the substring is found.

## Installation

Clone the repository to your local machine:
```sh
git clone git@github.com:denysderihlazov/substr.git
```
Navigate to the project directory:
```sh
cd <path_on_your_computer>/substr
```
Compile the program using GCC:
```sh 
gcc -Wall -g str.c -o str
```

## Usage

To search for a substring in text from a file or stdin:
 - ### Using a text file:
    Run the program with the substring and the name of the text file:
    ```sh
    ./str <substring> <file_name>
    ```
    ### Examples:
    - To find a substring in a file:
    ```sh
    ./str lo str.txt
    ```
     - To find and `print the first line` containing "lo" in 'str.txt':
    ```sh
    ./str lo str.txt grep
    ```
 - ### Using standard input (stdin):
    Run the program with the substring followed by the grep command to search through the text entered into stdin:
    ```sh
    ./str <substring>
    ```
    ### Examples:
    - To find a substring in a stdin:
    ```sh
    ./str lo
    ```
     - To find and `print the first line` containing "lo" from stdin:
    ```sh
    ./str lo grep
    ```
Replace <substring> with the text you are searching for. Replace <file_name> with the file you want to search through.

## Help
For usage instructions, you can run the program with -h or --help:
```sh
./str --help
```
This will display helpful information on how to use the program.

## Features
 - Searches for a substring in a text file or stdin.
- Prints the line containing the substring, functioning similarly to the `grep` command in Unix-based operating systems.
 - Handles large input by dynamically resizing the buffer.