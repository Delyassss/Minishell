# 🐚 Minishell

## 📌 Overview

**Minishell** is a project from the 42 curriculum where you build a simple Unix shell from scratch in C.
The goal is to understand how shells like Bash work by implementing command parsing, execution, and environment handling.

---

## 🎯 Objectives

* Reproduce basic behavior of a Unix shell
* Understand process creation and management
* Learn about file descriptors, pipes, and signals
* Handle user input and parsing

---

## ⚙️ Features

### ✅ Mandatory

* Display a prompt and wait for user input
* Execute commands with arguments (e.g. `ls -l`)
* Handle environment variables (`$PATH`, `$HOME`, etc.)
* Implement built-in commands:

  * `echo`
  * `cd`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`
* Handle pipes (`|`)
* Handle redirections:

  * `>` (output)
  * `>>` (append)
  * `<` (input)
* Signal handling:

  * `Ctrl+C`
  * `Ctrl+D`
  * `Ctrl+\`

---

## 🧠 Concepts Learned

* Processes (`fork`, `execve`, `wait`)
* File descriptors & redirection
* Parsing and tokenization
* Signals (`signal`, `sigaction`)
* Environment variables management
* Memory management in C

---

## 🚀 Usage

### 1. Compile

```bash
make
```

### 2. Run

```bash
./minishell
```

---

## 🧪 Example

```bash
$> echo Hello World
Hello World

$> ls | grep minishell
minishell

$> export NAME=42
$> echo $NAME
42
```

---

## ⚠️ Notes

* Minishell does **not** need to implement every Bash feature
* Behavior should mimic Bash as closely as required by the subject
* Memory leaks must be avoided

---

## 👨‍💻 Authors

* Your Name (Ilyass Dabounou)

---

## 📚 References

* Unix manual pages (`man`)
* Bash behavior testing
* 42 subject PDF

---

## 📝 License

This project is part of the 42 School curriculum and is intended for educational purposes.
