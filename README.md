# Problem

We have a UI for showing a "process" consisting of several "jobs". Jobs can be executed in parallel or sequentially.

![image](https://github.com/user-attachments/assets/4f71e8c4-ed65-47b4-8ec4-212ddb67d516)

The UI is readonly, so users should not be able to re-arrange the placement of the boxes, change colours, edit text or anything like that. Rendering the boxes isn't a problem, but I'm having problems with the layout, i.e. where each box should go. What is a good algorithm for calculating the layout?

# Algorithm

- Assume data is a tree with one root.  ( If more than one job has no parents, add a dummy node whose children are the parentless jobs )
- Find single root
- Perform a depth first search from the root
- Each time more than one child is found, ADD rows for the new job chains
- Each time a job chain needs to wrap around, INSERT a new row.

# Input

```
first_job another_job
another_job FTP
another_job yet_another
FTP analyze
yet_another calculate
calculate mark
analyze post
post report
another_job j3_1
j3_1 j3_2

```

# Output
```
jobname        row     col
first_job       0       0
another_job     0       1
j3_1            0       2
j3_2            0       3
yet_another     1       1
calculate       1       2
mark            1       3
FTP             2       1
analyze         2       2
post            2       3
report          3       2
```

![image](https://github.com/user-attachments/assets/05112982-8b41-4ffd-8a7a-2243d7a43f8e)



