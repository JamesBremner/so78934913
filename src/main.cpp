#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"
#include "GraphTheory.h"

raven::graph::cGraph g;

class cJob
{
public:
    std::string myName;
    int myIndex; // graph vertex index
    int myRow;
    int myCol;
    int myChildVisitCount;

    cJob(
        const std::string &name,
        int index,
        int row,
        int col)
        : myName(name),
          myIndex(index),
          myRow(row),
          myCol(col),
          myChildVisitCount(0)
    {
    }
};

std::vector<cJob> vJobs;

void readfile(const std::string &fname)
{
    g.directed();
    std::ifstream ifs(fname);
    if (!ifs.is_open())
        throw std::runtime_error("cannot open file");
    std::string line;
    while (getline(ifs, line))
    {
        int p = line.find(" ");
        if (p == -1)
        {
            std::cout << line << "\n";
            throw std::runtime_error("bad format");
        }
        g.add(
            line.substr(0, p),
            line.substr(p + 1));
    }
}
int findRoot()
{
    for (int vi = 0; vi < g.vertexCount(); vi++)
    {
        if (!g.adjacentIn(vi).size())
        {
            vJobs.emplace_back(
                g.userName(vi), vi, 0, 0);
            return vi;
        }
    }
    throw std::runtime_error("Cannot find root");
}

int visitCount(int vi)
{
    auto it = find_if(
        vJobs.begin(), vJobs.end(),
        [&](const cJob &j) -> bool
        {
            return (j.myIndex == vi);
        });
    if (it == vJobs.end())
        return 0;
    it->myChildVisitCount++;
    return it->myChildVisitCount;
}

int parentJob(int index)
{
    auto it = find_if(
        vJobs.begin(), vJobs.end(),
        [&](const cJob &j) -> bool
        {
            return (j.myIndex == index);
        });
    return it - vJobs.begin();
}

void search()
{
    int row, col;
    row = col = 0;
    int root = findRoot();
    // std::cout << "visit\n";
    dfs(
        g,
        root,
        [&](int vi) -> bool
        {
            // runs every time a vertex is visited by DFS

            if (vi == root)
                return true;

            int parentGraphIndex = g.adjacentIn(vi)[0];
            int siblings = g.adjacentOut(parentGraphIndex).size();
            int sibCount = visitCount(parentGraphIndex);

            int parentJobIndex = parentJob(parentGraphIndex);
            if (siblings == 1)
            {
                col = vJobs[parentJobIndex].myCol + 1;
                row = vJobs[parentJobIndex].myRow;
            }
            else
            {
                if (sibCount == 1)
                {
                    col = vJobs[parentJobIndex].myCol + 1;
                    row = vJobs[parentJobIndex].myRow;
                }
                else
                {
                    col = vJobs[parentJobIndex].myCol;
                    row = vJobs[parentJobIndex].myRow + sibCount - 1;
                }
            }

            // std::cout << g.userName(vi)
            //           << " parent " << g.userName(parentGraphIndex)
            //           << " " << siblings
            //           << " " << sibCount
            //           << " placing " << " at " << row << "," << col
            //           << "\n";

            vJobs.emplace_back(
                g.userName(vi), vi, row, col);
            return true;
        });

    std::cout << "\n";
}
void text()
{
    std::cout << "jobname        row     col\n";
    for (auto &j : vJobs)
    {
        std::cout.width(15);
        std::cout << std::left
                  << j.myName
                  << "\t" << j.myRow
                  << "\t" << j.myCol
                  << "\n";
    }
}
class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500}),
          lb(wex::maker::make<wex::label>(fm))
    {
        lb.move(50, 50, 100, 30);
        lb.text("Hello World");

        show();
        run();
    }

private:
    wex::label &lb;
};

main()
{
    readfile("../dat/dat1.txt");
    search();
    text();

    cGUI theGUI;
    return 0;
}
