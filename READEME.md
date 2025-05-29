Modules:
-file load parse contains the functions needed to open and parse the file we are given
-trim and split_csv are helper files for parse_file, which does the bulk of the parsing.
-load_file takes a filepath and loads the file

- data has the functions to properly store the data we are given from parsing the file
- also contains the structure which is used to store data, called Requirement

-previous iterations of this program included graph and graph.h, which were designed to draw the diagram of the dependency tree, which is no longer required