# dfa-minimization &nbsp; [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/code-chaser/dfa-minimization/blob/main/LICENSE) [![Generic badge](https://img.shields.io/badge/Download-Code-purple.svg)](https://github.com/code-chaser/dfa-minimization/archive/refs/heads/main.zip)
___
## Introduction
a program that takes a dfa as input and outputs the minimum possible states dfa with the same language as the input dfa
___

<br>

## Instructions
___
#### BUILD & EXECUTE
Run the following commands in the root directory:
- Compilation: 
```bash
g++ -o "dfa-minimization" dfa-minimization.cpp
```
- Run the executable: 
```bash
./dfa-minimization
```
___
#### INPUTS
You need to provide following details of the dfa:
- number of states;
- size of alphabet;
- alphabet;
- transition table;
- index of initial state;
- number of final states;
- indices of final states;
___
#### OUTPUTS
Following details will be printed:
- reachable states in the input dfa;
- reachable non-final states of the input dfa;
- reachable final states of the input dfa;
- number of equivalence states partitions;
- all equivalence states partitions;
- transition table of the equivalent minimized states dfa;
___
___
