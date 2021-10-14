Project 3 due Dec 1 at 12:30 p.m.

## [project 3](PROJECT3.md) task [link](PROJECT3.md)

## How to use git repositories for project3 submission

0. ID or TeamID is **ID** in the text below 

1. If you have cloned 2020Fall repo, navigate to local src directory and pull the code 
```
cd 2020Fall
git pull
```

2. Save all your new work in your repo in new folder named project3: 
```
cd ..
cd ID
git pull
mkdir project3

```

* copy all the java files from 2020Fall/src/project3 folder to ID/project3 

3. make changes to RatingSummaryTest.java in **ID/project3** folder and save changes using IDE or text editor of choice 
  * Visual Studio Code
  * IntelliJ
  * Eclipse
  * Netbeans
  * Notepad++
  * Atom

4. Compile and run the program within your IDE or using the following commands. 

```
javac -d bin .\<ID>\project3\*.java
java -cp .\bin project3.RatingStatsApp
```


5. Check in changes often to  **ID** repository 
-> make sure you are in **ID** folder for git commandline:

```
cd CS3354/ID
git add project3/*.java
git commit -m "Project 3 code update comment here"
gitk
```
gitk will show you the status, close it to continue
```
git push origin:<ID>
```

6. Repeat step 4 and 5 often to save your work until done. 
  * it allows you to re-trace your steps
  * do not forget to list **ALL** team members under @author javadoc tag

7. Done! 

## Other Class resources 
* [lectures](https://canvas.txstate.edu)
* [material](https://git.txstate.edu/CS3354/2020Fall/tree/master/material)