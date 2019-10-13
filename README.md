# IGBTQ-SchedulingAlgorithm
Improved Group Based Time Quantum is a CPU Scheduling algorithm which is derived from Robin algorithm and is proved to
be very efficient and gives much better result than any other Pre-Emptive Round Robin
algorithm. In this algorithm every process is first sorted in ascending order of burst times and
then equally divided into four groups. For each group the mean of the burst time is considered as
the Time Quantum for that group. Time quantum is a major factor which decides efficiency of
Round Robin algorithm. So taking the average ensures that each process gets considerate amount
of time in each cycle. Also, if 90% of the processes’ burst time is exhausted then it is allowed to
run to completion else it will be pre-empted if necessary. Compared to other algorithms like
Round Robin, Dynamic Round Robin with Controlled Pre-emption, Group Based Time
Quantum, and this algorithm has proved to be faster and more efficient and the tasks are
scheduling with much lesser Average Waiting Time and Average Turnaround Time.

Referrences-  Hadiza Musa Mijinyawa, Saleh E Abdullahi: Improved Group Based Time Quantum (IGBTQ) CPU.

https://ieeexplore.ieee.org/abstract/document/8333324

Psuedocode:
PSEUDO CODE
1) FILL Ready_Queue (RQ) with burst times.
2) IF Ready_Queue is empty go to step 9.
3) Copy burst times and store in RQ and then sort the processes available in ascending order.
4) Group the sorted burst times into four equal parts and place the grouped processes in queues
Q1, Q2, Q3, and Q4 respectively.
5) For each group, take the mean of the burst times as its time quantum (i.e. calculate TQ1,
TQ2, TQ3 and TQ4).
6) For each process, assign its time quantum to be the value of the TQ calculated for its group.
7) Now the process are run just like Round Robin scheduling apart from the face that each
group has a different time quantum assigned to it.
7) FOR each process IN RQ{
IF process[remaining_burst_time] ≤ process[initial_burst_time]*0.10 THEN
COMPLETE process
CALCULATE WT, TT
 }
8) Calculate AWT, ATAT by adding individual burst time and turnaround time and the
dividing them by the number of processes.
9) END
