PROGRAMMING ASSIGNMENT 2 : IMPLEMENTING BTO AND MVTO VARIANTS
JANGA TUSHITA SHARVA
CS21BTECH11022

-----------------------------------------------------------------

This directory consists of the following files:
 - BTO-CS21BTECH11022.cpp
 - MVTO-CS21BTECH11022.cpp
 - MVTO-gc-CS21BTECH11022.cpp
 - k-MVTO-CS21BTECH11022.cpp
 - Logger.h
 - Transaction.h
 - Transaction.cpp
 - DataItem.h
 - PrimitiveDataItem.h
 - VersionedDataItem.h
 - report.pdf
 - readme.txt
 - inp.txt
 - run.sh

And following sample folders
 - outputs
 - inputs

-----------------------------------------------------------------

'inp.txt' is a sample input file. The file contains
the following information, as mentioned in the problem statement.


NOTE:
- C++17 is required to run this, because template functions are  used.
- There must be inp.txt which aligns with problem statement. I have kept an inp.txt in this folder which can be modified.
- There must be a folder `outputs`. I have submitted this too, along with some sample output files inside the folder.
- After programs are executed, the outputs will be in the outputs folder, so as to prevent any confusion
- Everytime the programs are executed, the files in the outputs folder are deleted by the script itself if there are any.
- Each of the algorithm outputs to different log file

-----------------------------------------------------------------
EXECUTION INSTRUCTIONS
-----------------------------------------------------------------

(I) METHOD 1: All files for `ONE` input file at a time
This directory contains a bash script "run.sh". To run this
file,
Change the permissions of the executable 
 - chmod u+x run.sh
Run the script
 - ./run.sh
 By default, the input file will be ``inp.txt`` in the same folder as the programs. 
 - To change the name of the file, change the `input_file_name` at line 10.


(II) METHOD 2: All files for `ONE` input file at a time, with checking memory leaks
This directory contains a bash script "run.sh". To run this
file,
Change the permissions of the executable 
 - chmod u+x run.sh
Run the script
 - ./run.sh
 By default, the input file will be ``inp.txt`` in the same folder as the programs. 
 - To change the name of the file, change the `input_file_name` at line 10.


(III) METHOD 2: Run all testcases at a time
Steps: 
(1) Make sure that the lines 24 to 48 in run.sh file are commented
(2) Uncomment the lines 51 to 63 in the run.sh file
(3) Make sure that all the testcases are present in the subfolders of the folder testcases.

|---- BTO-CS21BTECH11022.cpp
|---- MVTO-CS21BTECH11022.cpp
|---- k-MVTO-CS21BTECH11022.cpp
|---- MVTO-gc-CS21BTECH11022.cpp
|---- report.pdf
|---- readme.txt
|---- inp.txt
|---- outputs
|    |---- (might be empty, or there might be files)
|---- run.sh
|---- inputs
|    |---- E1
|    |    |---- .txt files with any name
|    |---- E2
|    |    |---- .txt files with any name
|    |---- E3
|    |    |---- .txt files with any name
|    |---- E4
|    |    |---- .txt files with any name
|    |---- E5
|    |    |---- .txt files with any name



All the text files under the subfolders will be run.
NOTE that the log files will be deleted after each iteration. i.e., for each test case all of the three programs will be executed and before the next test case all the outputs will be deleted.
For reference, I had uploaded the sample inputs folder I used for the experiments for the report.
-----------------------------------------------------------------

To see the log files, go to the outputs folder. The output files would be named as <implementation>-log.txt, 
Along with this, the algorithm name, abortCnt and CommitDelay are printed to the console.

-----------------------------------------------------------------

To execute only one file at a time, you may comment out any of those lines or follow these steps:
Open the commandline and open the current directory.
- For BTO:
    $ g++ -std=c++17 BTO-CS21BTECH11022.cpp Transaction.cpp -o a.out && ./a.out "<input_file_name>"
- For MVTO:
    $ g++ -std=c++17 MVTO-CS21BTECH11022.cpp Transaction.cpp -o a.out && ./a.out "<input_file_name>"
- For k-MVTO:
    $ g++ -std=c++17 k-MVTO-CS21BTECH11022.cpp Transaction.cpp -o a.out && ./a.out "<input_file_name>"
- For MVTO-gc:
    $ g++ -std=c++17 MVTO-CS21BTECH11022-gc.cpp Transaction.cpp -o a.out && ./a.out "<input_file_name>"


REMEBER TO DELETE THE OUTPUT FILES IF YOU ARE NOT RUNNING THE SCRIPT. ELSE THE PREVIOUS FILES GET APPENDED, AND MIGHT MISLEAD THAT RESULTS ARE WRONG.