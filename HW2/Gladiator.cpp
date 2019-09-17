
#include "Gladiator.hpp"



int Glad::getID() const{
    return gladiatorID;
}




 bool Glad::operator<(const Glad& gladiator) const {
     if(this->gladiatorLevel == gladiator.gladiatorLevel){
         return this->gladiatorID > gladiator.gladiatorID;
     }
     else {
         return this->gladiatorLevel < gladiator.gladiatorLevel;
     }
 }

bool Glad::operator>(const Glad& gladiator) const{
    return gladiator < *this;
}



bool Glad::operator==(const Glad& glad) const{
    bool t= this->gladiatorID== glad.gladiatorID;
    return t;
}



std::ostream& operator<<(std::ostream& output, const Glad& gladiator){
    output << "Glad " << gladiator.gladiatorID<<" "<< gladiator.gladiatorLevel ;
    
    return output;
}

