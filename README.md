# CS4346_BEEGAI
CS 4346: Artificial Intelligence
Project #1-Spring 2023
Due Date: Feb.15, 2023
Create an intelligent computer expert system for an emergency room of a hospital to 
diagnose toxic substances and poisons and to recommend the treatment based on the diagnosis. 
Perform research using Web or any other source to collect knowledge about the symptoms caused by 
toxic substance and poisons as well as their treatments. The emergency room staff will feed the 
symptoms of the patient. Using Backward Chaining, your expert system will diagnose the toxic 
substance or the poison and then using Forward Chaining, it will recommend the treatment.  After 
collecting knowledge, develop a decision tree for Backward Chaining and a decision tree for the 
Forward Chaining.  Then transform the decision trees into rules.  The decision trees should be big 
enough to generate a minimum of thirty rules in total (more rules are fine) for Backward chaining. 
The Forward chaining, the number of rules will be equal the number of toxic substance you are 
considering.  The rules should contain variables. Implement the expert system program, employing 
Backward Chaining and Forward Chaining methodologies. The backward chaining will diagnose the 
toxic substances/poisons and forward chaining will provide the treatment.
Develop a user-friendly interface, which receives input data from an emergency room staff in 
restricted English format, uses keyword matching, and responds in a restricted English format.
Implement the expert system program, employing Backward Chaining and Forward 
Chaining methodologies. 
The Backward chaining and Forward chaining algorithms have been provided on CANVAS 
for you to write programs for these inference Engines in C++ programming language. 
In addition, the Backward chaining and Forward chaining programs written in C language 
have also been provided  on CANVAS, but these programs are intentionally made inefficient and 
erroneous. Instead of blindly using these inference engine programs, you must study them and 
rewrite them in C++ language by employing Software Engineering principles which prohibits 
‘GO TO’ statements and discourage global variable.  
You have a choice of writing your own programs in C++ language using the provided 
algorithms or rewrite given C language programs in C++. In each case, separate Knowledge 
base and Inference Engine parts of each program and bring efficiency in functionality and 
output using your creativity. Efficiency methods include dynamic memory management and 
Hashing functions. 
Using any other algorithms or programs from any other source including web will be 
treated as plagiarism, subject to severe penalty. 
Your ‘main’ function will call the two other functions, i.e., ‘Identify Poison’ based on 
backward chaining and ‘Treatment’ based on forward chaining.
Form a team of a maximum of three students. You are expected to develop the decision 
trees, rules, interface, and the inference engines as a team. After programs are developed, each 
member of the team will follow the following six steps individually:
1. Run the program with the rules for a minimum of three goals (three Poisons). Each run will 
be initiated by a user through the Interface. The program will identify the type of the poison 
and provide a list of treatments for that poison.
2. Print intermediate results of at least one run to trace your program.
3. Analyze the results, and the efficiency of the program. It should include how good are 
the results, how much memory is used, how fast was the program, and how the 
changes you made could have affected the efficiency and processing of the program.
4. Write his/her Project REPORT containing the explanation of the problem and the 
domain, decision tree, rules, methodologies used (Backward and Forward), the 
program, a copy of the source code, detailed explanations of the modifications to the 
program you implemented, and the analysis of the program, and the analyses of 
results as defined in item #3 above.  Also, clearly identify the contribution of each 
team member.
5. Demonstrate the execution and performance of the program in Dr. Ali’s Office.
6. In order to run your programs, upload your Files with full instructions to run your 
programs. Upload instructions are given below:
Warning:  EACH STUDENT MUST PERFORM STEPS 1 TO 5 INDIVIDUALLY.  DO 
NOT COPY PROGRAMS FROM ANY SOURCE EXCEPT THE PROGRAMS I HAVE 
PROVIDED THROUGH TRACS. ALSO, DO NOT COPY REPORT FROM YOUR 
PARTNER OR ANY OTHER PERSON.
Note: Each team must demonstrate the execution of the programs in Dr. Ali’s office
Project Submission Instructions 
REPORT SUBMISSION: 
 Upload your project report on CANVAS as a file [ABSOLUTELY NO 
EMAILS; Minus 50 points for email submissions] and make sure it 
can be downloaded easily.
 Also, upload a Readme file containing detailed instructions on how to run 
your program.
SOURSE CODE and related files SUBMISSION: 
Upload source code file as well as other files needed to run your program and 
verify your results. Source code file naming convention must be: Project1-
student ID.cpp; Naming convention of other files will be similar except the file 
extensions. Your source code must run on a PC computer.
The file uploading instructions are given below:

Login to CANVAS
Access CS 4346 spring 23 course, then follow the following steps:
 Click on [Assignments].
 Select Project #1
 Click on ‘Submit Assignment’
 Choose your Files one by one, and UPLOAD them
 Agree to tool’s End-User License Agreement
 Click on ‘Submit Assignment’
 The attachment(s) will be listed in the order they were entered.
  You may also click [Preview] to view your submission.
 Click [Submit] when you are done.


//////////////////////////////////////////
////////TO RUN AND USE THE PROGRAM////////
//////////////////////////////////////////

To compile the program, compile it using g++ main.cpp
To start running the program, type ./a.out
Answer any prompts the program asks, and it will give an answer.
The following are all correct in their diagnosis and treatment outputs given their inputs.