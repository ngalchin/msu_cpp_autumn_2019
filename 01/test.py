import os


myCmd = os.popen('./calc "2 + 3 * 4 - -2"').read()
print("2 + 3 * 4 - -2 =", myCmd, ("\t OK" if myCmd == '16' else "\tWrong answer"))

myCmd = os.popen('./calc " 2 + 2 - -1"').read()
print(" 2 + 2 - -1 =", myCmd, ("\t OK" if myCmd == '5' else "\tWrong answer"))

myCmd = os.popen('./calc "2+-4"').read()
print("2+-4 =", myCmd, ("\t OK" if myCmd == '-2' else "\tWrong answer"))

myCmd = os.popen('./calc "2-3*4+-5/2"').read()
print("2-3*4+-5/2 =", myCmd, ("\t OK" if myCmd == '-12' else "\tWrong answer"))

myCmd = os.popen('./calc "2-3*4*2+1--2+-5/2"').read()
print("2-3*4*2+1--2+-5/2 =", myCmd, ("\t OK" if myCmd == '-21' else "\tWrong answer"))

myCmd = os.popen('./calc "2/0"').read()
print("2/0 =", myCmd, ("\t OK" if myCmd == 'Error' else "\tWrong answer"))

myCmd = os.popen('./calc "2+11 -1 +"').read()
print("2+11 -1 + =", myCmd, ("\t OK" if myCmd == 'Error' else "\tWrong answer"))


