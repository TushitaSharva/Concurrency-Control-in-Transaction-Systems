PROGRAMMING ASSIGNMENT 1 : IMPLEMENTING BOCC AND FOCC-CTA, FOCC-OTA
JANGA TUSHITA SHARVA
CS21BTECH11022

-----------------------------------------------------------------

This directory consists of the following files:
 - BOCC-CTA-CS21BTECH11022.cpp
 - FOCC-CTA-CS21BTECH11022.cpp
 - FOCC-OTA-CS21BTECH11022.cpp
 - Logger.h
 - Transaction.h
 - Transaction.cpp
 - DataItem.h
 - DataItemForAbortOther.h
 - report.pdf
 - readme.txt
 - inp.txt
 - run.sh

ANd following sample folders
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
(1) Make sure that the lines 22 to 35 in run.sh file are commented
(2) Uncomment the lines 37 to 47 in the run.sh file
(3) Make sure that all the testcases are present in the subfolders of the folder testcases.

|---- FOCC-CTA-CS21BTECH11022.cpp
|---- BOCC-CTA-CS21BTECH11022.cpp
|---- FOCC-OTA-CS21BTECH11022.cpp
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



All the text files under the subfolders will be run.
NOTE that the log files will be deleted after each iteration. i.e., for each test case all of the three programs will be executed and before the next test case all the outputs will be deleted.
For reference, I had uploaded the sample input folder I used for the experiments for the report.
-----------------------------------------------------------------

To see the log files, go to the outputs folder. The output files would be named as <implementation>-log.txt, 
Along with this, abortCnt and CommitDelay are printed to the console.

-----------------------------------------------------------------

To execute only one file at a time, you may comment out any of those lines or follow these steps:
Open the commandline and open the current directory.
- For FOCC-CTA:
    $ g++ -std=c++17 FOCC-CTA-CS21BTECH11022.cpp Transaction.cpp -o focc_c.out && ./focc_c.out "<input_file_name>"
- For FOCC-OTA:
    $ g++ -std=c++17 FOCC-OTA-CS21BTECH11022.cpp Transaction.cpp -o focc_o.out && ./focc_o.out "<input_file_name>"
- For BOCC:
    $ g++ -std=c++17 BOCC-CTA-CS21BTECH11022.cpp Transaction.cpp -o bocc.out && ./bocc.out "<input_file_name>"

REMEBER TO DELETE THE OUTPUT FILES IF YOU ARE NOT RUNNING THE SCRIPT. ELSE THE PREVIOUS FILES GET APPENDED, AND MIGHT MISLEAD THAT RESULTS ARE WRONG.