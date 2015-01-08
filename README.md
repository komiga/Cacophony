
## Cacophony

*Cacophony* is a serialization header library for C++11.

It operates much like [cereal](http://USCiLab.github.com/cereal), but
doesn't deal with polymorphism, making it a lighter-weight library.

The documentation currently does not provide any examples nor signatures for
serialization functions. See the tests for idiomatic usage.

## Dependencies

Cacophony uses:

1. [duct++](https://github.com/komiga/duct-cpp) (HEAD)

See `dep/README.md` for dependency setup.

## Building

Cacophony is a header library and is thus not compiled directly.

All features support Clang 3.3+ with libc++ (SVN head) and GCC with libstdc++
as early as 4.7.3 (potentially earlier).

Once dependencies are setup (see `dep/README.md`), the tests can be compiled
using plash's standard project protocol: http://komiga.com/pp-cpp

## License

Cacophony carries the MIT license, which can be found both below and in the
`LICENSE` file.

```
Copyright (c) 2014-2015 Timothy Howard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
