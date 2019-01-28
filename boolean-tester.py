import sys
# Boolean Test Recursive

statements = ["ab", "!(ab)", "ab1", "0"]
if (len(sys.argv) > 1):
    statements = sys.argv[1:]

def evaluate(statement, inputs):
    statement = statement.replace(" ", "")
    if (len(statement) == 1): 
    # Check single Variables
        if statement in inputs.keys():
            return inputs[statement]
        else:
            sys.exit("ERROR: Unsupported Variable\n  : \"" + statement + "\"")
            return False
    elif ((statement.find("!") == 0) and (len(statement) == 2)):
    # Check NOT
        return not evaluate(statement[1:], inputs)
    elif ("(" in statement):
    # Check Parentheses
        start = statement.find("(")
        end = statement.find(")")
        output = evaluate(statement[start+1:end], inputs)
        return evaluate(statement[0:start] + str(int(output)) + statement[end+1:], inputs)
    elif ("+" in statement):
        orLoc = statement.find("+")
        return evaluate(statement[0:orLoc], inputs) or evaluate(statement[orLoc+1:], inputs)
    elif ("*" in statement):
    # Check OR
        andLoc = statement.find("*")
        return evaluate(statement[0:andLoc], inputs) and evaluate(statement[andLoc+1:], inputs)
    elif ("xor" in statement):
    # Check AND
        xorLoc = statement.find("xor")
        return evaluate(statement[0:xorLoc], inputs) != evaluate(statement[xorLoc+3:], inputs)
    elif (statement[0] in inputs.keys()) and (statement[0] in inputs.keys()):
        output = evaluate(statement[0], inputs) and evaluate(statement[1], inputs)
        return evaluate(str(int(output)) + statement[2:], inputs)
    else:
    # Catch Errors
        sys.exit("ERROR: Unsupported Input\n  : \"" + statement + "\"")
        return False


statementNames = []
for s in range(len(statements)):
    print("f" + str(s) + " = " + statements[s])
print("")

variables = ""
for s in statements:
    variables += s
for s in [" ", "*", "+", "!", "(", ")", "xor", "1", "0"]:
    variables = variables.replace(s, "")
if not variables.isalpha():
    sys.exit("ERROR: Unsupported Input\n  : \"" + variables + "\"")
variables = sorted(set(variables))
#print(variables)
inputs = [False] * len(variables)
outputs = inputs

compares = len(statements) - 1
equality = [[True]] * compares
for i in range(len(equality)):
    equality[i] = [True] * compares
    compares -= 1
#print(equality)

line = ""
for val in variables:
    line += (" {:2s}").format(val)
line += " Num  "
for i in range(len(statements)):
    line += ("{:3s}").format("f" + str(i))
print(line)

num = 0
inputsDict = {"0":False, "1":True}
while True: 
    line = ""
    for v in inputs:
        line = ("{:2b} ").format(v) + line
    line += (" {:2n} ").format(num)

    for i in range(len(inputs)):
        inputsDict[variables[i]] = inputs[len(inputs)-1-i]
    
    results = []
    for s in statements:
        results.append(evaluate(s, inputsDict))
    
    for r in results:
        line += ("{:3b}").format(r)
    
    for i in range(len(equality)):
        for q in range(len(equality[i])):
            if (results[i] != results[q+i+1]):
                equality[i][q] = False

    print(line)

    done = True
    for i in range(len(inputs)):
        if (inputs[i]):
            inputs[i] = False 
        else:
            inputs[i] = True
            done = False 
            break 
    
    num += 1

    if (done):
        print("")
        allEq = True
        for i in range(len(equality)):
            for q in range(len(equality[i])):
                print("f" + str(i) + " = f" + str(q+i+1) + "  : " + str(equality[i][q]))
                if not equality[i][q]:
                    allEq = False
        print("All Equal: " + str(allEq))
        break