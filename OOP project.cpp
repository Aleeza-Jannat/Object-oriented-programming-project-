#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
/*This class represents a user with properties like firstName, lastName, username, and password.
It declares a pure virtual function getRole(), making User an abstract base class,
and enforcing that any derived class must implement this function.
It also defines a virtual destructor to ensure proper cleanup in derived
classes when objects are deleted*/
class User {    //super-class user
public:         //access modifier
    char firstName[50];     //holds the first name 
    char lastName[50];      //holds the last name 
    char username[50];      //holds the username
    char password[50];      //holds the password
    virtual const char* getRole() = 0;      //pure virtual function (representing the role e.g admin or player)
    virtual ~User() {}      //virtual destructor 
};
/*The Admin class extends the User class, inherits its members
(variables and functions), and implements the abstract getRole() function.
The constructor initializes the inherited string fields to empty values.
The getRole() function returns "Admin", providing the specific role for an Admin object*/
class Admin : public User {     //inherited by user super-class
public:
    Admin() {       //constructor of admin class 
        firstName[0] = '\0';        //setting first element to null character, setting all empty by default
        lastName[0] = '\0';
        username[0] = '\0';
        password[0] = '\0';
    }
    virtual const char* getRole() {         //overridden version of getrole
        return "Admin";     //representing the role of admin user 
    }
};
class QuizResult {
public:
    int score;      //the user's score on the quiz
    int total;      //the total possible score or points on the quiz.
};
/*The Player class extends User, inheriting all of its members and functionality while adding new behavior
specific to the Player.It introduces an array of QuizResult objects to store up to 100 quiz results,
and it keeps track of the number of results with resultCount.The getRole() function is overridden to
return the string "Player", giving Player its own distinct role, which can be useful in applications
like games or user management systems.*/
class Player : public User {        //inherited by super-class user
public:
    static const int MAX_RESULTS = 100;     //all instances of player will share same value for max result,maximum number of quizz results a player can store 
    // Why is static used here ?
    // Static means this constant belongs to the class itself, not to individual objects of the class.
    // All instances of Player share the same value of MAX_RESULTS.
    QuizResult quizResults[MAX_RESULTS];        //object created of class Quizzresults which is declared earlier
    int resultCount;        //to keep track that how many quiz results have been added to quizzresults array
    Player() {      //consstructor for player class
        firstName[0] = '\0';    //setting first element to null character, setting all empty by default
        lastName[0] = '\0';
        username[0] = '\0';
        password[0] = '\0';
        resultCount = 0;        //setting default result count as zero(No result stored)
    }
    virtual const char* getRole() {     //overridden version of getrole
        return "Player";        //representing the role of player user 
    }
};
/*Question is an abstract base class for representing a question with an ID and text.
It includes pure virtual functions that must be implemented by derived classes, including
getting the question’s weight, validating an answer, and printing the question.*/
class Question {
public:
    int id;     //for question type
    char text[256];     //a character array that can store the text of the question 
    Question() {        //default constructor
        id = 0;         //Initializes the id to 0(default value)
        text[0] = '\0';     //Initializes the text array to an empty 
    }
    //these 3 are pure virtual functions 
    virtual int getWeight() = 0;      //pure virtual function representing the weightage of questions  
    virtual bool validateAnswer(const char* answer) = 0;     //pure virtual function to check whether the anwer is valid or not     
    virtual void printQuestion() = 0;       //pure virtual function that prints or displays the question to the user.
    virtual ~Question() {}      //The virtual destructor ensures that if a Question object is deleted via a pointer to the base class
};
/*This function compares two C-style strings (char arrays) for equality, ignoring case differences.
It uses the _stricmp function, which is a case-insensitive string comparison function.
If the strings are equal (ignoring case), it returns true, otherwise false.*/
bool equalsIgnoreCase(const char* a, const char* b) {
    return _stricmp(a, b) == 0;    // _stricmp returns 0 if the strings are equal (ignoring case)
}/*MCQQuestion is a derived class from the Question class, representing a multiple-choice question.
It stores the correct choice and the four possible choices for the user to select from.
The class implements the pure virtual functions from the Question class: getWeight(), validateAnswer(), and printQuestion().*/
class MCQQuestion : public Question {
public:
    char correctChoice[256];   //holds the correct choice for the multiple-choice question
    char choices[4][256];      //array of 4 choices (each with up to 255 characters) for the question

    MCQQuestion() : Question() {  //constructor for MCQQuestion
        for (int i = 0; i < 4; i++) {
            choices[i][0] = '\0';  //initializing each choice to be an empty string
        }
        correctChoice[0] = '\0';    //initializing the correct choice to be an empty string
    }

    virtual int getWeight() {     //returns the weight (or points) for this question, in this case, 2 points
        return 2;
    }

    /*The validateAnswer function checks if the provided answer matches the correct choice,
    ignoring case differences by calling the equalsIgnoreCase function.*/
    virtual bool validateAnswer(const char* answer) {
        return equalsIgnoreCase(answer, correctChoice);   //returns true if the answer matches the correct choice
    }

