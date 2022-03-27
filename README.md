**In the name of Allah Most Gracious Most Merciful.**

*"Verily! In the creation of the heavens and the earth, and in the
alternation of night and day, there are indeed signs for men of
understanding"* **Sura El-Imran, verse 190.**

# What is pray5times project ?

Pray5times is an open source project which has the purpose to calculate
5 prayers time with the algorithm visible to everyone. Before the creation
of the project, I realized there was not enough of ressources to understand
how prayer times was calculated.

To calculate each prayer time I used the following ressources:

- Meeus, J. (1998). Astronomical Algorithms. Willmann-Bell, Inc.
- [praytimes.org](http://praytimes.org/wiki/Prayer_Times_Calculation)

I used the book to calculate the equation of time and the declination of the
sun. Then, to calculate each prayer time I used the
[praytimes.org](http://praytimes.org/wiki/Prayer_Times_Calculation).

If you want to improve your knowledge about how to calculate prayer time or you
want to use the code for your own project, I invite anyone to participate
maintain/improve the project.

# What is pray5times-wrapper ?

This is a wrapper on pray5times software. It allows to calculate prayer times on
several days and years if you want. And it takes string location in contrary of
pray5times software which takes longitude and latitude coordonates. The wrapper
generate text file output with five prayers times.

# How to install

To install the project, you have to run:

`make && sudo make install`

# How to generate rpm

To generate rpms of the project you need to launch:

`./build.sh`

Then rpms packages are generated in the release directory.
To install in your machine, just do in the release directory :

`sudo dnf localinstall *.rpm`

# How to launch tests and coverage

You can use the following command to launch unitary tests:

`make check`

If you want to know what is the coverage of these tests on the code, you can
run the following command:

```
make coverage
make coverage-report.html
```

report-html folder is created and you can see the coverage of the code with
the following commands:

```
cd report-html
firefox coverage-report.html
```

# Check memory leak

There is a target which can detect memory leak. This target use valgrind tool.
To use it:

`make valgrind`

If any error is reported, we have to fix it before submiting patchs.

# Use Cppcheck

During development it's important to check if each patch is correct before push
it in master. There is a tool which can detect errors/warnings in C.
You can run:

`make cppcheck`

Some errors are syntactic. These errors can be ignored.
