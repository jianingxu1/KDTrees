# KDTrees
This program implements the K-dimensional Trees data structure using C++. It features the Standard, Relaxed and Squarish variations, being the latter one the most efficient in queries.

It offers the following functionalities:
- Creation of a kd-tree either empty of with n random points.
- Deletion of a kd-tree
- Insertion of a k-dimensional point
- Search of nearest neighbor given a point

#### Usage
Compile and create the executable:
```bash
make
```
The script performs experimentation with dimensions k=2 to 6 with the specified kd-tree variation and outputs the time execution results of the queries in the data folder. To run the script:
```
chmod +x script.sh
./script.sh <type of tree: 0 Standard, 1 Relaxed, 2 Squarish>
```
To delete object and executable files:
```
make clean
```