    /*The printQuestion function displays the text of the question, followed by the four choices,
    and then shows the correct answer for reference (in a real quiz, this might be hidden).*/
    virtual void printQuestion() {
        cout << text << endl;    //prints the text of the question
        cout << "Choices: ";      //prints "Choices: "
        for (int i = 0; i < 4; i++) {
            cout << choices[i];   //prints each choice
            if (i < 3) {
                cout << ", ";
            }
        }
        cout << " (Correct: " << correctChoice << ")" << endl;   //prints the correct choice (for reference)
    }
};
/*TFQuestion is a derived class from the Question class, representing a true/false question.
It stores a boolean value indicating the correct answer (true or false).
The class implements the pure virtual functions from the Question class: getWeight(),
validateAnswer(), and printQuestion().*/
class TFQuestion : public Question {
public:
    bool correctAnswer;   //stores the correct answer for the true/false question (true or false)
    TFQuestion() : Question() {  //constructor for TFQuestion
        correctAnswer = false;    //default correct answer is false
    }
    virtual int getWeight() {     //returns the weight (or points) for this question, in this case, 1 point
        return 1;
    }
    /*The validateAnswer function checks if the provided answer matches the correct answer.
    It compares the answer (ignoring case) with the string "true" or "false" based on the correctAnswer value.*/
    virtual bool validateAnswer(const char* answer) {
        if (equalsIgnoreCase(answer, "true") && correctAnswer) {
            return true;    //returns true if the answer is "true" and correctAnswer is true
        }
        if (equalsIgnoreCase(answer, "false") && !correctAnswer) {
            return true;    //returns true if the answer is "false" and correctAnswer is false
        }
        return false;   //returns false if the answer does not match the correct answer
    }

    /*The printQuestion function displays the text of the question and the correct answer (true/false).
    In a real quiz, the correct answer would typically be hidden, but here it's shown for reference.*/
    virtual void printQuestion() {
        cout << text << " (Answer: ";   //prints the question text followed by " (Answer: "
        if (correctAnswer) {
            cout << "true";   //if correctAnswer is true, prints "true"
        }
        else {
            cout << "false";  //if correctAnswer is false, prints "false"
        }
        cout << ")" << endl;   //prints the closing parenthesis and moves to the next line
    }
};
/*CompleteQuestion is a derived class from the Question class, representing 
a question where the user needs to provide a complete answer.It stores the correct answer as a
string and implements the pure virtual functions from the Question class: getWeight(), validateAnswer(),
and printQuestion().*/
class CompleteQuestion : public Question {
public:
    char correctAnswer[256];   //stores the correct answer for the complete question (up to 255 characters)

    CompleteQuestion() : Question() {  //constructor for CompleteQuestion
        correctAnswer[0] = '\0';    //initializes correctAnswer to an empty string
    }

    virtual int getWeight() {     //returns the weight (or points) for this question, in this case, 3 points
        return 3;
    }

    /*The validateAnswer function checks if the provided answer matches the correct answer,
    ignoring case differences by calling the equalsIgnoreCase function.*/
    virtual bool validateAnswer(const char* answer) {
        return equalsIgnoreCase(answer, correctAnswer);   //returns true if the answer matches the correct answer
    }

    /*The printQuestion function displays the text of the question along with the correct answer
    (in a real quiz, the correct answer would typically be hidden, but here it's shown for reference).*/
    virtual void printQuestion() {
        cout << text << " (Answer: " << correctAnswer << ")" << endl;   //prints the question text followed by the correct answer
    }
};

/*AuthenticationService is a class responsible for user authentication. It manages a collection of users (both Admin and Player objects) and provides functions for login, adding users, and updating user information.*/
class AuthenticationService {
private:
    User* users[100];    //array to store up to 100 users
    int userCount;       //keeps track of the number of users in the system

public:
    AuthenticationService() {    //constructor for AuthenticationService
        userCount = 0;  //initializing the user count to 0
        //Creating an admin user and adding it to the users array
        Admin* admin = new Admin();
        strcpy(admin->firstName, "Admin");
        strcpy(admin->lastName, "User");
        strcpy(admin->username, "admin");
        strcpy(admin->password, "admin");
        users[userCount++] = admin;
        //Creating a player user and adding it to the users array
        Player* player = new Player();
        strcpy(player->firstName, "Player");
        strcpy(player->lastName, "User");
        strcpy(player->username, "player");
        strcpy(player->password, "player");
        users[userCount++] = player;
    }

    ~AuthenticationService() {    //destructor to clean up dynamic memory
        for (int i = 0; i < userCount; i++) {
            delete users[i];   //delete each user to avoid memory leaks
        }
    }

    /*The login function checks the provided username and password.
    If a matching user is found, it returns the corresponding User object, otherwise, it returns NULL.*/
    User* login(const char* username, const char* password) {
        for (int i = 0; i < userCount; i++) {
            if (equalsIgnoreCase(username, users[i]->username) &&
                strcmp(password, users[i]->password) == 0) {
                return users[i];   //returns the user if username and password match
            }
        }
        return NULL;    //returns NULL if no matching user is found
    }

