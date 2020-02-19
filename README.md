# Boolean Tester
Command line tool to generate truth table for boolean expressions

## Installation
On Linux run the following in the bool-test directory, it requires root access:

	./install.sh

## Usage
Once installed, the boolean tester can be used by running:

	bool-test [options] [expressions]


### Options
`--version`
Prints version information.

`--help` or `-h`
Prints a help menu.

`--verbose` or `-v`
Print out formatted expressions, this is the default when expressions are entered as command line parameters/

`--no-compare` or `-n`
Stop printing of a list of expression equalities after the truth table.


### Expressions
Expressions can either be entered as command line parameters or when prompted. When entering expressions into the prompt you can start evaluation by entering a blank.

Expressions are composed of variables (any lowercase English letter) and operators. Operators must be all uppercase, and are listed in their order of evaluation. Two variables placed directly next to each other will be assume to have and `AND` operator between them.

| Operator  | Usage |
| --------: | :---- |
| `()`      | Forces order of evaluation |
| `NOT` `!` `~` | Negation |
| `AND` `&` `*` | Conjunction |
| `NAND`    | Negated conjunction (not and) |
| `OR` `\|` `+`  | Disjunction |
| `NOR`     | Negated disjunction (not or) |
| `XOR`     | Exclusive or |
| `XNOR` `=`  | Equivalence or negated exclusive or (not xor) |


## Python version
I originally wrote this tool in python, this older version is also included in the repository (in the `python/` folder)
