# GSLanguage
EN: GSLanguage is a new compiled programming language written in C++ 20. The language is under development.<br>
RU: GSLanguage - новый компилируемый язык программирования, написанный на C++20. Язык находится в стадии разработки.

# Getting source
```shell
1) cd {pathToDir}
2) git clone https://github.com/EldarSalmanow/GSLanguage.git
```
1. Go to the directory to clone the repository.
2. Cloning repository.

# Build
```shell
1) cd {pathToDir}/GSLanguage
2) mkdir build
3) cd build
4) cmake ../ or cmake -G "MinGW Makefiles" ../
5) cmake --build . --target GSLanguage
```
EN:
1. Go to the directory with the cloned repository.
2. Create a directory for storing assembly files.
3. Go to the previously created directory.
4. Generating assembly files via CMake.<br>You can choose either configuration via MinGW or via MSVC.<br>Support for other compilers is not guaranteed at this time.
5. Building an executable file via target "GSLanguage"

# Run
Run without additional flags
```shell
GSLanguage.exe --file {pathToInputFile}.gs
```

Run with testing of each compilation step
```shell
GSLanguage.exe --file {pathToInputFile}.gs --test
```

Run with profiling of each compilation step.
```shell
GSLanguage.exe --file {pathToInputFile}.gs --profiling
```