    /*The addUser function adds a new user to the system if the username doesn't already exist
    and the maximum user limit (100) hasn't been reached. Returns true if the user is added successfully, false otherwise.*/
    bool addUser(User* user) {
        for (int i = 0; i < userCount; i++) {
            if (equalsIgnoreCase(user->username, users[i]->username)) {
                return false;   //returns false if the username already exists
            }
        }
        if (userCount < 100) {
            users[userCount++] = user;   //adds the user if there's space
            return true;
        }
        return false;   //returns false if the maximum number of users is reached
    }

    /*The getUserCount function returns the current number of users in the system.*/
    int getUserCount() {
        return userCount;
    }

    /*The getUserAt function retrieves a user at the specified index if it's valid.
    Otherwise, it returns NULL.*/
    User* getUserAt(int index) {
        if (index < 0 || index >= userCount)
            return NULL;   //returns NULL if the index is out of bounds
        return users[index];   //returns the user at the specified index
    }

    /*The updateName function allows updating the first and last name of a user.
    It prompts the user to enter the new names and stores them in the user's firstName and lastName attributes.*/
    void updateName(User* user) {
        cout << "Enter new first name: ";
        cin.getline(user->firstName, 50);   //prompts and gets new first name
        cout << "Enter new last name: ";
        cin.getline(user->lastName, 50);    //prompts and gets new last name
        cout << "Name updated successfully." << endl << endl;   //prints a success message
    }
};
/*QuizService is a class that manages quiz questions. It allows adding, viewing, and loading questions from a file.
It also handles selecting quiz questions for a quiz and cleaning up memory when destroyed.*/
class QuizService {
private:
    Question* questions[200];    //array to store up to 200 questions
    int questionCount;           //keeps track of the number of questions in the system
    int questionCounter;         //used to assign unique IDs to questions

public:
    QuizService() {   //constructor for QuizService
        questionCount = 0;   //initializing question count to 0
        questionCounter = 1;  //starting question ID from 1
    }

    ~QuizService() {  //destructor to clean up dynamically allocated memory
        for (int i = 0; i < questionCount; i++) {
            delete questions[i];   //delete each question to avoid memory leaks
        }
    }

    /*The viewAllQuestions function displays all the available questions in the system.
    If there are no questions, it informs the user that there are no questions available.*/
    void viewAllQuestions() {
        if (questionCount == 0) {
            cout << "\033[31mNo questions available.\033[0m" << endl<<endl;   //prints error message if no questions exist
            return;
        }
        cout << "Total Questions: " << questionCount << endl;  //prints the total number of questions
        for (int i = 0; i < questionCount; i++) {
            questions[i]->printQuestion();  //prints each question in the system
        }
        cout << endl;
    }

    /*The loadQuestionsFromFile function loads quiz questions from a file.
    It processes the file line by line and adds questions to the system,
    handling MCQ, TF (True/False), and Complete questions based on the file content.*/
    void loadQuestionsFromFile() {
        cout << "Enter the full file location to load questions (e.g., C:\\path\\to\\file.txt): ";
        char fileLocation[256];   //stores the file location entered by the user
        cin.getline(fileLocation, 256);

        ifstream fin(fileLocation);   //opens the file for reading
        if (!fin.good()) {   //checks if the file was opened successfully
            cout << "\033[31mFile not found at the specified location.\033[0m" << endl<<endl;   //prints error if file not found
            return;
        }
        char line[256];
        while (!fin.eof()) {   //continues reading until the end of the file
            if (!fin.getline(line, 256)) break;   //reads a line from the file
            if (strlen(line) == 0) {
                continue;   //skips empty lines
            }
            char type[256];
            strcpy(type, line);   //stores the question type (MCQ, TF, or COMPLETE)
            for (int t = 0; t < (int)strlen(type); t++) {
                type[t] = (char)toupper(type[t]);   //converts the question type to uppercase
            }
            if (strcmp(type, "MCQ") == 0) {   //if the question type is MCQ (Multiple Choice Question)
                char mcqText[256], correct[256], c2[256], c3[256], c4[256];
                if (!fin.getline(mcqText, 256) || !fin.getline(correct, 256) ||
                    !fin.getline(c2, 256) || !fin.getline(c3, 256) || !fin.getline(c4, 256)) {
                    break;  //if any of the necessary lines are missing, break the loop
                }
                MCQQuestion* q = new MCQQuestion();   //creates a new MCQQuestion object
                q->id = questionCounter++;  //assigns a unique ID to the question
                strcpy(q->text, mcqText);   //sets the text of the question
                strcpy(q->correctChoice, correct);  //sets the correct choice
                strcpy(q->choices[0], correct);   //sets the choices for the MCQ question
                strcpy(q->choices[1], c2);
                strcpy(q->choices[2], c3);
                strcpy(q->choices[3], c4);
                if (questionCount < 200) {
                    questions[questionCount++] = q;   //adds the question to the list
                }
            }
            else if (strcmp(type, "TF") == 0) {   //if the question type is TF (True/False)
                char tfText[256], boolStr[256];
                if (!fin.getline(tfText, 256) || !fin.getline(boolStr, 256)) {
                    break;   //if any of the necessary lines are missing, break the loop
                }
                TFQuestion* q = new TFQuestion();   //creates a new TFQuestion object
                q->id = questionCounter++;   //assigns a unique ID to the question
                strcpy(q->text, tfText);   //sets the text of the question
                if (equalsIgnoreCase(boolStr, "true")) {   //sets the correct answer based on the input
                    q->correctAnswer = true;
                }
                else {
                    q->correctAnswer = false;
                }
                if (questionCount < 200) {
                    questions[questionCount++] = q;   //adds the question to the list
                }
            }
            else if (strcmp(type, "COMPLETE") == 0) {   //if the question type is COMPLETE (open-ended question)
                char compText[256], compAnswer[256];
                if (!fin.getline(compText, 256) || !fin.getline(compAnswer, 256)) {
                    break;   //if any of the necessary lines are missing, break the loop
                }
                CompleteQuestion* q = new CompleteQuestion();   //creates a new CompleteQuestion object
                q->id = questionCounter++;   //assigns a unique ID to the question
                strcpy(q->text, compText);   //sets the text of the question
                strcpy(q->correctAnswer, compAnswer);   //sets the correct answer for the question
                if (questionCount < 200) {
                    questions[questionCount++] = q;   //adds the question to the list
                }
            }
            else {
                cout << "\033[31mInvalid question type: \033[0m" << endl;   //prints an error if the question type is invalid
            }
        }
        fin.close();   //closes the file
        cout << "Questions loaded successfully." << endl<<endl;   //prints success message
    }

