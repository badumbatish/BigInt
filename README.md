

# BigInt_v2 overview
[BigInt](https://github.com/tanghocle123/BigInt) is reborned, with better time and space complexity for all operations (base 10 only).
## Index

- [About](#About)
- [Usage](#usage)
  - [Installation](#installation)
  - [Commands](#commands)
- [Development](#development)
  - [Pre-Requisites](#pre-requisites)
  - [Development Environment](#development-environment)
  - [File Structure](#-file-structure)
  - [Build](#build) 
- [Community](#community)
  - [Contribution](#contribution)
- [FAQ](#faq)
- [Resources](#resources)
- [Gallery](#gallery)
- [Credit/Acknowledgment](#creditacknowledgment)
- [License](#license)

## About
BigInt_v2 is a better version of [BigInt](https://github.com/tanghocle123/BigInt). It uses std::string under the hood to compute addition, subtraction, multiplication and in the future, division. 
This is a student side-project so please don't put too much hope in it. However, it is still amazingly fast compared to other student's BigInt projects and (might be) safer than other C BigInt project. 


## Usage
Use it to do Big Integer computation (>64 bit or >128 bit)

###   Installation
C++ is very versatile so I would expect this works well on Windows, Mac and Linux.
Download the repository to begin using right away.

###   Commands
```C++
#include <iostream>
#include "BigInt.h"

int main()
{
	BigInt a("123",1); // 1 indicate positive number
	BigInt b("456",1); // 1 indicate positive number
	std::cout << "This is addition:\t" << a+b << std::endl;
	std::cout << "This is subtraction:\t" << a-b << std::endl;
	std::cout << "This is multiplication:\t" << a*b << std::endl;
}
```
Result:
```
This is addition:	579
This is subtraction:	-333
This is multiplication:	56088
Press ENTER to continue...
```
##  Development

###  Pre-Requisites
- [Googletest](https://github.com/google/googletest) and [BigIntTester](https://github.com/tanghocle123/BigIntTester) for testing
- C++11 or newer for developing code
- A compiler.
- Text editor or IDE.

###  Development Environment
As long as you have a compiler, you should be good

###  File Structure
You can begin develop by having these file ready in this structure

```
├── BigInt_v2
│   ├── BigInt.cpp
│   ├── BigInt.h
│   └──main.cpp
└── BigInt_tester
    ├── include_test.h
 	├── main.cpp
    └── Test_folder
```
###   Build
For testing, run main.cpp in BigInt_tester

For writing code, run main.cpp in BigInt_v2

## Community

This is open-source, you can use this library how ever you wish to use it.

 ###  Contribution

 Your contributions are always welcome and appreciated. Following are the things you can do to contribute to this project.

 1. **Report a bug** <br>
 If you think you have encountered a bug, and I should know about it, feel free to report it at [tanghocle456@gmail.com]() and I will take care of it.

 2. **Request a feature** <br>
 You can also request for a feature at [tanghocle456@gmail.com](), and if it is viable, it will be picked for development.  

 3. **Code contribution** <br>



## FAQ
```
Q: Why use std::string
A: Because it is very friendly for beginner developers with its features.
Plus, I used to tinker with BigInt using std::string, so I feel like I got 
something to hold on to
```

```
Q: How long did it took to write all this?
A: Including researching time, coding time and testing time, I would say 
about 1 week and a half.
```


```
Q: Why this project?
A: It all happens when the corona virus hit and I lost my job. So I stay home
and write a BigInteger library for fun.
```
```
Q: How fast are your library compared to others?
A: Very fast, there is no benchmark, but I heavily ad-hoc coded the library just for base 10, so expect it to be very very fast.

Q: You have no multithreading, how can it be fast?
A: I ultilize bitwise operator, pointer iterator, use backward strings to calculate multiplication.
Const refference, move constructor are also implemented so that passing parameters
wouldn't be too expensive that it would slow down my library.
Using the same two string to execute the recursive Karatsuba function means no
string or substring copying in the functions, which is a huge increase in effiency.
```
##  Resources
These are the resources I learned from to make this library come true.
### String optimization
[An Overview of Optimization](https://www.oreilly.com/library/view/optimized-c/9781491922057/ch01.html)

[Optimize String Use: A Case Study](https://www.oreilly.com/library/view/optimized-c/9781491922057/ch01.html)

[Why use string::iterator rather than index?](https://stackoverflow.com/a/1995123)

[Why pass by reference ??](https://www.learncpp.com/cpp-tutorial/73-passing-arguments-by-reference/)

[std::move by en.cppreference.com](https://en.cppreference.com/w/cpp/utility/move)
### String multiplication
[https://en.wikipedia.org/wiki/Karatsuba_algorithm](https://en.wikipedia.org/wiki/Karatsuba_algorithm)

[Grade school multiplication by tutorialspoint](https://www.tutorialspoint.com/multiply-strings-in-cplusplus)
### Testing
[https://github.com/google/googletest/blob/master/googletest/docs/primer.md](https://github.com/google/googletest/blob/master/googletest/docs/primer.md)
### Utilities
[https://stackedit.io/](https://stackedit.io/) for online readme editing

[Mastering markdown](https://guides.github.com/features/mastering-markdown/)

[README template I use for most of my projects.](https://www.reddit.com/r/programming/comments/cfeu99/readme_template_i_use_for_most_of_my_projects/)


##  Gallery

## Credit/Acknowledgment
Kudos to my uncle Mike, for introducing me to google test (which is a huge deal because I just can't fix all the bugs without my honey sugar test case.

Thank you Github, I copied code from the site some times since I was soooo lazy to come up with a grade school multiplication implementation.

Kudos to my best buddy Son Nguyen for cheering me up in bad times, I wouldn't did it without you man.
##  License
What license? *** THIS IS  <b>  OPEN SOURCE!!! </b> </em>
