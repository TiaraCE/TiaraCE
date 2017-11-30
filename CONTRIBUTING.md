# TiaraCE-Guidelines
Development guidelines for the development of TiaraCE. **WIP**

TiaraCE is intended to be a cross-platform application. As such, there are a few things that **must** be considered before writing code for this project.

The following is a list of things that must be taken into consideration before any code is accepted into the codebase:

*   All code is to be written in C++, and should adhere at minimum to the C++11 standard.
    *   Code that follows up to the C++17 is permitted.


*   Code must be able to be compiled in Clang or GCC/MinGW.
    *   Use of Visual Studio's code or project files is prohibited.


*   Code should use `snake_case` in file names.
    *   Use of `CamelCase` is permitted within code, so long as it does not pertain to file names.
