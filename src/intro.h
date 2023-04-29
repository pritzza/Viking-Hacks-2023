#ifndef RECTANGLE_H//this checks if this headerfile has been defined and if it has been already it will skip redefining it otherwise it will proceed to define it
#define RECTANGLE_H//this starts defining the constant so that it can be shown that it already has been defined
#include <iostream>
#include <string>
using namespace std;

//defintion or declaration of the class
class Intro
{
private:
    string username;
    string temp;
    string c;
    
    //mutator
    void setUser()
    {
        //getting username
        getline(cin, username);
        
        if (username=="")
        {username="VikingGuy";}
    }//end of set width
public:
    //intro function
    Intro()
    {
        //clearing screen
        cout<<"\x1b[2J";
        
        //title output
        cout<<"Welcome to Viking Quest: The Green Crusade  ";
        
        //enter because formatting
        enter();
        
        //vern asks name
        cout<<"Vern: Greetings Traveler.";
        
        //enter because formatting
        enter();
        
        //name
        cout<<"Vern: What is your name?";
        
        //enter because formatting
        enter();
        
        //my name is
        cout<<"Please type your name:";
        
        //user provides name
        setUser();
        
        //clearing the screen again
        cout<<"\x1b[2J";
        
        //more exposition
        cout<<"My name is "<<username <<" and I seek glory and adventure in this land, but something does not feel right.";
        
        //enter because formatting
        enter();
        
        //exposition
        cout<<"Vern: Aye "<<username<<" you are correct.";
        
        //enter because formatting
        enter();
        
        //more exposition
        cout<<"Vern: There is a plague in this land. The water is poisoned, the air is foul, the soil is barren and void of life.";
        
        //enter because formatting
        enter();
        
        // blah blah blah
        cout<<"Vern: The greedy guilds from faraway lands have ravaged this fair landscape that many loved and lived in.";
        
        //enter because formatting
        enter();
        
        //there is so much exposition
        cout<<"Vern: They have made it a hollow shell of its former glory; a cursed realm that slays all who enter.";
        
        //enter because formatting
        enter();
        
        //THE FIGHT STATEMENT(by chat gpt 4)
        cout<<username<<": By Odin’s beard, this is a grim sight to behold. This land is sick and dying, and no warrior deserves to live in such misery. The cowardly scum who have done this must pay for their crimes.";
        
        //AGAIN??
        enter();
        
        //old man the end
    cout<<"Vern: You must move with vicious haste "<<username<<". There remains a hidden corner of the forest untouched from desecration, where you must equip yourself for your noble mission. Then you must face the perilous waters of the tainted lake and cleanse them of their corruption. Finally you must ascend the mighty mountain and confront the wicked ones who cause this harm to our great land.";
        
        //enter
        enter();
        
        //END
        cout<<"Vern: Will you fight?";
        
        enter();
        
        
        
        
        
        
        
    }
    
    //function to press enter(for only this class)
    void enter()
    {
        //this is here bc it has to be
                
        //waiting for enter
        getline(cin,c);
        
        //clearing the screen
        cout<<"\x1b[2J";
    }
    
    
    //accessor
    string getUser()
    {
        return username;
    }
    
};//end of declaration

//this weird thing
#endif//ends the definition of RECTANGLE_H
