# UESTC Compiler Experiments (2019)

Course exercises covering lexical analysis, parsing, and an unfinished LLVM IR generator for a small C-like language. The IR generator in `lab4/` writes LLVM IR text directly; it does not require the LLVM C API to build.

## Compiler way

For the IR generator, use GCC, GNU Make, Flex, and Bison. From the repository root:

```sh
cd lab4
mkdir -p obj bin
make CC='gcc -fcommon'
```

The executable is `lab4/bin/genllvm.out`. The `-fcommon` option accommodates the existing `astRoot` definitions when building with modern GCC. This is a legacy teaching project; the build still emits compiler warnings.

## Run way

From `lab4/`, create a minimal input and generate its IR:

```sh
printf 'int main() { return 0; }\n' > sample.c
make run FILE=sample.c
```

The result is `sample.ll`, alongside the input. It contains a definition of `main` returning `0`. The Make variable is uppercase `FILE`, and the target is `run`. The previously documented `example/test.c` path is not present in this checkout.

## Something should be paid attention to

The historical Makefiles can leave object files after a failed build. To rebuild the IR generator from a clean state, run these commands from `lab4/`:

```sh
make clean
make CC='gcc -fcommon'
```

Build serially: the Makefiles generate several files in a single recipe and do not coordinate parallel builds. Generated IR uses historical LLVM syntax and platform attributes; compatibility with a particular LLVM toolchain must be checked separately.

Directory layout:

| Directory | Content |
| --- | --- |
| [lab1](lab1) | Java lexical analysis in C and Flex |
| [lab2](lab2) | Recursive-descent parsing exercises |
| [lab3](lab3) | Flex/Bison parser and AST exercises; includes `test.c` |
| [lab4/src](lab4/src) | IR generator, parser, and lexer source |
| [lab4/include](lab4/include) | Headers |
| `lab4/obj` | Object files created during the build |
| [lab4/bin](lab4/bin) | Generator executable and historical test files |

Contact with me:

- QQ: 1025532090
- WeChat: ltclookatme

Look forward to learning from you!

## Things that have been implemented

- Basic arithmetic.
- String declarations, concatenation, character access, and assignment handling.
- IR headers with platform information and attribute definitions.
- Function parameter passing and nested scopes.

The generator remains unfinished; these features are learning exercises rather than a guarantee of complete language support or memory safety.
