// Muhammad_Yousaf_22i8797_F
#include <iostream>
#include <limits>
#include <Windows.h>
#include "List.h"
#include "Project.h"
#include "SupportingFunction.h"

using namespace std;

void PrintProjectBasicInfo(Project &project)
{
    system("cls");
    std::cout << "Project id. " << project.id << "    Project Name : " << project.name << endl;
    std::cout << "  Tasks:  " << endl;
    project.PrintTasksBasicInfo();
    std::cout << "  Resouces: " << endl;
    project.PrintResourcesInfo();
    cout<<endl;
}
void AddResources(Project &project)
{
    int num_of_resources;
    cout << "Enter the number of resources you want to enter : ";
    IntInputAndValidation(num_of_resources, 1, 999);

    string skill_name;
    float proficiency_lvl;
    for (int i = 1; i <= num_of_resources; i++)
    {
        cout << "Enter the name of the skill Possessed by the resource.no" << i << ": ";
        cin >> skill_name;
        cout << "Enter the proficiency level of the entered skill(0 to 1): ";
        floatInputAndValidation(proficiency_lvl, 0, 1);

        Resource *r = new Resource(skill_name, proficiency_lvl);
        Resource::id_counter--;
        project.resources.insert(*r);

        system("cls");
        PrintProjectBasicInfo(project);
    }
}
void AddTasks(Project &project)
{

    int task_duration, dependency_task_id, required_skill_id, num_of_tasks;
    string name;
    cout << "Enter the number of tasks you want to enter : ";
    IntInputAndValidation(num_of_tasks, 1, 99);
    cout << endl;

    // Taking the input of the all the tasks of the project
    for (int i = 1; i <= num_of_tasks; i++)
    {
        cout << "Details for task.no" << i << endl;
        cout << "Enter the name of the task : ";
        cin >> name;
        cout << "Enter the duration of the task: ";
        IntInputAndValidation(task_duration, 1, 999999);
        cout << "Enter the id of the skill on which this task is dependent: ";
        IntInputAndValidation(required_skill_id, 1, project.resources.last_index);

        Task *t = new Task(name, required_skill_id, task_duration);
        Task::id_counter--;
        project.tasks.insert(*t);

        system("cls");
        PrintProjectBasicInfo(project);
        cout << endl
             << "Avaliable skills: " << endl;
        project.DisplayAllSkillsPossessedbyResources();
        cout << endl;
    }

    // Number of tasks > be greater than 1 for these proccesses, '1' means there is only one task in the list
    if (project.tasks.last_index > 1)
    {
        // Identifying the task with the start time of zero to get the starting time of the task, start time of the rest of the tasks will be calculated automatically.
        while (true)
        {
            int id_with_zero_st_time;
            char add_task_of_time_zero;
            cout << "Enter the id of the Independent Tasks(tasks with the start time of '0'): ";
            IntInputAndValidation(id_with_zero_st_time, 1, project.tasks.last_index);

            if (project.getTask(id_with_zero_st_time).ES == 0)
                cout << "Early Start of this task is already equal to zero." << endl;
            else
                project.getTask(id_with_zero_st_time).ES = 0;

            cout << "Do you want to set another task independent(with the start time of '0')? (y/n) : ";
            cin >> add_task_of_time_zero;

            if (add_task_of_time_zero == 'n')
                break;
            else if (add_task_of_time_zero != 'y')
            {
                cout << "Invalid input! Exitting the proccess! " << endl;
                break;
            }
        }

        // Now Identifying the dependencies of the tasks from the user
        for (int i = 1; i <= project.tasks.last_index; i++)
        {
            if (project.getTask(i).ES == 0)
                continue;

            int dependent_id;
            char keep_adding_dependent_tasks;
            while (true)
            {
                cout << "Enter the task's id on which task with id.no: " << i << " is dependent" << endl;
                IntInputAndValidation(dependent_id, 1, project.tasks.last_index, i);

                if (project.getTask(i).checkExistanceOfDependency(dependent_id))
                {
                    cout << "This Dependency already exists!" << endl;
                    Sleep(2000);
                }
                else if (project.getTask(dependent_id).checkExistanceOfDependency(i))
                {
                    cout << "This Dependency is not possible !" << endl
                         << "As task with id.no: " << dependent_id << " is dependent on " << i << endl;
                         Sleep(2000);
                }
                else
                {
                    project.getTask(i).AddTaskDependencies(dependent_id);
                    cout << "Task with id.no: " << i << " is now dependent on " << dependent_id << endl;
                    Sleep(2000);
                }

                cout << "Do you want to keep adding dependencies of this tasks? (y/n)) : ";
                cin >> keep_adding_dependent_tasks;

                if (keep_adding_dependent_tasks == 'n')
                {
                    system("cls");
                    PrintProjectBasicInfo(project);
                    break;
                }
                else if (keep_adding_dependent_tasks != 'y')
                {
                    system("cls");
                    PrintProjectBasicInfo(project);
                    cout << "invalid input! Exitting the current Proccess" << endl;
                    break;
                }

                system("cls");
                PrintProjectBasicInfo(project);
            }
        }
    }
    else if (project.tasks.last_index == 1) // '1' means first task
    {
        project.getTask(1).ES = 0;
    }
}
void ProjectInputs(Project &project)
{
    string name;

    cout << "Enter name of the project : ";
    getline(cin,name);
    project.name = name;

    //cin.clear();
    //cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    PrintProjectBasicInfo(project);

    AddResources(project);

    cout << endl
         << "Avaliable skills: " << endl;
    project.DisplayAllSkillsPossessedbyResources();
    cout << endl;
    AddTasks(project);
}

void Menu(Project &project)
{
    system("cls");
    int choice;
    while (true)
    {
        cout << endl
             << "1. Modify the Duration of All Tasks" << endl
             << "2. Modify the duration of a Specific Task" << endl
             << "3. Print Task Dependency List" << endl
             << "4. Calculate and Print Basic Schedule" << endl
             << "5. Print Critical Tasks" << endl
             << "6. Print Completion with respect to Resources availability" << endl
             << "7. Print Completion time with respect to Resources availability and Skill Proficiency level" << endl
             << "8. Print Prject Basic Information" << endl
             << "9. Exit" << endl
             << endl;
        cout<<"Enter your choice: ";
        IntInputAndValidation(choice, 1, 9);

        switch (choice)
        {
        case 1:
            project.setTaskDuration(); // modify the duration of all tasks
            break;
        case 2:
        {
            int task_id;
            int new_duration;
            cout << "Enter the task ID to modify it's duration : ";
            IntInputAndValidation(task_id, 1, project.tasks.last_index);
            cout << "Enter the new duration of the task : ";
            IntInputAndValidation(new_duration, 1, 9999);

            project.set_nth_TaskDuration(task_id, new_duration); // modify the duration of task with nth id = 'task_id'
        }
        break;
        case 3:
            system("cls");
            project.PrintTaskDependencyList();
            cout << endl;
            break;
        case 4:
            project.calculateBasicSchedule();
            break;
        case 5:
            project.PrintCriticalTasks();
            break;
        case 6:
            project.completionTimeWithResources();
            break;
        case 7:
            /* code */
            break;
        case 8:
            project.PrintTasksBasicInfo();
            break;
        case 9:
            cout<<"Exitting..."<<endl;
            exit(0);
            break;
        default:
            break;
        }
    system("pause");
    }
}
int main()
{
    system("cls");
    Project project;
    ProjectInputs(project);
    Menu(project);

    return 0;
}