    /*The getQuizQuestions function retrieves up to 5 quiz questions from the system and stores them in the outQuestions array.
    It returns the number of questions retrieved.*/
    int getQuizQuestions(Question* outQuestions[5]) {
        int count;
        if (questionCount < 5) {
            count = questionCount;  //if there are fewer than 5 questions, retrieve all available questions
        }
        else {
            count = 5;   
        }
        for (int i = 0; i < count; i++) {
            outQuestions[i] = questions[i];   //copies the questions to the output array
        }
        return count;   //returns the number of questions retrieved
    }

    /*The addQuestion function adds a new question to the quiz if there's space available in the system (up to 200 questions).*/
    void addQuestion(Question* question) {
        if (questionCount < 200) {
            questions[questionCount++] = question;   //adds the question to the list
        }
    }
};/*AdminService is a class that provides functionalities for Admin users.
It allows managing users and quiz questions, such as adding new users and adding questions to the quiz.*/
class AdminService {
private:
    AuthenticationService* authService;   //pointer to AuthenticationService for user management
    QuizService* quizService;             //pointer to QuizService for question management

public:
    /*Constructor that initializes the AdminService with AuthenticationService and QuizService*/
    AdminService(AuthenticationService* as, QuizService* qs) {
        authService = as;
        quizService = qs;
    }

    /*viewAllUsers function displays the list of all users in the system, showing their usernames, roles,
    and names (first and last)*/
    void viewAllUsers() {
        cout << "List of users:" << endl;
        int cnt = authService->getUserCount();   //gets the total number of users
        for (int i = 0; i < cnt; i++) {
            User* u = authService->getUserAt(i);   //gets each user object
            cout << "Username is: " << u->username << "     (" << "Role:" << u->getRole() << ") -"
                << "     First name: " << u->firstName << "    Last name: " << " (" << u->lastName << ") -" << endl;
        }
        cout << endl;
    }

