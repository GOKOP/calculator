This is a simple interpreter of arithemtic equations.
It supports basic operations like addition, multiplication etc.
but also roots, trigonometric functions and similar stuff.

**Note:** This is a learning project and if you came here looking for something to actually use,
there are far better and more polished alternatives.
One that I can recommend is [qalculate](https://qalculate.github.io/).

## Building

On any platform you're gonna need Cmake and a C++ compiler with C++17 support.

### Linux and other Unix-like

Run:

```
cmake -S. -Bbuild
cd build
make
```

### Windows

If you don't have Cmake, you can get it from [here](https://cmake.org/download/).

#### Visual Studio

If you have Visual Studio installed, cmake will by default generate a solution for the newest version you have.
If for some reason it doesn't, specify it with the -G option.

```
cmake -S. -Bbuild
# or
cmake -S. -Bbuild -G "Visual Studio 16 2019"
```

After that find the .sln file, open it and compile as you would normally do in Visual Studio.

#### GNU Make

You can also use a Windows version of GNU Make which you can get[here](http://gnuwin32.sourceforge.net/packages/make.htm)) 
You can get an up to date version of GCC (and Clang) [here](https://winlibs.com/).
Make sure that relevant binaries are in your `Path` and run:

```
cmake -S. -Bbuild -G "Unix Makefiles"
cd build
make
```

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
- `log(x, y)` - logarithm of base y
