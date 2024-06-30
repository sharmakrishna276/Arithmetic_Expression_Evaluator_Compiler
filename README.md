Compiler for Simple Language of Expressions

To check the correctness of syntax, run the following commands in terminal from the parent directory:

1.  make
2.  A binary file named "e++" is generated to the bin/ directory. Copy it to the samples/ directory.
3.  Go to tests/targ/ and then open the folder according to your system, i.e., Windows, Linux or MacOS. Copy the targ++ binary file to the samples/ directory.
4.  cd samples/
5.  ./e++ test_{1 or 2 or 3}.txt
6.  ./targ++ targ.txt

If the targ commands generated were syntactically correct, it shows "Compilation Sucessful!".

NOTE: If terminal shows permission denied error, then run ”sudo chmod +x targ++” only once.

To run the tester, run the following commands in terminal from the parent directory:

1.  make tester
2.  cd bin/
3.  ./tester
4.  Follow the instructions displayed on the screen.

