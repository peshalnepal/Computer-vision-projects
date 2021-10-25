
# Store and Sort images by the number of pixel 
In this project , Images are read and store in vector and then sorted based on the size of the images. 

## Prerequisites:
- opencv is required to run this project and if not install follow previous documentation on logistic setup 
- camke is also needed and if not install in your device you can use following syntax to install <br/>
  ***`sudo apt-get install cmake`*** 

## Run the project
- Download the code from the Git
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake .`*** command
- After this, Run ***`make`*** command
- executable name **sortimages** has been created 
- To check the output, Run ***`./sortimages`*** command in terminal
- If user want to apply feature detect algorithm in specific images, the path to the images with their name and extension of images should be pass in ***`./sortimages pathtotheimage/imagename.extension pathtotheimage/imagename.extension pathtotheimage/imagename.extension`*** . Two images are to be passed as feature are to be compared.
- To close all the window press key **'esc'** from the keyboard
  

## Templates 
Templates are powerful tools that provide a function of code reusability. Functions or classes which can provide results for different data types without reusing code multiple times can be achieved by Templates. Source code contains only function/class but compiled code may contain multiple copies of the same function/class. 

## Standard Template Library
It is a standard library containing the Generic/template classes that provide common programming data structures and functions such as lists, stacks, arrays, etc.  

Four Components of STL are
- **Containers:**
  These are responsible for storing data of different data types. There are mainly three types of containers
    - Sequence containers: Where data are stored in sequential order. vectors, lists, Dequeue are some of the Sequence containers
    - Associative containers: Where data are store in key-value pairs. Direct access to data is faster and data are stored in tree-like structures. Map, multimap, set, multiset are some of the Associative containers.
    - Derived containers: Where data are store in one after another like in stack and direct access is hard to achieve. Some of the techniques used to extract data from piles of data are LIFO, FIFO. 
      Real-world modeling as data is stored in a stack or queue. Stack, queue, Priority queue are some of the Derived containers.
 
- **Algorithms:**
   Algorithms consist of a set of Generic function which processes data in the containers. Some of the algorithms are

    - Sorting
    - Searching
    - Important STL Algorithms
    - Useful Array algorithms
    - Partition Operations
- **Iterators:**
    Iterators are objects that point to the content of the containers. Even though these are objects they act as pointers.
- **Functors:**
    Functors are objects that can be treated as though they are a function or function pointer. Useful in place when values to be passed may vary for the function. Specially used in STL functions.

### **Steps involved to store and sort array**
- At first, images are stored in vector<Mat> which is a vector of mat object
- Then sort function is used which takes Functors whose main purpose is to compare the size of two images. 