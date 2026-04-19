// Muhammad_Yousaf_22i8797_F
#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <string>
#include "List.h"
#include "Task.h"
#include "Resource.h"
#include "SupportingFunction.h"

using namespace std;

class Project
{
public:
    string name;
    int duration;
    List<Task> tasks;
    List<Resource> resources;
    int id;
    static int id_counter;

    Project(string Name) : name(Name), duration(-1), id(id_counter++)
    {
    }
    Project() : duration(-1), id(id_counter++), name("MY Project")
    {}

    Task &getTask(int id_of_task) // id and index of task in list of tasks are same
    {
        return tasks.getElement(id_of_task);
    }
    Resource &getResource(int id_of_resource) // id and index of resource in list of tasks are same
    {
        return resources.getElement(id_of_resource);
    }

    void PrintResourcesInfo()
    {
        if (resources.last_index == 0)
        {
            cout << "No Resources!" << endl;
            cout << endl;
        }
        else
        {
            for (int i = 1; i <= resources.last_index; i++)
            {
                resources.getElement(i).DisplayResourceInfo();
            }
        }
    }

    void PrintTasksBasicInfo()
    {
        if (tasks.last_index == 0)
        {
            cout << "No Tasks!" << endl;
            cout << endl;
        }
        else
        {
            for (int i = 1; i <= tasks.last_index; i++)
            {
                tasks.getElement(i).PrintBasicTaskInfo();
            }
        }
    }

    void DisplayAllSkillsPossessedbyResources()
    {
        // Displaying all available skill information
        for (int i = 1; i <= resources.last_index; i++)
        {
            resources.getElement(i).skill.DisplaySkillInfo();
        }
    }

    void setTaskDuration()
    {
        // modify task duration of all tasks
        int new_duration;
        for (int i = 1; i <= tasks.last_index; i++)
        {
            cout << "Enter new task Duration of task " << tasks.getElement(i).name << " of id:" << i << " : ";
            IntInputAndValidation(new_duration, 1, 99);

            tasks.getElement(i).duration = new_duration;
        }
    }

    void set_nth_TaskDuration(int nth_TaskDuration, int new_duration)
    {
        // modify task duration of nth tasks
        tasks.getElement(nth_TaskDuration).duration = new_duration;
    }

    void PrintTaskDependencyList()
    {
        List<int> tempDependenciesList;
        // display the dependency of all tasks
        for (int i = 1; i <= tasks.last_index; i++)
        {
            cout << endl
                 << "- ";
            tasks.getElement(i).PrintIdAndName();
            cout << endl;

            cout << "Dependencies: " << endl;

            for (int k = 1; k <= tasks.last_index; k++)
            {
                if (tasks.getElement(i).checkExistanceOfDependency(k))
                {
                    cout << "   -|";
                    tasks.getElement(k).PrintIdAndName();
                    cout << endl;
                }
            }
            cout << "__________________________________________" << endl;
        }
    }

private:
    void PrintBasicSchedule()
    {
        cout << setw(15) << "id" << setw(15) << "name" << setw(15) << "duration" << setw(15) << "ES" << setw(15) << "EF" << setw(15) << "LS" << setw(15) << "LF" << setw(15) << "slack" << endl;
        for (int i = 1; i <= tasks.last_index; ++i)
        {
            tasks.getElement(i).PrintBasicScheduleTaskInfo();
        }
        return;
    }

    int calculateESAndEF() // it will return maxEF for the further calculations of LS and LF
    {
        int maxEF = 0;
        Task *current_task;
        List<int> calTasksInd;
        List<int> tempDependencies;
        for (int i = 1; i <= tasks.last_index; i++)
        {
            current_task = &tasks.getElement(i);
            if (current_task->ES == 0)
            {

                maxEF = current_task->EF = current_task->duration;
                calTasksInd.insert(i);
            }
        }

        for (int i = 1; i <= calTasksInd.last_index; i++)
        {
            int current_cal_index = calTasksInd.getElement(i);
            for (int j = 1; j <= tasks.last_index; j++)
            {
                current_task = &tasks.getElement(j);
                if (current_task->checkExistanceOfDependency(current_cal_index))
                {
                    if (tasks.getElement(current_cal_index).EF > current_task->ES)
                        current_task->ES = tasks.getElement(current_cal_index).EF;
                    current_task->EF = current_task->ES + current_task->duration;

                    if (current_task->EF > maxEF)
                        maxEF = current_task->EF;

                    tempDependencies = current_task->dependencies;
                    bool calculated = true;
                    for (int k = 1; k <= tempDependencies.last_index; k++)
                    {
                        if (tasks.getElement(tempDependencies.getElement(k)).ES == -1)
                            calculated = false;
                    }
                    if (calculated)
                        calTasksInd.insert(current_task->id);
                }
            }
        }
        current_task = nullptr;
        delete current_task;
        current_task = nullptr;
        tempDependencies = List<int>();
        calTasksInd = List<int>();

        return maxEF;
    }

