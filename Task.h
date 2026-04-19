// Muhammad_Yousaf_22i8797_F
#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <iomanip>
#include "Skill.h"
#include "Resource.h"
#include "List.h"

using namespace std;

struct Task
{
    string name;
    int duration;
    int ES;
    int EF;
    int LS;
    int LF;
    int slack;
    List<int> dependencies;
    int skill_id;
    int id;
    static int id_counter;

    Task(const Task &other)
        : name(other.name),
          duration(other.duration),
          ES(other.ES),
          EF(other.EF),
          LS(other.LS),
          LF(other.LF),
          slack(other.slack),
          dependencies(other.dependencies),
          skill_id(other.skill_id),
          id(other.id)
    {
    }

    Task() : name("NILL"), duration(-1), ES(-1), EF(-1), LS(-1), LF(999999), skill_id(-1), id(id_counter++), slack(-1)
    {
    }

    Task(string Name, int required_skill_id, int Duration) : name(Name), duration(Duration), ES(-1), EF(-1), LS(-1), LF(999999), slack(-1), skill_id(required_skill_id), id(id_counter++)
    {
    }

    void AddTaskDependencies(int dependency_task_id)
    {
        dependencies.insert(dependency_task_id);
    }

    void PrintBasicTaskInfo()
    {
        cout << "Task Id: " << id << "   Task Name: " << name << "   Task Duration: " << duration<<endl;
    }

    void PrintBasicScheduleTaskInfo()
    { //                    id              name                duration            ES            EF            LS            LF            slack
        cout << setw(15) << id << setw(15) << name << setw(15) << duration << setw(15) << ES << setw(15) << EF << setw(15) << LS << setw(15) << LF << setw(15) << slack << endl;
    }

    void PrintIdAndName()
    {
        cout << "task id:" << id << setw(20) << "task name:" << name;
    }

    bool checkExistanceOfDependency(int key_id)
    {
        if (dependencies.last_index == 0)
            return false;

        for (int i = 1; i <= dependencies.last_index; i++)
        {
            if (key_id == dependencies.getElement(i))
                return true;
        }
        return false;
    }
};
int Task::id_counter = 1;
#endif