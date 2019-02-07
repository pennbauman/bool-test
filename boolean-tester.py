import sys
import os
# Boolean Test Recursive

# Print Help Menu
def helpPrint():
    # Get text form help.txt in same directory
    try:
        helpFile = os.path.dirname(os.path.abspath(__file__)) + "/help.txt"
        helpText = open(helpFile, "r")
    # catches errors in file get
    except:
        sys.exit("ERROR: Could Not Locate Help File")
    # prints out file line by line
    for line in helpText:
        print(line.replace("\n", ""))
    helpText.close()

# evaluates logical statement, with given variables values
def evaluate(statement, inputs):
    statement = statement.replace(" ", "")
    # Check single Variables
    if (len(statement) == 1): 
        # returns varaibles value
        if statement in inputs.keys():
            return inputs[statement]
        # returns error if single remaining character in not a variables
        else:
            sys.exit("ERROR: Unsupported Variable\n  : \"" + statement + "\"")
            return False
    # NOT
    for c in range(len(statement)-1):
        # single character not symbols ("!", "~")
        if ((statement[c] == "!") or (statement[c] == "~")) and (statement[c+1] in inputs.keys()):
            output = not inputs[statement[c+1]]
            return evaluate(statement[0:c] + str(int(output)) + statement[c+2:], inputs)
        # "NOT" not symbol
        elif (c < len(statement)-3):
            if (statement[c:2] == "NOT") and (statement[c+3] in inputs.keys()):
                output = not inputs[statement[c+3]]
                return evaluate(statement[0:c] + str(int(output)) + statement[c+4:], inputs)
    # AND (without symbol)
    for c in range(len(statement)-1):
        if (statement[c] in inputs.keys()) and (statement[c+1] in inputs.keys()):
            output = evaluate(statement[c], inputs) and evaluate(statement[c+1], inputs)
            return evaluate(statement[0:c] + str(int(output)) + statement[c+2:], inputs)
    # Parentheses
    if ("(" in statement):
        start = statement.find("(")
        # check that parantheses are closed, and ensure proper pair is used
        i = 0
        closed = False
        for c in range(len(statement)):
            if (statement[c] == "("):
                i += 1
            elif (statement[c] == ")"):
                if (i == 1):
                    end = c 
                    closed = True
                    break
                else: 
                    i -= 1
        # error if paratheses aren't closed
        if not closed:
            sys.exit("ERROR: Unclosed Parentheses\n  : \"" + statement + "\" " + str(i))
        output = evaluate(statement[start+1:end], inputs)
        return evaluate(statement[0:start] + str(int(output)) + statement[end+1:], inputs)
    # XNOR
    elif ("=" in statement) or ("XNOR" in statement):
        if ("=" in statement):
            xnorLoc = statement.find("=")
            l = 1
        elif ("XNOR" in statement):
            xnorLoc = statement.find("XNOR")
            l=4
        return evaluate(statement[0:xnorLoc], inputs) == evaluate(statement[xnorLoc+l:], inputs)
    # Implication
    #elif (">" in statement) or ("IMP" in statement):
    #    if (">" in statement):
    #        impLoc = statement.find(">")
    #        l = 1
    #    elif ("IMP" in statement):
    #        impLoc = statement.find("IMP")
    #        l=3
    #    return (not evaluate(statement[0:impLoc], inputs)) or evaluate(statement[impLoc+l:], inputs)
    # NOR
    elif ("NOR" in statement):
        norLoc = statement.find("NOR")
        return not (evaluate(statement[0:norLoc], inputs) or evaluate(statement[norLoc+3:], inputs)) 
    # OR
    elif ("+" in statement) or ("OR" in statement):
        if ("+" in statement):
            orLoc = statement.find("+")
            l = 1
        elif ("OR" in statement):
            orLoc = statement.find("OR")
            l = 2
        return evaluate(statement[0:orLoc], inputs) or evaluate(statement[orLoc+l:], inputs)
    # XOR
    elif ("XOR" in statement):
        xorLoc = statement.find("XOR")
        return evaluate(statement[0:xorLoc], inputs) != evaluate(statement[xorLoc+3:], inputs)
    # NAND
    elif ("NAND" in statement):
        nandLoc = statement.find("NAND")
        return not (evaluate(statement[0:nandLoc], inputs) and evaluate(statement[nandLoc+4:], inputs))
    # AND
    elif ("*" in statement) or ("&" in statement) or ("AND" in statement):
        if ("*" in statement):
            orLoc = statement.find("*")
            l = 1
        elif ("&" in statement):
            orLoc = statement.find("&")
            l = 1
        elif ("AND" in statement):
            orLoc = statement.find("AND")
            l = 3
        return evaluate(statement[0:orLoc], inputs) and evaluate(statement[orLoc+l:], inputs)
    # Catch Other Errors
    sys.exit("ERROR: Unsupported Input\n  : '" + statement + "'")
    return False