    void calculateLSAndLF(int maxEF)
    {
        Task *current_task;
        Task *cal_task;
        List<int> calTasksInd;
        // List<int> calTasksInd2;
        List<int> tempDependencies;

        // cout<<"8th element dep print() : ";
        // tasks.getElement(8).dependencies.print();

        for (int i = 1; i <= tasks.last_index; i++)
        {
            current_task = &tasks.getElement(i);
            bool independent = true;
            for (int j = 1; j <= tasks.last_index; j++)
            {
                if (tasks.getElement(j).checkExistanceOfDependency(i))
                {
                    // cout<<j<<" is dependent on "<<i<<endl;
                    independent = false;
                }
            }
            if (independent)
            {
                current_task->LF = maxEF;
                current_task->LS = maxEF - current_task->duration;
                calTasksInd.insert(i);
            }
        }
        // cout<<"8th element dep print() : ";
        // tasks.getElement(8).dependencies.print();

        for (int i = 1; i <= calTasksInd.last_index; ++i)
        {
            cal_task = &tasks.getElement(calTasksInd.getElement(i)); // pointing task with id of calTasksInd(task whose LS and LF is calculated) ith element
            // cout<<"i: "<<i<<" calTask : id" <<cal_task->id<<endl;
            if (!cal_task->dependencies.isEmpty())
                tempDependencies = cal_task->dependencies;
            else
                continue;

            for (int j = 1; j <= tempDependencies.last_index; j++)
            {
                // cout<<"j: "<<j<<endl;
                // cout<<"   temp on j: "<<j<<" jth dep: "<<tempDependencies.getElement(j)<<endl;
                current_task = &tasks.getElement(tempDependencies.getElement(j)); // current task is the task with the id equal to jth dependency of cal_task(calculated task)
                                                                                  // cout<<"hello"<<endl;
                if (cal_task->LS < current_task->LF)
                {
                    current_task->LF = cal_task->LS;
                    current_task->LS = current_task->LF - current_task->duration;
                    bool found = false;
                    for (int k = 1; k <= calTasksInd.last_index; k++)
                    {
                        if (calTasksInd.getElement(k) == current_task->id)
                            found = true;
                    }
                    if (!found)
                        calTasksInd.insert(current_task->id);
                    // calTasksInd.remove(1);
                }
            }

            tempDependencies = List<int>();
        }

        calTasksInd = List<int>();
        tempDependencies = List<int>();
    }

    void calculateSlack()
    {
        Task *current_task;
        for (int i = 1; i <= tasks.last_index; i++)
        {
            current_task = &tasks.getElement(i);
            current_task->slack = current_task->LS - current_task->ES;
        }
    }

public:
    void calculateBasicSchedule()
    {
        if (tasks.getElement(1).EF == -1 || tasks.getElement(1).ES == -1)
        {
            int maxEF = calculateESAndEF();
            // cout<<" in basic 8th element dep print() : ";
            // tasks.getElement(8).dependencies.print();
            calculateLSAndLF(maxEF);
            calculateSlack();
        }

        PrintBasicSchedule();
    }

