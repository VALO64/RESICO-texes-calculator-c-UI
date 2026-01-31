# Taxes calculator C++ RESICO

This is a related project with two other repositories that I have in my account.
- My UI in python  https://github.com/VALO64/GUI-RESICO-Calculator
- The hello world template using wxWidgets https://github.com/VALO64/wxWidgets_basic_template
You can access to the information to understand more about the project.

## ## Why didn't I continue with python to create the main UI?

Well this is just a personal decision, in the beginning I decided to practice my UI coding skills with python but I felt frustrated with the library of Qt even that's a high level language. My first coding language was C, so I tried to implement something cross platform, something that I could build and works in any machine also I wanted to comeback to my origins, for that reason I decided to use C++ and wxWidgets library for my project, in a weird way I understand C better than other languages so I just decided to read the documentation and update my progress.

## How did I communicate between languages Python and C++?

If you have time coding in different languages you should know the answer. But if you don't I'll explain to you. Imagine that there's a person that speaks Spanish and there's another one that just speaks mandarin, in theory the communication sounds imposible but let's say that both speak english so now they can communicate and translate the information to their own language is the same with the communication between the languages in this case I used Json files that's the equivalent to english in the example that I gave before so with json files you can convert the information given for an script/ code and use it in another coding language.

In python the library is included already, but in the case of C++ we have to install a library to manage json files and use other one that is included on the code named **fstream**. 
```
#include <fstream>
```

### Command to install json library on MAC.

First you have to have installed homebrew in your system, after that just use the following command.

```
brew install nlohmann-json
```

When you have it installed on your system you can use it like this.

```
#include <nlohmann/json.hpp>
```

Also if you want to compile the code using the terminal you have to specify that you're using the library linking it.

```
clang++ -std=c++11 read_json.cpp -o programa -I/opt/homebrew/include
```

## Screenshots

- Version 1.1
<img width="403" height="250" alt="imagen" src="https://github.com/user-attachments/assets/0fc5fc5a-4c31-4e9f-9126-27e210abb087" />

- Version 1.2
Tool bar with different options as select the pdf to make the program calculate without typing any number and help option.

<img width="252" height="328" alt="imagen" src="https://github.com/user-attachments/assets/153933e2-9230-41a6-9507-f0fb3ed262c5" />

-Version 1.2.1
New button added but needs set new settings and conditions

<img width="500" height="383" alt="image" src="https://github.com/user-attachments/assets/650f83e2-4a57-430e-be40-100934994aec" />


