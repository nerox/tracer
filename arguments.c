#include <iostream>
#include <stdlib.h>
#include <sstream> 
int main(int argc, char *argv[])
{
    std::cout << "There are " << argc << " arguments:\n";
    int width,height,fieldview,objects;
    bool shadows,reflections,refractions,precision,vector;
    int from[3];
    int to[3];
    int up[3];

    // Loop through each argument and print its number and value
    for (int count{ 0 }; count < argc; ++count)
    {
        if(argv[count] == std::string("w")){
              std::stringstream temp(argv[count+1]); 
              temp >> width; 
              std::cout <<  width<< " ancho\n";  
        }
        if(argv[count]==std::string("h")){
              std::stringstream temp(argv[count+1]); 
              temp >> height; 
              std::cout <<  height<<" alto\n"; 
 
        }
        if(argv[count]==std::string("fv")){
              std::stringstream temp(argv[count+1]); 
              temp >> fieldview; 
              //std::cout << fieldview<< " field view\n";    
        }
        if(argv[count]==std::string("sh")){
              shadows= (std::string(argv[count+1])=="1");
              std::cout <<  shadows << " shadows\n";    
        }
        if(argv[count]==std::string("fl")){
              reflections= (std::string(argv[count+1])=="1");
              std::cout <<  reflections<<" reflection\n";    
        }
        if(argv[count]==std::string("fr")){
              refractions= (std::string(argv[count+1])=="1");
              std::cout <<  refractions<<" refraction\n";    
        }
        if(argv[count]==std::string("pr")){
              precision= (std::string(argv[count+1])=="1");
              std::cout <<  precision<<" precision\n";    
        }
        if(argv[count]==std::string("v")){
              vector= (std::string(argv[count+1])=="1");
              std::cout <<  vector <<" vector\n";    
        }
        if(argv[count]==std::string("o")){
              std::stringstream temp(argv[count+1]); 
              temp >> objects; 
              std::cout <<  objects<<" objects\n";    
        }
        if(argv[count]==std::string("fm")){
              std::stringstream temp(argv[count+1]); 
              temp >> from[0]; 
              std::stringstream temp1(argv[count+2]); 
              temp1 >> from[1]; 
              std::stringstream temp2(argv[count+3]); 
              temp2 >> from[2]; 
              std::cout <<  from[0]<< " "<<from[1]<< " "<<from[2] <<" from\n";    
        }
        if(argv[count]==std::string("to")){
              std::stringstream temp(argv[count+1]); 
              temp >> to[0]; 
              std::stringstream temp1(argv[count+2]); 
              temp1 >> to[1]; 
              std::stringstream temp2(argv[count+3]); 
              temp2 >> to[2]; 
              std::cout <<  to[0]<< " "<<to[1]<< " "<<to[2] <<" to\n";    
        }
        if(argv[count]==std::string("up")){
              std::stringstream temp(argv[count+1]); 
              temp >> up[0]; 
              std::stringstream temp1(argv[count+2]); 
              temp1 >> up[1]; 
              std::stringstream temp2(argv[count+3]); 
              temp2 >> up[2]; 
              std::cout <<  up[0]<< " "<<up[1]<< " "<<up[2] <<" up\n";    
        }
    }
 
    return 0;
}