    /*addNewUser function allows the admin to create a new user (Admin or Player).
    It ensures the user enters non-empty values for first name, last name, username, password, and role (Admin/Player).*/
    void addNewUser() {
        char firstName[50];
        char lastName[50];
        char username[50];
        char password[50];
        char role[50];

        // Loop to input and validate first name (must not be empty)
        do {
            cout << "Enter first name: ";
            cin.getline(firstName, 50);

            if (strlen(firstName) == 0) {
                cout << "\033[31mError: First name cannot be empty. Please try again.\033[0m" << endl;
            }
        } while (strlen(firstName) == 0);

        // Loop to input and validate last name (must not be empty)
        do {
            cout << "Enter last name: ";
            cin.getline(lastName, 50);

            if (strlen(lastName) == 0) {
                cout << "\033[31mError: Last name cannot be empty. Please try again.\033[0m" << endl;
            }
        } while (strlen(lastName) == 0);

        // Loop to input and validate username (must not be empty)
        do {
            cout << "Enter username: ";
            cin.getline(username, 50);

            if (strlen(username) == 0) {
                cout << "\033[31mError: Username cannot be empty. Please try again.\033[0m" << endl;
            }
        } while (strlen(username) == 0);

        // Loop to input and validate password (must not be empty)
        do {
            cout << "Enter password: ";
            cin.getline(password, 50);

            if (strlen(password) == 0) {
                cout << "\033[31m Error: Password cannot be empty. Please try again.\033[0m" << endl;
            }
        } while (strlen(password) == 0);

        // Loop to input and validate role (must not be empty and should be either Admin or Player)
        do {
            cout << "Enter role (Admin/Player): ";
            cin.getline(role, 50);

            if (strlen(role) == 0) {
                cout << "\033[31mError: Role cannot be empty. Please try again.\033[0m" << endl;
            }
        } while (strlen(role) == 0);
        cout << endl;
        // Creating a new user object based on the role
        User* newUser = NULL;
        if (equalsIgnoreCase(role, "Admin")) {   //creates an Admin user
            Admin* a = new Admin();
            strcpy(a->firstName, firstName);
            strcpy(a->lastName, lastName);
            strcpy(a->username, username);
            strcpy(a->password, password);
            newUser = a;
        }
        else {   //creates a Player user
            Player* p = new Player();
            strcpy(p->firstName, firstName);
            strcpy(p->lastName, lastName);
            strcpy(p->username, username);
            strcpy(p->password, password);
            newUser = p;
        }

        // Attempt to add the new user to the authentication service
        if (authService->addUser(newUser)) {
            cout << "User added successfully." << endl;
        }
        /*Checking for Username Existence: The actual check for whether the username already exists is
        happening inside the addUser method of the authService. The addUser function is assumed to internally
        check whether the username provided by the user already exists in the system. This would typically
        involve searching through a list of existing users or querying a database for a matching username.
        TO CHECK IF THE USERNAME EXIST OR NOT there was another methord too like we can overload = operator 
        should be done in user class
          // **Overloaded assignment operator to check for username uniqueness**
    User& operator=(const User& other) {
        if (this != &other) {  // Prevent self-assignment
            if (strcmp(username, other.username) == 0) {  
                cout << "\033[31mError: Username already exists.\033[0m" << endl;
            } else {
                // If the username is different, assign it
                strncpy(username, other.username, sizeof(username));
            }
        }
        return *this;
    }
*/
        else {
            cout << "\033[31mUsername already exists.\033[0m" << endl;   //shows error if username already exists
            delete newUser;   //delete the new user object if it wasn't added
        }
    }


    /*addNewQuestion function allows the admin to create a new quiz question (MCQ, TF, or Complete type).
    It prompts the admin to enter the necessary details for the selected question type.*/
    void addNewQuestion() {
        char type[50];
        cout << "Enter question type (MCQ/TF/COMPLETE): ";
        cin.getline(type, 50);
        for (int i = 0; i < (int)strlen(type); i++) {
            type[i] = (char)toupper(type[i]);   //convert question type to uppercase
        }

        // Handle MCQ (Multiple Choice Question)
        if (strcmp(type, "MCQ") == 0) {
            char mcqText[256], correct[256], c2[256], c3[256], c4[256];
            cout << "Enter question text: ";
            cin.getline(mcqText, 256);
            cout << "Enter correct choice: ";
            cin.getline(correct, 256);
            cout << "Enter choice 2: ";
            cin.getline(c2, 256);
            cout << "Enter choice 3: ";
            cin.getline(c3, 256);
            cout << "Enter choice 4: ";
            cin.getline(c4, 256);

            MCQQuestion* q = new MCQQuestion();
            q->id = -1;   //set question ID to -1, as it will be assigned later
            strcpy(q->text, mcqText);
            strcpy(q->correctChoice, correct);
            strcpy(q->choices[0], correct);
            strcpy(q->choices[1], c2);
            strcpy(q->choices[2], c3);
            strcpy(q->choices[3], c4);
            quizService->addQuestion(q);   //add the new MCQ question to the quiz
            cout << "MCQ Question added." << endl;

        }
        // Handle TF (True/False) Question
        else if (strcmp(type, "TF") == 0) {
            char tfText[256], boolStr[256];
            cout << "Enter question text: ";
            cin.getline(tfText, 256);
            cout << "Enter answer (true/false): ";
            cin.getline(boolStr, 256);

            TFQuestion* q = new TFQuestion();
            strcpy(q->text, tfText);
            if (equalsIgnoreCase(boolStr, "true")) {
                q->correctAnswer = true;
            }
            else {
                q->correctAnswer = false;
            }
            quizService->addQuestion(q);   //add the new TF question to the quiz
            cout << "TF Question added." << endl;
        }
        // Handle Complete Question (Open-ended question)
        else if (strcmp(type, "COMPLETE") == 0) {
            char compText[256], compAnswer[256];
            cout << "Enter question text: ";
            cin.getline(compText, 256);
            cout << "Enter correct answer: ";
            cin.getline(compAnswer, 256);

            CompleteQuestion* q = new CompleteQuestion();
            q->id = -1;   //set question ID to -1, as it will be assigned later
            strcpy(q->text, compText);
            strcpy(q->correctAnswer, compAnswer);

            quizService->addQuestion(q);   //add the new Complete question to the quiz
            cout << "Complete Question added." << endl;
        }
        else {
            cout << "\033[31mInvalid question type.\033[0m" << endl;   //if the type entered is invalid
        }
        cout << endl;
    }
   
};/* PlayerService class handles all player-related functionalities including:
   - Starting a quiz for the player by retrieving questions from the QuizService.
   - Calculating and displaying the player's quiz scores.
   - Displaying statistics such as highest, lowest, and average scores.
   - Displaying the player's individual quiz results. */
