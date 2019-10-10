

# Parallel and Distributed Computing 

[Course Website](https://sites.usc.edu/prasanna/teaching/fall2019/ee451/)
---
This repositary contains programming assignments completed as a part of the course EE 451 - Parallel and Distributed computing under Prof. [Viktor Prasanna](https://sites.usc.edu/prasanna/) in Fall 2019, USC.

## Getting Started

Implementation of different programming models - PRAM, Shared memory, Message Passing for different algorithms 

PHW1 - Basic Naive Matrix, BlocK Matrix  and KMeans Clustering Implementation

[**Programming Homework #1**](https://github.com/SiddhantNadkarni/Parallel-and-Distributed-Computing/blob/master/Homework_PDFs/EE%20451%20F%202019%20PHW%201.pdf) <br/>
[**Report on Programming Homework #1**](https://github.com/SiddhantNadkarni/Parallel-and-Distributed-Computing/blob/master/Reports/PHW_1/report.pdf) <br/>

* Q1 a,b - Comparision of Matrix Multiplications type (Naive vs Block) in terms of time taken (s) and performance (MFLOPs) <br/>
![Fig1](https://github.com/SiddhantNadkarni/Parallel-and-Distributed-Computing/blob/master/Plots/PHW_1/Figure_1.png) <br/>
![Fig2](https://github.com/SiddhantNadkarni/Parallel-and-Distributed-Computing/blob/master/Plots/PHW_1/Figure_2.png) <br/>

* Q2 - K Means Clustering of grayscale Intensities in an Image <br/>
![Screen Shot 2019-09-13 at 10 30 41 PM](https://user-images.githubusercontent.com/19183728/64903892-2bc00400-d676-11e9-8787-1259c5a2f736.png)<br/>


PHW2 - Parallelized Naive Matrix and Parallelized K-Means Clustering Implementation [PThread Shared Programming Models]

### Prerequisites

All Homeworks are written in C++11, compiler used: g++ (latest version) <br/>
[Boost](https://www.boost.org/doc/libs/1_62_0/more/getting_started/windows.html) C++ library version 1.70.0

### Directory Layout

```bash
├── Homework_PDFs
│   ├── EE 451 F 2019 PHW 1.pdf
│   └── EE_451_F_2019_HW_2.pdf
├── Input
│   └── input.raw
├── Plots
│   ├── Figure_1.png
│   ├── Figure_2.png   
│   └── plotGraph.py
├── Reports
│   ├── report.pdf  
│   └── report.docx
├── src
│   ├── HW_1  
│   └── HW_2
├── License
├── Makefile
└── README.md
```

### Building

Git clone the repositary and run the makefile.

```
git clone https://github.com/SiddhantNadkarni/Parallel-and-Distributed-Computing.git
cd src/PHW_<homework number>
make
```


## Running the tests

```
For PHW1: 
./p1a
./p1b <block_Size>
./p2 <path to input image>

For PHW2:

```




## Authors

* **Siddhant Nadkarni** 



## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details


## Acknowledgments

* [Victor K. Prasanna](https://sites.usc.edu/prasanna/)
* [Introduction to Parallel Computing](http://srmcse.weebly.com/uploads/8/9/0/9/8909020/introduction_to_parallel_computing_second_edition-ananth_grama..pdf)



