# ideas

#### simple math language
Math operations:
```text
() ^ * / + -
```

example script:
```text
a = 1 + 2 + 3;
b = 1 * 2 * 3;
print a;
print b;
c = a * b;
print c;
```

tokenizer:
```text
a = 1 + 2 + 3 -> [VARIABLE(a), EQUALS, NUMBER(1), PLUS, NUMBER(2), PLUS, NUMBER(3)]
```

ast:
```text
[VARIABLE(a), EQUALS, NUMBER(1), PLUS, NUMBER(2), PLUS, NUMBER(3)] 
->
PROGRAM
  ASSIGNMENT
    VARIABLE(a)
    EXPRESSION
      OPERATION(PLUS)
        OPERATION(PLUS)
          NUMBER(1)
          NUMBER(2)
        NUMBER(3)
```

interpreter:
```text
sets a to { 1 + 2 + 3 }
evaluates { 1 + 2 + 3 } to 6
```