class PlayerService {
private:
    QuizService* quizService;   // A reference to the QuizService that handles questions

public:
    /* Constructor that initializes the PlayerService with QuizService */
    PlayerService(QuizService* qs) {
        quizService = qs;  // Store the reference to the QuizService
    }

    /* startQuiz function starts a new quiz for the player.
       It retrieves 5 questions from the quiz service and evaluates the player's answers. */
    void startQuiz(Player* player) {
        Question* selectedQuestions[5];  // Array to hold 5 questions for the quiz
        int count = quizService->getQuizQuestions(selectedQuestions);   // Get 5 questions from QuizService
        if (count < 5) {  // Check if there are enough questions to start the quiz
            cout << "\033[31mNot enough questions to start the quiz.\033[0m" << endl<<endl;  // Display error message
            return;  // Exit the function if there are less than 5 questions
        }
        int score = 0;  // Initialize player's score to 0
        int total = 0;  // Initialize total score to 0
        for (int i = 0; i < count; i++) {  // Loop through all the questions
            total += selectedQuestions[i]->getWeight();   // Add question's weight to the total score
        }
        cout << "The quiz contains 5 questions by default including MCQ's ,TF and Complete Questions" << endl;
        cout << "\033[3m---MARKS LIST--- " << endl<<"Complete Question=3 marks"<<endl<<"Multiple Choice Question=2 marks"<<endl<<"True\False Questions=1 mark\033[0m"<<endl;
        // Loop through each question to present it to the player
        for (int i = 0; i < count; i++) {
            cout << "\nQuestion " << (i + 1) << ": " << endl;  // Display the question number
            cout << selectedQuestions[i]->text << endl;  // Display the question text
            
/*Dynamic_cast is used here to safely check if the base class pointer (Question*) is actually
pointing to an object of the derived class (MCQQuestion*), ensuring type safety
and preventing undefined behavior when accessing derived class-specific members.*/
// Handle MCQ questions by checking the type and casting the question pointer to MCQQuestion
            MCQQuestion* mcqPtr = dynamic_cast<MCQQuestion*>(selectedQuestions[i]);
            if (mcqPtr != NULL) {  // If the question is of type MCQ
                cout << "Options:" << endl;  // Display options for MCQ
                for (int j = 0; j < 4; j++) {  // Loop through the 4 choices for MCQ
                    cout << (char)('A' + j) << ". " << mcqPtr->choices[j] << endl;  // Display choices A, B, C, D
                }
            }
            /*What is dynamic cast?
            dynamic_cast is a type of cast in C++ used for safely converting pointers or references
            between related types in a class hierarchy, typically from a base class to a derived class.
            It performs runtime checks to ensure the cast is valid, and it is commonly used when
            dealing with polymorphic types (classes with virtual functions).*/

            cout << "Your answer: ";  // Prompt the player for their answer
            char answer[256];  // Declare a buffer to store the player's answer
            cin.getline(answer, 256);  // Get the player's answer from input

            // For MCQ, translate the answer to the full choice if it's a letter (A, B, C, D)
            if (mcqPtr != NULL) {  // If the question is of type MCQ
                char upperAns = (char)toupper(answer[0]);  // Convert the answer to uppercase
                int index = upperAns - 'A';  // Convert the letter to the corresponding index (A=0, B=1, C=2, D=3)
                if (index >= 0 && index < 4) {  // Check if the index is valid
                    strcpy(answer, mcqPtr->choices[index]);  // Map the letter to the full choice
                }
                else {  // If the index is invalid (outside A-D)
                    cout << "\033[31mInvalid choice, skipping this question.\033[0m" << endl;  // Display error message
                    continue;  // Skip this question and move to the next one
                }
            }

            // Check if the answer is correct, and update the score if necessary
            if (selectedQuestions[i]->validateAnswer(answer)) {  // If the answer is correct
                cout << "Correct!" << endl;  // Display correct message
                score += selectedQuestions[i]->getWeight();  // Add the weight of the question to the score
            }
            else {  // If the answer is wrong
                cout << "\033[31mWrong answer.\033[0m" << endl;  // Display wrong answer message
            }
        }

        // Record the player's quiz result (if there's space for more results)
        if (player->resultCount < Player::MAX_RESULTS) {  // If the player has room for more results
            QuizResult r;  // Create a new QuizResult object
            r.score = score;  // Set the score for this result
            r.total = total;  // Set the total possible score for this result
            player->quizResults[player->resultCount++] = r;  // Store the result in the player's quizResults array and increment result count
        }

        // Display the player's score at the end of the quiz
        cout << "\nQuiz completed! Your score: " << score << "/" << total << endl;  // Display final score
    }

