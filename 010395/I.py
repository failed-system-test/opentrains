import re

s = input()
pat = re.compile("^A+!+$")
if pat.match(s):
    print("Panic!")
else:
    print("No panic")
