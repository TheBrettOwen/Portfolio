Brett Owen, bmo23, A04850405

Task 4:
-The database object is an 11x5000 array, where the first 10 rows are moments, and the 11th row is the digit the image represents.
-For the binarization of the digit in classify digit, I simply used the binarize function and passed into it the digit image.
-The function also calculates 10 moments, those moments being u(0,10) and u(0,9)  through u(9,1) and u(10, 0). This is to have
	a substantial amount of moments with a wide range of exports.
-I used the last half of the dataset for the test images. After running tests and comparing true the 2207 true positives to the 
	5000 digits processed, the accuracy came out to be 44.14%.

The test function I used is included, as well as the database.mat file which has the database object I used. Also, most of the
	moment functions use the rawMoment function I wrote, also included in the folder. 