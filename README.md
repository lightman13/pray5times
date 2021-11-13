**In the name of Allah Most Gracious Most Merciful.**

*"Verily! In the creation of the heavens and the earth, and in the
alternation of night and day, there are indeed signs for men of
understanding"* **Sura El-Imran, verse 190.**

# How to install

To install the project, you have to run:

`make && sudo make install`

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
