This is a simple interpreter of arithemtic equations.
It supports basic operations like addition, multiplication etc.
but also roots, trigonometric functions and similar stuff.

**Note:** This is a learning project and if you came here looking for something to actually use,
there are far better and more polished alternatives.
One that I can recommend is [qalculate](https://qalculate.github.io/).

## Building

### Linux (and probably other \*nixes as well)

Make sure you you have make and a fairly recent version of gcc installed, then just run `make`.

### Windows

You need make (for example from [here](http://gnuwin32.sourceforge.net/packages/make.htm)) and a fairly recent version of gcc (for example from [here](https://winlibs.com/)).
Make sure that relevant binaries and includes are in your `%PATH%`
and then either run `make windows` from cmd or `make` from some POSIX shell.

## Usage

Valid operations are: (where x and y are numbers, named functions or expressions in parentheses)
- `+x` – unary plus
- `-x` – unary minus
- `x + y` – addition
- `x - y` – subtraction
- `x * y` – multiplication
- `x / y` – division
- `x ^ y` – x to the power of y
- `sqrt(x)` – square root
- `cbrt(x)` – cubic root
- `root(x, y)` – root of base y
- `sin(x)` – sine
- `cos(x)` – cosine
- `tan(x)` – tangent
- `ctg(x)` – cotangent
- `asin(x)` – arcsine
- `acos(x)` – arccosine
- `atan(x)` – arctangent
- `ln(x)` - natural logarithm
- 'log(x, y)` - logarithm of base y
