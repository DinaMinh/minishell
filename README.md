*This project has been created as part of the 42 curriculum by ebourdet, dminh.*

## Description
Minishell is a project from the 42 curriculum that challenges us to create our own minimal, bash-like shell. The main goal is to understand how a shell processes user input, interacts with the operating system, and executes processes using system calls.

Our implementation features a custom lexer and parser that break down user input into manageable tokens (words, operators, filenames). Key features of our shell include:
* **Command Execution:** Locating binaries using the `PATH` environment variable or absolute/relative paths.
* **Pipes and Redirections:** Chaining commands with pipes (`|`) and handling standard input/output redirections (`<`, `>`, `<<`, `>>`), including a robust heredoc system.
* **Built-ins:** Fully functional built-in commands implemented from scratch: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
* **Environment Variables:** Expansion of environment variables (like `$USER` or `$?`) and management of local variables.
* **Signal Handling:** Proper behavior for `SIGINT` and `SIGQUIT` in interactive mode, during execution, and inside heredocs.

## Instructions

### Compilation
To compile the project, navigate to the root of the repository and run:
```bash
make
```
### Execution
Start the interactive shell by running:
```bash
./bin/minishell
```
To exit the project, typing the exit built-in command (you can optionally provide a specific exit status, e.g., exit 42) or
Pressing Ctrl + D (EOF) on an empty prompt.
Pressing Ctrl + C will safely interrupt the current process and return you to a fresh new prompt, while Ctrl + \ does nothing in interactive mode, accurately replicating bash's behavior.

### Usage Examples
Here are a few examples of what you can execute in our Minishell:

* Simple commands with arguments and quotes:
```bash
minishell$ echo -n "Hello, 42!"
Hello, 42!minishell$ ls -la
```
* Chain multiple commands and redirect input/output seamlessly :
```bash
minishell$ cat Makefile | grep "CC" > compiler_info.txt
minishell$ wc -l < compiler_info.txt
minishell$ cat existing_file.txt >> appended_file.txt
```

* Use our robust heredoc implementation (which safely handles temporary files and signals):
```bash
minishell$ cat << EOF
> This is a multi-line input
> testing the heredoc feature
> EOF
```

* Expand variables (including the $? exit status) and create your own:
```bash
minishell$ export GREETING="Welcome to Minishell"
minishell$ echo $GREETING
Welcome to Minishell
minishell$ false
minishell$ echo "Last command exit status: $?"
Last command exit status: 1
```
## Resources

* **GNU Bash Reference Manual:** Used to replicate standard shell behaviors, built-in specifications, and exit codes.
* **GNU Readline Library Documentation:** Used for managing the interactive prompt, line reading, and command history.
* **Linux Programmer's Manual (man pages):** Consulted extensively for understanding and implementing system calls such as `fork`, `execve`, `pipe`, `dup2`, `signal` etc...
* **Stackoverflow:** For specific cases.
* **Other stud:** Discussing the cases to handle, finding and fixing bugs, and discussing how Bash works.

**AI Usage:**
* Generative AI (Gemini):
* **Debugging:** Discussing edge cases to handle, finding and fixing bugs
* **Concept Clarification:** Helping to understand the actual behavior of Bash to avoid errors.
* **Documentation:** Used to generate the structural template and formatting of this README file.