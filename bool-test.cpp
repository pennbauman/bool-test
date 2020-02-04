// Penn Bauman
// pennbauman@protonmail.com
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

// Parse-tree node
struct node {
	string data;
	node* left;
	node* right;
};


// Print help information
void printHelp() {
	cout << "Usage: bool-test [options] [expressions]" << endl;
	cout << "  --version         Prints version information" << endl;
	cout << "  --help, -h        Print this help menu" << endl;
	cout << "  --verbose, -v     Print out formatted expressions, default with command line input" << endl;
	cout << "  --no-compare, -n  Removes expression comparisions after the truth table" << endl;
	cout << endl;
	cout << "Expressions: " << endl;
	cout << "  Expressions can either be entered as command line parameters or when prompted." << endl;
	cout << "  When entering expressions into the prompt you can start evaluation by entering a blank." << endl;
	cout << "  Expressions are composed of variables (any lowercase English letter) and operators." << endl;
	cout << "  Operators must be all uppercase, and are listed in their order of evaluation." << endl;
	cout << "    ()         Forces order of evaluation" << endl;
	cout << "    NOT, !, ~  Negation" << endl;
	cout << "    NAND       Negated conjunction (not and)" << endl;
	cout << "    AND, &, *  Conjunction" << endl;
	cout << "    NOR        Negated disjunction (not or)" << endl;
	cout << "    OR, |, +   Disjunction" << endl;
	cout << "    XNOR, =    Equivalence or negated exclusive or (not xor)" << endl;
	cout << "    XOR        Exclusive or" << endl;
}

// Recursive construct parse-tree
node* parse(string s) {
	//cout << "parse: '" << s << "'" << endl;
	/* Order of operations
	*   reverse in if statements
	* NOT
	* NAND
	* AND
	* NOR
	* OR
	* EQV, XNOR
	* XOR
	* IMP, not implemented
	*/
	if (s.size() == 0)
		return NULL;
	node* fin = new node;
	int p;
	// Single variables
	if (s.size() == 1) {
		if ((s[0] > 96) && (s[0] < 123)) {
			fin->data = s;
			fin->left = NULL;
			fin->right = NULL;
			return fin;
		}
		return NULL;
	}
	// Check parentheses
	if ((s[0] == '(') && (s[s.size() -1] == ')'))
		return parse(s.substr(1, s.size() - 2));
	// IMP
	// ! NOT IMPLEMENTED

	// XOR
	p = 0;
	for (int i = 1; i < s.size()-1; i++) {
		if (s[i] == '(')
			p++;
		if (s[i] == ')')
			p--;
		if (p == 0) {
			if (s.substr(i,3) == "XOR") {
				fin->data = "XOR";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+3));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
		}
	}
	// EQV, XNOR
	p = 0;
	for (int i = 1; i < s.size()-1; i++) {
		if (s[i] == '(')
			p++;
		if (s[i] == ')')
			p--;
		if (p == 0) {
			if (s[i] == '=') {
				fin->data = "XNOR";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+1));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
			if (s.substr(i,4) == "XNOR") {
				fin->data = "XNOR";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+4));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
		}
	}
	// OR
	p = 0;
	for (int i = 1; i < s.size()-1; i++) {
		if (s[i] == '(')
			p++;
		if (s[i] == ')')
			p--;
		if (p == 0) {
			if ((s[i] == '+') || (s[i] == '|')) {
				fin->data = "OR";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+1));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
			if (s.substr(i,2) == "OR") {
				fin->data = "OR";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+2));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
		}
	}
	// NOR
	p = 0;
	for (int i = 1; i < s.size()-1; i++) {
		if (s[i] == '(')
			p++;
		if (s[i] == ')')
			p--;
		if (p == 0) {
			if (s.substr(i,3) == "NOR") {
				fin->data = "NOR";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+3));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
		}
	}
	// AND
	p = 0;
	for (int i = 1; i < s.size()-1; i++) {
		if (s[i] == '(')
			p++;
		if (s[i] == ')')
			p--;
		if (p == 0) {
			if ((s[i] == '*') || (s[i] == '&')) {
				fin->data = "AND";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+1));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
			if (s.substr(i,3) == "AND") {
				fin->data = "AND";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+3));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
		}
	}
	// NAND
	p = 0;
	for (int i = 1; i < s.size()-1; i++) {
		if (s[i] == '(')
			p++;
		if (s[i] == ')')
			p--;
		if (p == 0) {
			if (s.substr(i,4) == "NAND") {
				fin->data = "NAND";
				fin->left = parse(s.substr(0,i));
				fin->right = parse(s.substr(i+4));
				if ((fin->left == NULL) || (fin->right == NULL))
					return NULL;
				return fin;
			}
		}
	}
	// NOT
	if ((s[0] == '!') || (s[0] == '~')) {
		if ((s.size() == 2) || (s[1] == '(')) {
			fin->data = "NOT";
			fin->left = NULL;
			fin->right = parse(s.substr(1));
			if (fin->right == NULL)
				return NULL;
			return fin;
		} else {
			fin->data = "AND";
			fin->left = parse(s.substr(0,2));
			fin->right = parse(s.substr(2));
			if ((fin->left == NULL) || (fin->right == NULL))
				return NULL;
			return fin;
		}
	}
	if (s.substr(0,3) == "NOT") {
		if ((s.size() == 4) || (s[3] == '(')) {
			fin->data = "NOT";
			fin->left = NULL;
			fin->right = parse(s.substr(4));
			if (fin->right == NULL)
				return NULL;
			return fin;
		} else {
			fin->data = "AND";
			fin->left = parse(s.substr(0,4));
			fin->right = parse(s.substr(4));
			if ((fin->left == NULL) || (fin->right == NULL))
				return NULL;
			return fin;
		}
	}
	// Symbolless AND
	if (s.size() < 2)
		return NULL;
	fin->data = "AND";
	fin->left = parse(s.substr(0,1));
	fin->right = parse(s.substr(1));
	if ((fin->left == NULL) || (fin->right == NULL))
		return NULL;
	return fin;
}

