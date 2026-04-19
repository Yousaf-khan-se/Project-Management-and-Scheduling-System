// Muhammad_Yousaf_22i8797_F
#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include "Skill.h"

struct Resource
{
    int id;
    bool availability;
    Skill skill;
    static int id_counter;

    Resource() :  availability(true), id(id_counter), skill("Nill", 0.0, id_counter++)
    {}
    Resource(string Possessed_skill_name, float skill_proficiency) : id(id_counter), availability(true), skill(Possessed_skill_name, skill_proficiency, id_counter++)
    {}

    void DisplayResourceInfo()
    {
        cout<<"Resource id: "<<this->id<<"   availability: ";
        if(this->availability)
        cout<<"true    ";
        else
        cout<<"false   ";
        cout<<endl<<"Possessed ";
        this->skill.DisplaySkillInfo();
    }
    void RevertAvailability()
    {
        if(this->availability == true)
        this->availability = false;
        else
        this->availability = true;
    }
};
int Resource::id_counter = 1;
#endif