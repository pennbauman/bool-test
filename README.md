# Boolean Tester
Python tool to general truth tables for boolean expersions

## Usage
Enter expesssions you would like to test, one per line. Enter a blank expression to start testing. Expressions must use lower case single letter variables and can use the following operations:

|   Symbol | Usage |
| -------: | :---- |
| `! ~ NOT` | Inversion |
| `* & AND` | Conjunction |
|      `xy` | Two variable placed adjacent to each other assume AND |
|  `+ | OR` | Disjunction |
|     `XOR` | Exclusive OR  |
|    `NAND` | NOT AND  |
|     `NOR` | NOT OR  |
|  `= XNOR` | NOT XOR, Equivilence |
|      `()` | Forces order of operations |

## Installation

#### Linux
Run (requires root access): 

    ./install.sh

and you can then run:

    bool-test

to run the tool.

#### Windows & Mac OS (or Linux without install)
Just run the python script by your prefered method.
