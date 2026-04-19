// Muhammad_Yousaf_22i8797_F
#ifndef SKILL_H
#define SKILL_H
#include <iostream>

using namespace std;

struct Skill
{
    string name;
    float proficiency;
    int id;

    Skill(string name_ ,float proficiency_, int id_counter) : name(name_), id(id_counter), proficiency(proficiency_)
    {}

    void DisplaySkillInfo()
    {
        cout<<"Skill Id: "<<id<<"   Skill Name: "<<name<<"   Skill Proficiency lvl: "<<proficiency<<endl;
    }
};
#endif 