# Inititalize statements (must be empty to behave in command line)
statements = []
# check for help parameter 
if (len(sys.argv) > 1):
    if (sys.argv[1] == "help"):
        helpPrint()
# Get statements from inut
print("Enter expessions or 'help' for more information.")
for i in range(10):
    s = input("f" + str(i) + " = ")
    # check empty statements (ends statement entry)
    if (s == ""):
        print("")
        break
    # check for help menu request
    elif (s == "help"):
        helpPrint()
        i -= 1
    else:
        statements.append(s)
# error if not statements are entered
if (len(statements) == 0):
    sys.exit("ERROR: No Statements Entered")
# Gets varaibles used in statements
variables = ""
for s in statements:
    v = s
    # remove opperations from statments 
    for operater in  [" ", "!", "~", "NOT", "*", "&", "AND", "+", "|", "OR", "XOR", ">", "IMP", "NAND", "NOR", "=", "XNOR", "(", ")", "1", "0"]:
        v = v.replace(operater, "")
    # error if variable is not a letter
    if not v.isalpha():
        sys.exit("ERROR: Unsupported Input\n  : '" + s + "'")
    else:
        variables += v
# Sort vaiables and create array of their values
variables = sorted(set(variables))
inputs = [False] * len(variables)
# creates matrix of statement equality, is trianglular matrix
compares = len(statements) - 1
equality = [[True]] * compares
for i in range(len(equality)):
    equality[i] = [True] * compares
    compares -= 1
# prints out table header
line = ""
for val in variables:
    line += (" {:s}").format(val)
line += " Num "
for i in range(len(statements)):
    line += ("{:3s}").format("f" + str(i))
print(line)
# Interate through all combinations of variables
num = 0
inputsDict = {"0":False, "1":True}
while True: 
    # prints variables and number for line
    line = ""
    for v in inputs:
        line = ("{:2b}").format(v) + line
    line += (" {:3n}").format(num)
    # set variables in inputs dictionary to current values
    for i in range(len(inputs)):
        inputsDict[variables[i]] = inputs[len(inputs)-1-i]
    # get results of statments with current values
    results = []
    for s in statements:
        results.append(evaluate(s, inputsDict))
    # print results for line
    for r in results:
        line += ("{:3b}").format(r)
    # check for inequlaity between statements 
    for i in range(len(equality)):
        for q in range(len(equality[i])):
            if (results[i] != results[q+i+1]):
                equality[i][q] = False
    # print whole line
    print(line)
    # change variables to next combo, prepare to break if at final combo
    done = True
    for i in range(len(inputs)):
        if (inputs[i]):
            inputs[i] = False 
        else:
            inputs[i] = True
            done = False 
            break 
    # if at final variables combo, break from loop
    if (done):
        print("")
        # print final equality of statments
        allEq = True
        for i in range(len(equality)):
            for q in range(len(equality[i])):
                print("f" + str(i) + " = f" + str(q+i+1) + "  : " + str(equality[i][q]))
                if not equality[i][q]:
                    allEq = False
        # print final equality of statments
        if (len(statements) > 2):
            print("All Equal: " + str(allEq))
        break
    
    num += 1