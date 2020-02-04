# Boolean Tester
Command line tool to generate truth table for boolean expressions

## Installation
On Linux run the following in the dndice directory, it requires root access:

	./install.sh

## Usage
Once installed, the boolean tester can be used by running:

	bool-test [options] [expressions]


### Options
`--version`
Prints version information.

`--help, -h`
Prints a help menu.

`--verbose, -v`
Print out formatted expressions, this is the default when expressions are entered as command line parameters/


### Expressions
Expressions can either be entered as command line parameters or when prompted. When entering expressions into the prompt you can start evaluation by entering '#' or 'done'.

Expressions are composed of variables (any lowercase English letter) and operaters. Operators must be all uppercase, and are listed in their order of evaluation. Two variables placed directly next to eachother will be assume to have and `AND` operater between them.

| Operator  | Usage |
| --------: | :---- |
| `()`      | Forces order of evaluation |
| `NOT` `!` `~` | Negation |
| `NAND`    | Negated conjunction (NOT AND) |
| `AND` `&` `*` | Conjunction |
| `NOR`     | Negated disjunction (NOT OR) |
| `OR` `|` `+`  | Disjunction |
| `XNOR` `=`  | Equivilence` ` or negated exclusive OR (NOT XOR) |
| `XOR`     | Exclusive OR |


## Python version
I originally wrote this tool in python, this older version is also included in the repository (in the `python/` folder)
