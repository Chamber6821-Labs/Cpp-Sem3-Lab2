**Reactions** is object-oriented library for creating command-based console application.
It is adopted version of framework [Takes](https://github.com/yegor256/takes).

# Quick start

Create this `app.cpp` file:
```c++
#include "Reactions/exit/ExNever.h"
#include "Reactions/fork/FkElse.h"
#include "Reactions/fork/FkWithName.h"
#include "Reactions/front/Console.h"
#include "Reactions/reaction/RcFork.h"
#include "Reactions/reaction/RcText.h"

// NOLINTNEXTLINE(bugprone-exception-escape)
auto main() -> int {
    make<Console>(
        make<RcFork>(
            make<FkWithName>("welcome", make<RcText>("Hello, World!\n")),
            make<FkElse>(make<RcText>("Unknown command!\n"))
        ),
        ">"
    )
        ->start(make<ExNever>());
}
```

Add this library in your CMake project. Part of CMakeLists.txt:

```cmake
add_executable(app app.cpp)
target_link_libraries(app PRIVATE Reactions::Reactions)
```

Build it like this:

```shell
$ cmake -B build
$ cmake --build build --target app
```

And run executable like this:

```shell
$ ./build/app
```

# Build and Run with CMake

**Note:** Today library support only CMake build system.

Your CMakeLists.txt should look like:

```cmake
cmake_minimum_required(VERSION 3.25)
project(App CXX)

set(CMAKE_CXX_STANDARD 20)
set(TARGET ${PROJECT_NAME}) # your application target name

include(FetchContent)

FetchContent_Declare(
        Reactions
        GIT_REPOSITORY https://github.com/Chamber6821/Reactions.git
        GIT_TAG 0.0.1
)

add_executable(${TARGET} app.cpp)

FetchContent_MakeAvailable(Reactions)
target_link_libraries(${TARGET} PRIVATE Reactions::Reactions)
```

With this configuration you can run it from command line:
```shell
$ cmake -B build
$ cmake --build build --target App
$ ./build/App
```
