Modules:
-file load parse contains the functions needed to open and parse the file we are given
-trim and split_csv are helper files for parse_file, which does the bulk of the parsing.
-load_file takes a filepath and loads the file

- data has the functions to properly store the data we are given from parsing the file
- also contains the structure which is used to store data, called Requirement

-previous iterations of this program included graph and graph.h, which were designed to draw the diagram of the dependency tree, which is no longer required

Instructions for running:
- a preconstructed exe called rdgg-76716794 is included, this will run the program.
- the program requires a user input of the file the user wants to analyze. 
- the input must be given in the form of the filepath of the designated file. 
- when prompted paste the file in and press enter.
- this will generate a report, under the name rdgg-report-76716794.md
    - note that this does overwrite previous versions of the report, and the file must be saved under a different name every time the program runs if you want to save previous versions