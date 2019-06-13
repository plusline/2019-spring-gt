# Graph-Theory-Project-Template
Project template of course - Graph Theory (EE6622E) in National Cheng Kung University.

## How to run

### Linux

```
# clone first (with submodule)
$ git clone --recursive https://github.com/<your-name>/Graph-Theory-Project-Template.git
# (Option) build libfakemn.a
$ cd fake-mininet && make lib && cd .. && cp fake-mininet/libfakemn.a .
# build
$ make 
# run 
$ ./main.out
```

### Windows

If your PC is `window 10`, then you need to install the related dependencies. For example, if you are using `VSCode` as your IDE, then you can install the plugin of `C/C++` in your vscode. And then install the following programs/packages:
* mingw
* git

Step by step to create `c_cpp_properties.json` and `tasks.json`:
* `Ctrl+Shift+P` -> `C/C++: Edit Configuration` -> then you have the first JSON file.
* `Ctrl+Shift+P` -> `Tasks: Configure Task` -> then you have the second JSON file.

Here is the setting of `c_cpp_properties.json` and `tasks.json`:
```json
# c_cpp_properties.json (If your mingw installed in another folder, then you have to change the value in `compilterPath`)
{
    "configurations": [
        {
            "name": "MinGW",
            "intelliSenseMode": "gcc-x64",
            "includePath": [
                "$(workspaceFolder)"
            ],
            "compilerPath": "C:/mingw/bin/gcc.exe",
            "cStandard": "c11",
            "cppStandard": "c++11"
        }
    ],
    "version": 4
}

# tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-g",
                "main.cc",
                "-o",
                "main.exe",
                "-Ifake-mininet/lib",
                "-g3",
                "-L.",
                "-lfakemn_win",
                "-std=c++11"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

After all the settings have been done, we can press `Ctrl+Shift+B` to run the task, if your settings is correct, then there will have an executable file which named `main.exe`.

Or you can just [DOWNLOAD a pre-built VM images](http://gofile.me/39GpL/XU5tznyO6) provided by TA.

> [Guide of environment setting](https://hackmd.io/-5WZQC-1QqOeV3KUX65tEw?view) on Windows.

## TODO - Your descriptions about solutions/algorithms/results

###
problem description
Given a directed graph graph.txt, the program will find out the path going through all the edges in the graph. 

### algorithms
1. distinguish the vertex from their <strong>more indegree</strong> and <strong>more outdegree</strong>
Using class DEGREE to record the information of indegree and outdegree of each vertex.
using class BI_DEGREE to record the information of difference of degree, then I devide them into more indegree list(in_list) and more outdegree list(out_list).

2. pair the <strong>more indegree</strong> and <strong>more outdegree</strong>
Checking whether the summation of indegree minus outdegree in in_list must equal to the summation of outdegree munus indegree in out_list, and pair the vertex in in_list with the one in out_list.
If the difference of in-out degree is more than one, the vertext need to pair up more than one time. 
We pair the vertext with greedy algorithm. We choose the vertex in in out_list orderly and find the vertex with the minimum vertex with it, ans so on.
If match up any vertex, I will add the flow of the minimum path from out_list to in_list. I will print out the result with all the flow in middle.svg.

3. find the correct order of walk(It is a big cycle, too)
Using class SIMPLE_EDGE(one_edge) to record every steps of walk.
I need to find the right order of every steps of walk which the tail of the previous edge is the head of current edge, all the way to the final edge.
I use double for loops to find the cycle. If the cycle not use all the edge in one_edge, it find the inner loop. At the next while loop, I will move the wrong loop to the end of the list(one_edge). The process will try the otheer direction of walk.
### results
You need to write the graph in graph.txt. Just list all the edge in the graph. 

We can observe the graph and the flow in middle.svg.

We can find the answer in answer.txt.

This algorithm can't garantee to find the shortest path. Because I want this program to run in polynomial time, I use greedy algorithm to find the path which is nearly the shortest path.


### makefile
```make``` to compile the main.cc.

```./main.out``` to run the main function.

```make plot``` to plot the middle.svg.