    /* displayScoreStatistics shows the player’s highest, lowest, and average score across all quizzes taken */
    void displayScoreStatistics(Player* player) {
        if (player->resultCount == 0) {  // Check if the player has taken any quizzes
            cout << "\033[31mNo quizzes taken yet.\033[0m" << endl<<endl;  // Display error message if no quizzes
            return;  // Exit the function if no quizzes were taken
        }

        int highest = player->quizResults[0].score;  // Initialize highest score to the first result's score
        int lowest = player->quizResults[0].score;   // Initialize lowest score to the first result's score
        int sum = 0;  // Initialize sum of scores to 0

        // Calculate highest, lowest, and total score
        for (int i = 0; i < player->resultCount; i++) {  // Loop through all quiz results
            int s = player->quizResults[i].score;  // Get the score for this quiz result
            if (s > highest) highest = s;  // Update highest score if this score is higher
            if (s < lowest)  lowest = s;   // Update lowest score if this score is lower
            sum += s;  // Add this score to the total sum
        }

        double average = (double)sum / (double)player->resultCount;  // Calculate average score
        cout << "Highest Score: " << highest << endl;  // Display the highest score
        cout << "Lowest Score: " << lowest << endl;    // Display the lowest score
        cout << "Average Score: " << average << endl;  // Display the average score
    }

    /* displayAllScores displays all the scores the player has achieved in different quizzes */
    void displayAllScores(Player* player) {
        if (player->resultCount == 0) {  // Check if the player has taken any quizzes
            cout << "\033[31mNo quizzes taken yet.\033[0m" << endl<<endl;  // Display error message if no quizzes
            return;  // Exit the function if no quizzes were taken
        }

        // Loop through all the scores and display them
        for (int i = 0; i < player->resultCount; i++) {  // Loop through each result
            cout << "Score: "
                << player->quizResults[i].score  // Display the score
                << "/"
                << player->quizResults[i].total  // Display the total score
                << endl;
        }
    }

    /* displayLastQuizDetails shows the score of the player's most recent quiz */
    void displayLastQuizDetails(Player* player) {
        if (player->resultCount == 0) {  // Check if the player has taken any quizzes
            cout << "\033[31mNo quizzes taken yet.\033[0m" << endl<<endl;  // Display error message if no quizzes
            return;  // Exit the function if no quizzes were taken
        }

        // Access the most recent result and display it
        QuizResult& lastResult = player->quizResults[player->resultCount - 1];  // Get the most recent result
        cout << "Last Quiz Score: "
            << lastResult.score  // Display the score of the most recent quiz
            << "/"
            << lastResult.total  // Display the total score of the most recent quiz
            << endl;
    }
};
/* GameEngine class is responsible for the main game logic.
It facilitates user authentication, handles admin and player menus,
starts and manages the quiz game, and performs actions based on user roles. */
class GameEngine {
private:
    AuthenticationService authService;  // Handles user authentication (login, name updates)
    QuizService quizService;           // Manages quiz-related services (question handling)
    AdminService* adminService;        // Admin-specific functionalities (user management, question handling)
    PlayerService* playerService;      // Player-specific functionalities (quiz management, score tracking)

public:
    /* Constructor initializes services for Admin and Player, and sets up their dependencies */
    GameEngine() {
        // Initialize AdminService with references to AuthenticationService and QuizService
        adminService = new AdminService(&authService, &quizService);
        // Initialize PlayerService with a reference to QuizService
        playerService = new PlayerService(&quizService);
    }

    /* Destructor cleans up dynamically allocated AdminService and PlayerService objects */
    ~GameEngine() {
        delete adminService;   // Deallocate AdminService object
        delete playerService;  // Deallocate PlayerService object
    }

