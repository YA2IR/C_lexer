# About
This is a lexer/tokenizer for the C programming language. It takes a C file as an input and produces the following (literal, token_type) pairs as output:
```
// example1.c:
    int x = 1.f*0xAB;
// gcc lexer/lexer.c main.c && ./a.out example1.c:
    == ('int','INT')
    == ('x','IDENT')
    == ('=','ASSIGN')
    == ('1.f','NUM')
    == ('*','STAR')
    == ('0xAB','NUM')
    == (';','SEMICOLON')
    == --END-- ==
```

For a full example, you can run it on example.c -an actual file-:
```
gcc main.c lexer/lexer.c && ./a.out example.c
```

# Limitations
- The lexer supports most but not all of the language. For example, it doesn't support the scientific notation "123.45e-6" yet, and I might have missed things like supporting suffixes in hexadecimal literals (i.e. "0xA(L)" is not allowed)
- There is only one token type that represents numbers "NUM"
- It doesn't support directives that are handled by the preprocessor (e.g. #define and #include)