// Print out parse-tree (with neat parentheses)
void printTree(node* n) {
	if (n == NULL)
		return;
	if ((n->left != NULL) || (n->right != NULL))
		cout << "(";
	printTree(n->left);
	if (n->left != NULL)
		cout << " ";
	cout << n->data;
	if (n->right != NULL)
		cout << " ";
	printTree(n->right);
	if ((n->left != NULL) || (n->right != NULL))
		cout << ")";
}

// Evaluate parse-tree recursively
bool evaluate(node* n, bool vars[]) {
	// NULL node error (should never happen)
	if (n == NULL) {
		cout << "NULL in evaluation (there is a logic error in this program)" << endl;
		return false;
	}
	// Check if variable
	if (n->data.size() == 1) {
		return vars[n->data[0]];
	}
	// Check operations
	if (n->data == "NOT")
		return !evaluate(n->right, vars);
	if (n->data == "AND")
		return evaluate(n->left, vars) && evaluate(n->right, vars);
	if (n->data == "NAND")
		return !(evaluate(n->left, vars) && evaluate(n->right, vars));
	if (n->data == "OR")
		return evaluate(n->left, vars) || evaluate(n->right, vars);
	if (n->data == "NOR")
		return !(evaluate(n->left, vars) || evaluate(n->right, vars));
	if (n->data == "XOR")
		return evaluate(n->left, vars) ^ evaluate(n->right, vars);
	if (n->data == "XNOR")
		return evaluate(n->left, vars) == evaluate(n->right, vars);
	// Unknown operation error (should never happen)
	cout << "Unknown operator '" << n->data << "' (there is a logic error in this program)" << endl;
	return false;
}


