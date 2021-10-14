# Project 2 due Nov 3 12:30 p.m.

## project 2 problem formulation [link](PROJECT2.md)

## How to use git repositories for project2 submission

0. ID or TeamID is **ID** in the text below 

1. If you have cloned 2020Fall repo, navigate to local src directory and pull the code 
```
cd 2020Fall
git pull
```

2. Save all your new work in your repo in new foldere named project2: 
```
cd ..
cd ID
git pull
mkdir project2
```
* copy RatingSummaryTest.java file from test/project2 folder to ID/project2 

3. make changes to RatingSummaryTest.java in **ID/project2** folder and save changes using IDE or text editor of choice 
  * Visual Studio Code
  * IntelliJ
  * Eclipse
  * Netbeans
  * Notepad++
  * Atom
  
4. Compile and run JUnit5 testing, within your IDE or download junit-platform-console-standalone-1.7.0.jar from [here]( https://repo1.maven.org/maven2/org/junit/platform/junit-platform-console-standalone/1.7.0) and place it in lib folder at the same level with src, ID, and material folders. 

```
>>javac -d bin –cp ".;bin\;lib\*"  src\project2\*.java ID\project2\*.java
>>java -cp ".;bin\;lib\*" org.junit.platform.console.ConsoleLauncher --exclude-engine=junit-vintage --include-engine=junit-jupiter --fail-if-no-tests --scan-classpath
```


5. Check in changes often to  **ID** repository 
-> make sure you are in **ID** folder for git commandline:

```
cd 2020Fall/ID
git add project2/RatingSummaryTest.java
git add project2/RatingSummaryHamcrestTest.java
git commit -m "Project 2 code update comment here"
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
* [lectures](canvas.txstate.edu)
* [material](git.txstate.edu/CS3354/material)
