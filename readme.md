This is a simple interpreter of arithemtic equations.
It supports basic operations like addition, multiplication etc.
but also roots, trigonometric functions and similar stuff.

**Note:** This is a learning project and if you came here looking for something to actually use,
there are far better and more polished alternatives.
One that I can recommend is [qalculate](https://qalculate.github.io/).

## Building

On any platform you're gonna need a C++ compiler with C++20 support.

### Linux and other Unix-like

You need Cmake and Make. Run:

```
cmake -S. -Bbuild
cd build
make
# or if you don't want to compile tests
make calc
```

### Windows

#### Visual Studio

Visual Studio has built-in support for Cmake projects (you might need to install it).

In order to build this project using Visual Studio:
(following instructions from [here](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170))

1. Open the main project folder (containing CMakeLists.txt) in Visual Studio
2. Wait for Visual Studio to sort Cmake out
3. Switch the solution explorer to CMake targets view
4. Build the `calc` target.

#### CMake

You can also use CMake directly (you can get it from [here](https://cmake.org/download/))
and build the project using any build system supported by it.
Below instructions show how to use it with Make, with GCC as the compiler.

You can get Make [here](http://gnuwin32.sourceforge.net/packages/make.htm).
You can get an up to date version of GCC (and Clang) [here](https://winlibs.com/).
Make sure that relevant binaries are in your `Path` and run:

```
cmake -S. -Bbuild -G "Unix Makefiles"
cd build
make
```

## Usage

Valid operations are: (where x and y are numbers, constants, named functions or expressions in parentheses)
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
- `deg(x)` – convert degrees to radians
- `asin(x)` – arcsine
- `acos(x)` – arccosine
- `atan(x)` – arctangent
- `ln(x)` - natural logarithm
- `log(x, y)` - logarithm of base y

Valid constants are:
- `pi` – pi
- `e` – e
