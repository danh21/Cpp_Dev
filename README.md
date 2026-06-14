# 📦 Project Name

> C++ development

---

## 📚 Table of Contents

- [📦 Project Name](#-project-name)
  - [📚 Table of Contents](#-table-of-contents)
  - [📝 About](#-about)
  - [✨ Features](#-features)
  - [🚀 Getting Started](#-getting-started)
    - [Prerequisites](#prerequisites)
    - [Usage](#usage)
    - [Source](#source)
    - [Reference](#reference)

---

## 📝 About

> This is a repo about C++ dev

---

## ✨ Features

- ✅ SQL
  - SQLite3 Multiple Ciphers
  - SQLCipher
- ✅ memcpy, memset on complex struct
  - check similar behavior with placement_new, call destructor

---

## 🚀 Getting Started

### Prerequisites

- List software dependencies or system requirements here:
  - MCVC with C++ extensions, SDK, Cmake

### Usage

[Optional] Setup git hooks
- chmod +x setup-hooks.sh .githooks/prepare-commit-msg
- ./setup-hooks.sh

Open *.sln to activate MCVC workspace

### Source

**SQLite3_MulCiphers**
- git clone https://github.com/utelle/SQLite3MultipleCiphers
  - to src/SQLite3_MulCiphers/third_parties
- build SQL3_MC_lib DLL
- build and run test_func app

**SQLite3_MulCiphers**
- git clone https://github.com/sqlcipher/sqlcipher
  - to src/SQLcipher/third_parties
  - Open the Developer Command Prompt for VS 2022 at source
  - nmake /f Makefile.msc sqlite3.c
- Open .sln workspace
  - setup your OpenSSL dir in project properties, build sqlcipher_wrapper DLL
  - build and run app

### Reference

- https://github.com/utelle/SQLite3MultipleCiphers
- https://github.com/sqlcipher/sqlcipher