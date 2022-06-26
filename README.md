**In the name of Allah Most Gracious Most Merciful.**

*"Verily! In the creation of the heavens and the earth, and in the
alternation of night and day, there are indeed signs for men of
understanding"* **Sura El-Imran, verse 190.**

# What is pray5times project ?

Pray5times is a library which allow to calculate the 5 prayers. The library is
available in several language thanks to langage bindings.

Supported languages:
- C
- Python
- Java
- C#

To calculate each prayer time I used the following ressources:

- Meeus, J. (1998). Astronomical Algorithms. Willmann-Bell, Inc.
- [praytimes.org](http://praytimes.org/wiki/Prayer_Times_Calculation)

I used the book to calculate the equation of time and the declination of the
sun. Then, to calculate each prayer time I used the
[praytimes.org](http://praytimes.org/wiki/Prayer_Times_Calculation).

# Example using the library

In the directory src/ there is an example of using the library pray5times in a
small application which print each prayers time.

# What is pray5times-wrapper ?

This is a wrapper on pray5times example software. It allows to calculate prayer times on
several days and years if you want. And it takes string location in contrary of
pray5times software which takes longitude and latitude coordonates. The wrapper
generate text file output with five prayers times.

# How to install from sources

To install the project, you have to run:

`make && sudo make install`

# How to compile in another langage of C ?

To compile the project in another language you can use the Makefile as follow.
For example, if you want to compile the library in Java you have to do the
following commands:

```
cd lib
make java
```

For each language there is a target in the makefile to compile the library.

For now there are only 3 language supported :
- Python
- Java
- C#

# How to generate and install rpm package

To generate rpms of the project you need to launch:

`./build.sh rpm LANGUAGE_DESIRED`

When LANGUAGE_DESIRED is the language you want to target.

Then rpms packages are generated in the release directory.
To install in your machine, just do in the release directory :

`sudo dnf localinstall *.rpm`

# How to generate deb package

To generate deb package you need to launch:

`./build.sh deb`

Then debian package are generated in the release directory.

For now the deb packaging is only for pray5times library compiled
in C.

# Developer section
## How to launch tests and coverage

You can use the following command to launch unitary tests:

```
cd lib/
make check
```

If you want to know what is the coverage of these tests on the code, you can
run the following command:

```
cd lib/
make coverage
make coverage-report.html
```

report-html folder is created and you can see the coverage of the code with
the following commands:

```
cd report-html
firefox coverage-report.html
```

## Check memory leak

There is a target which can detect memory leak. This target use valgrind tool.
To use it:

```
cd src/
make valgrind
```
If any error is reported, we have to fix it before submiting patchs.

## Use Cppcheck

During development it's important to check if each patch is correct before push
it in master. There is a tool which can detect errors/warnings in C.
You can run:

```
cd src
make cppcheck
```

Some errors are syntactic. These errors can be ignored.

## Use Pylint

As the wrapper is developped in Python, you can use the following command to
check if there are any errors/warnings in python:

```
cd wrapper
make pylint
```
