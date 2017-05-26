#!/usr/bin/python

import argparse


# Handle command line arguments
parser = argparse.ArgumentParser("file_to_header")
parser.add_argument("filename", help="filepath to convert to header", type=str)
args = parser.parse_args()


# Open input and ouput files
input_file=open(args.filename,"r")
output_name = args.filename + ".h"
output_file = open(output_name,"w")


# Build string data name
data_string = "const char* "
output_name = args.filename.replace(".","_")
output_name = output_name.replace("-","_")
data_string += "_data_" + output_name + " = " + "\n\n"

# output to file
output_file.write("\n\n")
output_file.write(data_string )

data_size = 0
for line in input_file:
	output_file.write("\"")
	line = line.rstrip("\n")
        line = line.replace("\"","\\\"")
	count = len(line) 
	output_file.write(line)
	while count < 140:
		output_file.write(' ')
		count += 1
	output_file.write("\\n\"")
	output_file.write("\n")
	data_size += count + 1
output_file.write(";")

data_size_string = "\n\n" + "size_t _size_" + output_name + " = " + str(data_size) + ";\n\n" 
output_file.write(data_size_string)
