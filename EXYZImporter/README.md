# EXYZ Importer

This SAMSON Element demonstrates how to implement an importer on an example of a simple XYZ-importer for files of the following format:

1. The 1st line: the number of atoms in the file.
2. The 2nd line: arbitraty header line.
3. Next lines contain information on atoms in the format (coordinates are in angstroms):
element_symbol x-coordinate y-coordinate z-coordinate

Example of a file in this format:
```
356
Model name
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

To test this importer, you can export (*File menu \ Save as*) any system from SAMSON in XYZ format and change the extension from `.xyz` to `.exyz`.

**Note:** SAMSON already has an XYZ Importer which is installed by default. 
