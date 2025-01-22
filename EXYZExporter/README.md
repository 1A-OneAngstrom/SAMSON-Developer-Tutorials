# EXYZ Exporter

Please, refer to the [Exporter tutorial](https://documentation.samson-connect.net/developers/latest/tutorials/exporting/).

This SAMSON Extension demonstrates how to implement an [exporter](https://documentation.samson-connect.net/developers/latest/exporters/) on an example of a simple XYZ-exporter for files of the following format:

1. The 1st line: the number of atoms in the file.
2. The 2nd line: arbitraty header line.
3. Next lines contain information on atoms in the format (coordinates are in angstroms):
element_symbol x-coordinate y-coordinate z-coordinate

Example of a file in this format:
```
10
SAMSON Export
C -6.644 9.967 5.557
C -7.934 9.831 4.773
C -7.934 10.816 3.617
C -8.098 8.407 4.266
N -7.404 9.603 7.84
C -6.46 9.161 6.834
C -5.09 9.488 7.383
O -5.008 10.375 8.245
H -8.382 9.481 7.521
H -7.182 10.599 8.021
```

To test this exporter, you can export any system from SAMSON (*File > Save*, *File > Save as...*, *File > Save selection as...*) into this format.

**Note:** SAMSON already has an XYZ Exporter which is installed by default.
