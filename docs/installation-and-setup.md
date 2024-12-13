<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](project-structure.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-cpp.md)

&nbsp;
# Installation and Setup

There is no binary distribution of REx, it must be built from source. This project includes C++ source code with build scripts for Linux, macOS, and Windows, as well as a Java Gradle project containing tests.

If you’d like to try REx without building it, you can run it directly on this website: [https://www.bottlecaps.de/rex/](https://www.bottlecaps.de/rex/).

## Prerequisites

REx can be built on Linux, macOS, and Windows. As a prerequisite, a C++ compiler must be available. The following table shows the environments that have been covered:

| Operating system | Compiler                    | Build script<br>in folder [`rex/scripts`](../rex/scripts/) |
|------------------|-----------------------------|------------------------------------------------------------|
| Linux            | g++                         | `build-gpp.sh`                                             |
| Linux            | clang                       | `build-clang.sh`                                           |
| macOS            | g++                         | `build-gpp.sh`                                             |
| macOS            | clang                       | `build-clang.sh`                                           |
| Windows          | g++                         | `build-gpp.bat`                                            |
| Windows          | clang-cl with MSVC 32 bit   | `build-clang-cl-x86.bat`                                   |
| Windows          | clang-cl with MSVC 64 bit   | `build-clang-cl-x64.bat`                                   |
| Windows          | Microsoft Visual C++ 32 bit | `build-msvc-x86.bat`                                       |
| Windows          | Microsoft Visual C++ 64 bit | `build-msvc-x64.bat`                                       |

The build scripts have been tested most recently on

 - g++ versions 6.3 through 14.2
 - clang 10.0
 - clang-cl 19.1
 - Microsoft Visual C++ 19.41.

In addition, for running the supplied tests, a Java Development Kit is necessary. This should be JDK 11 or higher. When going for tests of all target platforms, JDK 17 or higher is recommended, as some of them may ask for that (e.g. newer releases of Scala).

## Downloading and Building REx

Follow these steps to create a REx executable:

- clone this repository. Alternatively, download and unpack a [source release](https://github.com/GuntherRademacher/rex-parser-generator/releases).
- go to the repo's root folder.
- in subfolder [`rex/scripts`](../rex/scripts/), find the build script corresponding to your C++ compiler and operating system in the table shown above and run it. Upon success, it will indicate the path and name of the REx executable in the `rex/build/bin` subfolder.
- add the `rex/build/bin` folder to the `PATH` environment variable, so REx can be found just by the executable`s filename.

E.g.

 - in Linux or macOS `bash`:

   ```sh
   git clone https://github.com/GuntherRademacher/rex-parser-generator.git
   cd rex-parser-generator
   rex/scripts/build-gpp.sh
   export PATH=`realpath rex/build/bin`:$PATH
   ```

 - in Windows `cmd`:

   ```sh
   git clone https://github.com/GuntherRademacher/rex-parser-generator.git
   cd rex-parser-generator
   rex\scripts\build-msvc-x64.bat
   for %A in ("rex\build\bin") do set PATH=%~fA;%PATH%
   ```

The executable is all that is needed for using REx, it contains everything needed to generate parsers from input grammars, and the parsers are self-contained. There is no extra code required at runtime, except for the standard libraries of the respective target platform. At this point, REx is ready to use.

REx is also built by these GitHub workflows:

 - on Linux: [build-and-test-linux.yml](https://github.com/GuntherRademacher/rex-parser-generator/actions/workflows/build-and-test-linux.yml)
 - on Windows: [build-and-test-windows.yml](https://github.com/GuntherRademacher/rex-parser-generator/actions/workflows/build-and-test-windows.yml)

## Viewing REx Documentation locally

For viewing the documentation locally on the cloned repository, install Microsoft Visual Studio Code and invoke it with this command line:

```sh
code README.md
```

Then press `Ctrl+Shift+V` (Windows/Linux) or `Cmd+Shift+V` (macOS) to toggle the preview mode.

## Running REx Tests

Running the tests after building REx may help to confirm that a valid executable has been produced that meets the expectations.

The tests are located in the `rex-tests` subfolder, and they come as a Gradle project that executes Java code invoking REx. They run the REx executable on sample grammars and compile and execute generated parsers on their repective target platform. This is however only done if the target platform is available: many tests are optional, because they require specific compilers to be available in the test execution environment. The Java-based tests are always executed, because their dependencies are resolved automatically from Maven Central. Tests where the target platform is unavailable will be skipped. 

The table below shows the compile and runtime commands that the tests will use.

| Optional | Target Language | Compiler/Runtime      | Compile Command | Runtime Command     |
|----------|-----------------|-----------------------|-----------------|---------------------|
| ✔️      | C++             | g++                   | `g++`           | compiled executable |
| ✔️      | C#              | MS Visual C#          | `csc`           | compiled executable |
| ✔️      | C#              | Mono                  | `mcs`           | `mono`              |
| ✔️      | Go              | Go                    | `go`            | compiled executable |
| ✔️      | Haxe            | Haxe<br>Neko          | `haxe`          | `neko`              |
|          | Java            | JDK                   | `javac`         | `java`              |
| ✔️      | JavaScript      | Node.js               |                 | `node`              |
| ✔️      | Python          | Python 3              |                 | `python3`           |
| ✔️      | Scala           | Scala                 | `scalac`        | `scala`             |
| ✔️      | TypeScript      | TypeScript<br>Node.js | `npm`<br>`tsc`  | `node`              |
|          | XQuery          | BaseX                 |                 | `java`              |
|          | XQuery          | Saxon-HE              |                 | `java`              |
|          | XSLT            | Saxon-HE              |                 | `java`              |

Before running the tests, make sure that

 - the REx executable is available on the `PATH`. If not, extend the `PATH` as explained [above](#downloading-and-building-rex).
 - a Java Development Kit (JDK) for Java 11 or higher is available. The Scala tests, for Scala version 3.5 or higher, even require Java 17 or higher, and they will be skipped if unavailable.
 - the compilers are available for any target platforms that you want to have included in the test.

For running the tests, go to the `rex-tests` folder and run this command:

```sh
gradlew test
```
(on Linux or macOS, prepend `./` to the command).

This will execute the tests and report success or failure to the console. After completion, an HTML report of test execution can be found in `build/reports/tests/test/index.html`, and individual test results are available in XML files in folder `build/test-results/test`. Note that these paths are relative to the `rex-tests` folder of the `rex-parser-generator` project.

The `rex-tests` project can also be imported in Eclipse via `Import`→`Gradle`→`Existing Gradle Project`. Running it in Eclipse as a JUnit test may reveal more details in the test report, in particular the reasoning behind skipping certain tests.

During test execution, REx-generated parsers are cached, once the test was successful. Any subsequent test runs will succeed prematurely, if their generated parser matches the cached one, without compiling and executing it again. This serves for speeding up the test. For still compiling and executing the parsers, maybe in case a different compiler was installed, make sure to prevent the use of cached parsers. This can be done by deleting them in `build/cache` in the `rex-tests` project for Gradle execution, or `bin/cache` for Eclipse execution. Alternatively, a Gradle test run can also include the `clean` task to wipe the cache:

```sh
gradlew clean test
```
(on Linux or macOS, prepend `./` to the command).

&nbsp;
---
[⇦ Previous page](project-structure.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-cpp.md)