    /* Main method that runs the game logic continuously until the user exits.
       Handles login and user role determination (Admin or Player). */
    void start() {
        while (true) {  // Infinite loop for the game session
            cout << "|------------------------|" << endl;
            cout << "\033[35mWelcome to the Quiz Game!\033[0m" << endl;  // Display game introduction
            cout << "|------------------------|" << endl;
            // Get username input (username and password)
            char username[50];
            char password[50];
            do {
                cout << endl;
                cout << "\033[1mEnter username:\033[0m ";
                cin.getline(username, 50);  // Get user input for username

                if (strlen(username) == 0) {  // Check if username is empty
                    cout << "\033[31mError Username cannot be empty. Please try again.\033[0m" << endl;
                }
            } while (strlen(username) == 0);  // Repeat until a valid username is entered

            // Get password input and validate it
            do {
                cout << "Enter password: ";
                cin.getline(password, 50);  // Get user input for password

                if (strlen(password) == 0) {  // Check if password is empty
                    cout << "\033[31mError: Password cannot be empty. Please try again.\033[0m" << endl;
                }
            } while (strlen(password) == 0);  // Repeat until a valid password is entered

            // Attempt login using AuthenticationService
            User* user = authService.login(username, password);
            if (user == NULL) {  // If login fails
                cout << "\033[31mInvalid username or password. Try again.\033[0m" << endl;
                cout << endl;
                continue;  // Retry the login process
            }

            // Check if the logged-in user is an Admin or Player and proceed accordingly
            if (equalsIgnoreCase(user->getRole(), "Admin")) {  // If the user is an Admin
                Admin* adminPtr = dynamic_cast<Admin*>(user);  // Attempt to cast user to Admin
                if (adminPtr != NULL) {
                    adminMenu(adminPtr);  // Show Admin menu if the cast is successful
                }
            }
            else {  // If the user is a Player
                Player* playerPtr = dynamic_cast<Player*>(user);  // Attempt to cast user to Player
                if (playerPtr != NULL) {
                    playerMenu(playerPtr);  // Show Player menu if the cast is successful
                }
            }
        }
    }
private:
    /* adminMenu displays the menu of actions available to Admin users.
       It handles different actions related to user management, question handling, etc. */
    void adminMenu(Admin* admin) {
        cout << endl;
        cout << "Welcome, " << admin->firstName << " (" << admin->getRole() << ")!" << endl;
        
        cout << "The admin menu is shown below: " << endl;
        cout << endl;
        bool exitMenu = false;
        while (!exitMenu) {  // Loop for admin menu until the user chooses to exit
            cout << "[1] Switch Accounts" << endl;
            cout << "[2] Update Name" << endl;
            cout << "[3] View All Users" << endl;
            cout << "[4] Add New User" << endl;
            cout << "[5] View All Questions" << endl;
            cout << "[6] Add New Question" << endl;
            cout << "[7] Load Questions From File" << endl;
            cout << "[8] Exit" << endl;
            cout << endl;
            cout << "Your choice: ";
            char choice[10];
            cin.getline(choice, 10);  // Get admin's menu choice

            // Admin actions based on the user's menu choice
            if (choice[0] == '1') {
                exitMenu = true;  // Exit the menu if the user chooses to switch accounts
            }
            else if (choice[0] == '2') {
                authService.updateName(admin);  // Admin can update their name
            }
            else if (choice[0] == '3') {
                adminService->viewAllUsers();  // View all users
            }
            else if (choice[0] == '4') {
                adminService->addNewUser();  // Add a new user
            }
            else if (choice[0] == '5') {
                quizService.viewAllQuestions();  // View all quiz questions
            }
            else if (choice[0] == '6') {
                adminService->addNewQuestion();  // Add a new quiz question
            }
            else if (choice[0] == '7') {
                quizService.loadQuestionsFromFile();  // Load questions from file
            }
            else if (choice[0] == '8') {
                exit(0);  // Exit the game
            }
            else {
                cout << "\033[31mInvalid choice.\033[0m" << endl;  // Handle invalid menu choices
            }
        }
    }

    /* playerMenu displays the menu of actions available to Player users.
       It handles different actions related to quiz taking, score tracking, etc. */
    void playerMenu(Player* player) {
        cout << endl;
        cout << "Welcome, " << player->firstName << " (" << player->getRole() << ")!" << endl;
        cout << "The player menu is shown below: "<<endl;
        cout << endl;
        bool exitMenu = false;
        while (!exitMenu) {  // Loop for player menu until the user chooses to exit
            cout << "[1] Switch Accounts" << endl;
            cout << "[2] Update Name" << endl;
            cout << "[3] Start New Quiz" << endl;
            cout << "[4] Display Score Statistics" << endl;
            cout << "[5] Display All Scores" << endl;
            cout << "[6] Display Last Quiz Details" << endl;
            cout << "[7] Exit" << endl;
            cout << endl;
            cout << "Your choice: ";
            char choice[10];
            cin.getline(choice, 10);  // Get player's menu choice

            // Player actions based on the user's menu choice
            if (choice[0] == '1') {
                exitMenu = true;  // Exit the menu if the user chooses to switch accounts
            }
            else if (choice[0] == '2') {
                authService.updateName(player);  // Player can update their name
            }
            else if (choice[0] == '3') {
                playerService->startQuiz(player);  // Start a new quiz
            }
            else if (choice[0] == '4') {
                playerService->displayScoreStatistics(player);  // Display score statistics
            }
            else if (choice[0] == '5') {
                playerService->displayAllScores(player);  // Display all quiz scores
            }
            else if (choice[0] == '6') {
                playerService->displayLastQuizDetails(player);  // Display last quiz details
            }
            else if (choice[0] == '7') {
                exit(0);  // Exit the game
            }
            else {
                cout << "\033[31mInvalid choice.\033[0m" << endl;  // Handle invalid menu choices
            }
        }
    }
};
/* main function initializes the game engine and starts the game.
 It is the entry point of the program and will keep the game running until the user exits. */
int main() {
    GameEngine engine;  // Create an instance of the GameEngine class, which starts the game
    engine.start();     // Call the start method of the GameEngine to initiate the game loop
    return 0;  // Return 0 to indicate successful program execution
}
