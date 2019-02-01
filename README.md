# Boolean Tester
Python tool to general truth tables for boolean expersions

## Usage
Enter expesssions you would like to test, one per line. Enter a blank expression to start testing. 

Supported Boolean Operations:
| Sysbol | Usage |
| -----: | :---- |
|  !,~,NOT | Inversion |
|  *,&,AND | Conjunction |
|    xy    | Two variable placed adjacent to each other assume AND |
|  +,|, OR | Disjunction |
|      XOR | Exclusive OR  |
|     NAND | NOT AND  |
|      NOR | NOT OR  |
|  =, XNOR | NOT XOR, Equivilence |
|  ()      | Forces order of operations |

## Installation

#### Linux
Run: 

    ./install.sh

and you can then use:

    bool-test

in any command line to run the tool.

#### Windows & Mac OS
Just run the python script by your prefered method.