    void PrintCriticalTasks()
    {
        if (tasks.getElement(1).EF == -1 || tasks.getElement(1).ES == -1)
        {
            int maxEF = calculateESAndEF();
            calculateLSAndLF(maxEF);
            calculateSlack();
        }
        // PrintBasicSchedule();

        cout << "List of Critical Tasks: " << endl;
        if (tasks.last_index == 0)
        {
            cout << "No Tasks!" << endl;
            cout << endl;
        }
        else
        {
            for (int i = 1; i <= tasks.last_index; i++)
            {
                if (tasks.getElement(i).slack == 0)
                {
                    tasks.getElement(i).PrintBasicTaskInfo();
                }
            }
            if (this->duration == -1)
            {
                this->duration = 0;
                for (int i = 1; i <= tasks.last_index; i++)
                {
                    if (tasks.getElement(i).slack == 0)
                    {
                        this->duration += tasks.getElement(i).duration;
                    }
                }
            }
            cout << endl
                 << "Total Duration of Project: " << this->duration << endl;
        }
    }

private:
    int calculateESAndEF_wrt_Resources()
    {
        int maxEF = -1;
        int maxEFInd = -1;
        Task *cal_task;
        Task *current_task;
        Task *current_task2;
        Resource *current_resource;
        List<int> calTasksInd;
        List<int> tempDependencies;
        for (int i = 1; i <= tasks.last_index; i++)
        {
            current_task = &tasks.getElement(i);
            if (current_task->ES == 0)
            {
                calTasksInd.insert(i);
            }
        }
        for (int i = 1; i <= calTasksInd.last_index - 1; i++)
        {
            current_task = &tasks.getElement(calTasksInd.getElement(i));
            int min_index = i;
            for (int j = i + 1; j <= calTasksInd.last_index; j++)
            {
                current_task2 = &tasks.getElement(calTasksInd.getElement(j));
                if (current_task->LS > current_task2->LS)
                    min_index = j;
            }
            if (min_index != i)
                swap(calTasksInd.getElement(min_index), calTasksInd.getElement(i));
        }
        maxEF = tasks.getElement(calTasksInd.getElement(calTasksInd.last_index)).EF;
        maxEFInd = tasks.getElement(calTasksInd.getElement(calTasksInd.last_index)).id;

        for (int j = 1; j <= resources.last_index; j++)
        {
            for (int m = 1; m <= calTasksInd.last_index; m++)
            {
                if (tasks.getElement(calTasksInd.getElement(m)).skill_id == resources.getElement(j).id)
                {
                    bool found = false;
                    current_task = &tasks.getElement(calTasksInd.getElement(m));
                    for (int k = m + 1; k <= calTasksInd.last_index; k++)
                    {
                        if (tasks.getElement(calTasksInd.getElement(k)).skill_id == resources.getElement(j).id)
                        {
                            current_task2 = &tasks.getElement(calTasksInd.getElement(m + 1));

                            current_task2->ES = current_task->EF;
                            current_task2->EF = current_task2->ES + current_task2->duration;
                            found = true;
                        }
                    }
                }
            }
            
        }

        //cout<<maxEF<<maxEFInd<<endl;

        // for (int i = 1; i <= resources.last_index; i++)
        // {
        //     current_resource = &resources.getElement(i);
        //     for (int j = 1; j <= calTasksInd.last_index; j++)
        //     {
        //         cal_task = &tasks.getElement(calTasksInd.getElement(j));
        //         for (int k = 1; k <= tasks.last_index; k++)
        //         {
        //             current_task = &tasks.getElement(k);
        //             if (current_task->checkExistanceOfDependency(calTasksInd.getElement(j)))
        //             {
        //                 if (current_task->skill_id == current_resource->id && cal_task->skill_id == current_resource->id)
        //                 {
        //                     if (j == 1)
        //                     {
        //                         current_task->ES = cal_task->EF;
        //                         current_task->EF = current_task->ES + current_task->duration;
        //                     }
        //                     else
        //                     {
        //                         if (cal_task->EF > current_task->ES)
        //                         {
        //                             current_task->ES = cal_task->EF;
        //                             current_task->EF = current_task->ES + current_task->duration;
        //                         }
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }

        return maxEF;
    }

public:
    void completionTimeWithResources()
    {
        // Calculate the project's completion timeconsidering resource availability,
        // allowing tasks to start based on resource availability.
        //  Display the schedule as well.
        if (tasks.getElement(1).EF == -1 || tasks.getElement(1).ES == -1)
        {
            int maxEF = calculateESAndEF();
            calculateLSAndLF(maxEF);
            calculateSlack();
        }

        calculateESAndEF_wrt_Resources();

        PrintBasicSchedule();
    }
};
int Project::id_counter = 1;
#endif