int main(int argc, char* argv[]) {
	// Check command line parameters
	string current, total;
	bool vars_values[26];
	vector<node*> trees;
	bool options[] = {
		false, // --verbose, -v
		true, // --no-compate, -n
	};
	for (int i = 1; i < argc; i++) {
		current = argv[i];
		if (current == "--version") {
			cout << "Boolean Tester version 0.1" << endl;
			return 0;
		} else if ((current == "--help") || (current == "-h")) {
			printHelp();
			return 0;
		} else if ((current == "--verbose") || (current == "-v")) {
			options[0] = true;
		} else if ((current == "--no-compare") || (current == "-n")) {
			options[1] = false;
		} else {
			for (int i = 0; i < current.size(); i++) {
				if (current[i] == ' ') {
					current = current.substr(0,i) + current.substr(i+1);
					i--;
				}
			}
			trees.push_back(parse(current));
			if (trees[trees.size()-1] == NULL) {
				cout << "ERROR: Syntax in '" << current << "' is not interpretable" << endl;
				return 1;
			}
			cout << "f" << i << " = ";
			printTree(trees[i-1]);
			cout << endl;
			total += current;
		}
	}

	if (trees.empty()) {
		// Get expressions from user input
		cout << "Enter expressions to test:" << endl;
		for (int i = 0; i < 10; i++) {
			cout << "f" << i << " = ";
			getline(cin, current);
			for (int i = 0; i < current.size(); i++) {
				if (current[i] == ' ') {
					current = current.substr(0,i) + current.substr(i+1);
					i--;
				}
			}
			if (current == "")
				break;
			trees.push_back(parse(current));
			if (trees[i] == NULL) {
				cout << "ERROR: Syntax in '" << current << "' is not interpretable" << endl;
				return 1;
			}
			total += current;
		}
	}

	// Parse expressions into parse-trees
	if (options[0]) {
		cout << endl;
		for (int i = 0; i < trees.size(); i++) {
			cout << "f" << i << " = ";
			printTree(trees[i]);
			cout << endl;
		}
	}

	// Detect variables, and sort into vector
	vector<char> vars;
	bool found;
	for (int i = 0; i < total.size(); i++) {
		if ((total[i] > 96) && (total[i] < 123)) {
			found = false;
			for (int j = 0; j < vars.size(); j++) {
				if (vars[j] == total[i]) {
					found = true;
					break;
				}
			}
			if (!found)
				vars.push_back(total[i]);
		}
	}
	sort(vars.begin(), vars.end());

	// Warning for variables with over 1000 combinations
	if (vars.size() > 9)
		cout << "WARNING: More than 9 variables may result in formating problems" << endl;

	// Print table header
	cout << endl;
	for (int i = 0; i < vars.size(); i++) {
		cout << vars[i] << " ";
		vars_values[vars[i]] = false;
	}
	cout << "num";
	for (int i = 0; i < trees.size(); i++) {
		cout << " f" << i;
	}
	cout << endl;

	// Iterate over combinations and compute
	bool equal[trees.size()-1][trees.size()-1];
	for (int i = 0; i < trees.size()-1; i++) {
		for (int j = i; j < trees.size()-1; j++) {
			equal[i][j] = true;
		}
	}
	bool results[trees.size()];
	bool done;
	int num = 0;
	while (true) {
		// Print current combination data
		for (int i = 0; i < vars.size(); i++) {
			cout << vars_values[vars[i]] << " ";
		}
		printf("%3d", num);
		num++;
		// Evaluate parse-trees for current combination
		for (int i = 0; i < trees.size(); i++) {
			results[i] = evaluate(trees[i], vars_values);
			cout << "  " << results[i];
		}
		cout << endl;

		// Check expression equalities
		for (int i = 0; i < trees.size()-1; i++) {
			for (int j = i; j < trees.size()-1; j++) {
				equal[i][j] = equal[i][j] && (results[i] == results[j+1]);
			}
		}

		// Move to next combination, and check final state
		done = true;
		for (int i = 0; i < vars.size(); i++) {
			if (vars_values[vars[i]]) {
				vars_values[vars[i]] = false;
			} else {
				vars_values[vars[i]] = true;
				done = false;
				break;
			}
		}
		if (done)
			break;
	}

	if (options[1]) {
		cout << endl;
		// Print funtion equalities
		for (int i = 0; i < trees.size()-1; i++) {
			for (int j = i; j < trees.size()-1; j++) {
				cout << "f" << i;
				if (equal[i][j]) {
					cout << " == ";
				} else {
					cout << " != ";
				}
				cout << "f" << j+1 << endl;
			}
		}
	}

	return 0;
}
