<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](overview.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](installation-and-setup.md)

&nbsp;
# Project Structure

This is an overview of the topmost files and folders in this repository:

```
📂 rex-parser-generator
 ├─── 📂 .github                                 # GitHub actions
 │     ├─── 📂 workflows                         # Build and test workflows
 │     │     ├─── 📄 build-and-test-linux.yml    # Build and test workflow for Linux
 │     │     ├─── 📄 build-and-test-macos.yml    # Build and test workflow for macOS
 │     │     ├─── 📄 build-and-test-windows.yml  # Build and test workflow for Windows
 │     │     └─── 📄 check-markdown-links.yml    # documentation link check workflow
 │     └─── 📄 dependabot.yml                    # Dependency update workflow
 ├─── 📂 docs                                    # Project documentation
 │     └─── ...
 ├─── 📂 rex-tests                               # Java Gradle project testing the C++ executable 
 │     ├─── 📂 gradle/wrapper                    # Gradle wrapper files
 │     │     └─── ...
 │     ├─── 📂 src/test                          # Java test source code
 │     │     └─── ...
 │     ├─── 📄 build.gradle                      # Gradle build script
 │     ├─── 📄 gradlew                           # Gradle wrapper script for Linux and macOS
 │     ├─── 📄 gradlew.bat                       # Gradle wrapper script for Windows
 │     └─── 📄 settings.gradle                   # Gradle settings
 ├─── 📂 rex                                     # C++ project - main product code
 │     ├─── 📂 scripts                           # Build scripts
 │     │     ├─── 📂 fragments                   # Helper scripts
 │     │     │     └─── ...
 │     │     ├─── 📄 build-clang.sh              # Linux/macOS build script using clang
 │     │     ├─── 📄 build-gpp.sh                # Linux/macOS build script using g++
 │     │     ├─── 📄 build-clang-cl-x64.bat      # Windows build script using clang-cl (64 bit)
 │     │     ├─── 📄 build-clang-cl-x86.bat      # Windows build script using clang-cl (32 bit)
 │     │     ├─── 📄 build-gpp.bat               # Windows build script using g++
 │     │     ├─── 📄 build-msvc-x86.bat          # Windows build script using MS C++ (32 bit)
 │     │     └─── 📄 build-msvc-x64.bat          # Windows build script using MS C++ (64 bit)
 │     └─── 📂 src                               # C++ source code
 │           └─── ...
 ├─── 📄 .gitattributes                          # Defines attributes for files in the repo
 ├─── 📄 .gitignore                              # Specifies files and directories to ignore
 ├─── 📄 LICENSE                                 # A copy of the Apache 2.0 license
 └─── 📄 README.md                               # Main entry point for project information
```

When building and testing, there will be additional files and folders holding generated artifacts. The most important ones are shown below:

```
📂 rex-parser-generator
 ├─── 📂 rex-tests                               # Java Gradle project testing the C++ executable 
 │     ├─── 📂 build                             # Java build and test artifacts folder
 │     │     ├─── 📂 cache                       # Generated parser cache for test speedup
 │     │     │     └─── ...
 │     │     ├─── 📂 reports/tests/test          # HTML test reports
 │     │     │     ├─── 📄 index.html            # JUnit test report of Gradle test
 │     │     │     └─── ...
 │     │     ├─── 📂 test-results/test           # XML test result files
 │     │     │     └─── ...
 │     │     └─── ...
 └─── 📂 rex                                     # C++ project - main product code
       └─── 📂 build                             # C++ build artifact folder
             ├─── 📂 bin                         # Executable binaries
             │     └─── 📄 rex[.exe]             # REx executable: rex (or rex.exe on Windows)
             └─── ...
```

&nbsp;
---
[⇦ Previous page](overview.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](installation-and-setup.md)