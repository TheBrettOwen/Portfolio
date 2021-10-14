# Programming project 2: JUnit Testing
* Due date: Tuesday Nov 3 12:30 p.m.

**Goal:** The goal of the project is to help students understand the use of JUnit to test Java code.  You will create a set of unit tests, to test the behavior of the code in 2020Fall.git -> src/project2, project2 package.

**Unit testing** is used to test the behavior of the code (or parts of the code) written, without having to run the whole program. Assume that the front-end (RatingStatsApp console user interface) part of the program and the back-end part of the program (RatingSummary) are written by two different developers.  Unit testing ensures that the back-end code works correctly without having access to the front-end. 

In this project:
* Create JUnit tests to test the methods of class RatingSummary in src/project2 
  * including the ones inherited from AbstractRatingSummary. 
* Save the test methods in 2 files:
  * RatingSummaryTest.java - JUnit tests
  * RatingSummaryHamcrestTest.java - Hamcrest tests
* You **do not** test the other classes.
Start with testing the behavior of the class/methods under normal operation scenarios.  
* Mock objects can be created either in the same test method or before any test methods are run, using the @BeforeAll or @BeforeEach annotation. 

**Your code will be tested against src/project2/ code enforcing no source code modifications**

## Tasks:

1.	Implement the JUnit tests to test only the class RatingSummary.java. 
    * RatingSummaryTest.java - JUnit tests
	* RatingSummaryHamcrestTest.java - Hamcrest tests
	Try to be creative by coming up with test cases that can test as many different situations as possible. You don’t need to test the other classes.

2.	Use a standard Java coding style to improve your program’s visual appearance and make it more readable e.g. https://google.github.io/styleguide/javaguide.html

3.	Use Javadoc to document your code.


#[README](README.md) - Logistics, submission, compilation