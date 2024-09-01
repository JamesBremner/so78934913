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
```

# Output
```
jobname        row     col
first_job       0       0
another_job     0       1
yet_another     0       2
calculate       0       3
mark            1       2
FTP             2       1
analyze         2       2
post            2       3
report          3       2
```

![image](https://github.com/user-attachments/assets/d8ad63a9-a0f8-4ee8-9a7c-35dd94d8617c)


