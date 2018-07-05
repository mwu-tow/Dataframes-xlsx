# Introduction
This is a C++ library providing support for Luna Datasets framework. It provides function both for dataset file I/O operations and basic array splicing.

# Third party dependencies
* [xlnt library](https://github.com/tfussell/xlnt) (C++/CMake) — needed for .xlsx file format support.

# Build & Install
* have installed `xlnt` library either:
  * system-wide install (`cmake /PATH/TO/XLNT && make install`)
  * local install and set `CMAKE_PREFIX_PATH` to the location
  * separately provide library's include and library directories with `CMAKE_LIBRARY_PATH`
* clone the repo
* `cmake repo/DataframeHelper`
* `make`
* Binary will be placed in the `repo/native_libs/os/` directory where `os` is either `windows`, `macos` or `linux`.

# Structure

* `Core/`
  * `Common` — defines an `EXPORT` macro
  * `Error` — helpers for translating between C++ error reporting (exceptions) and Luna-consumable error messages
  * `Matrix2d` — class that manages a Luna-consumable 2D array with strings
* `IO/`
  * `xlsx` — read/write dataframe from/to files in Microsoft Excel Open XML Format;
  * `csv` — read/write dataframe from/to file in [CSV format](https://tools.ietf.org/html/rfc4180).

# API

## Types
#### using MatrixDataPtr = const char * const *;
`MatrixDataPtr` is a an array of string pointers. It represents a two-dimensional array of C-style strings stored in a single [row-major](https://en.wikipedia.org/wiki/Row-_and_column-major_order#/media/File:Row_and_column_major_order.svg) linear storage. The storage (both for the array itself and the strings) is managed by the `Matrix2d` class.

Pointer of that type is meant for Luna — to allow easy access to array elements.

Luna is not allowed to directly modify neither array elements nor the strings itself, the storage should be treated as read-only.

## Functions
### Core
#### void mat_delete(MatrixDataPtr mat)
Deletes a Matrix2d object associated with given matrix data pointer.

### IO