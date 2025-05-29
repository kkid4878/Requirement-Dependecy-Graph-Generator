Modules:
-file load parse contains the functions needed to open and parse the file we are given
-trim and split_csv are helper files for parse_file, which does the bulk of the parsing.
-load_file takes a filepath and loads the file

- originally used functions in data.c to store data from parsing file, but easier to just parse and store directly into data struct which is outlined in data.h
- also contains the structure which is used to store data, called Requirement

-previous iterations of this program included graph and graph.h, which were designed to draw the diagram of the dependency tree, which is no longer required

Note on AI usage:
- As was suggested, I used copilot's auto-complete feature to help generate parts of this assignment
- was mainly used in helping with the syntax for calls to the string library, as I am unfamiliar with it

Instructions for running:
- a preconstructed exe called rdgg-76716794 is included, this will run the program.
- the program requires a user input of the file the user wants to analyze. 
- the input must be given in the form of the filepath of the designated file. 
- when prompted paste the file in and press enter.
- this will generate a report, under the name rdgg-report-76716794.md
    - note that this does overwrite previous versions of the report, and the file must be saved under a different name every time the program runs if you want to save previous versions