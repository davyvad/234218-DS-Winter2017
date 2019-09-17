//
#ifndef Gladiator_hpp
#define Gladiator_hpp

#include <stdio.h>
#include <iostream>

//class NodeGroup;
class Glad {

	int gladiatorID;
	int gladiatorLevel; // Score

public:
    
	Glad(int id, int level = -1) :
			gladiatorID(id), gladiatorLevel(level) {};
	Glad(const Glad& glad) :
			gladiatorID(glad.gladiatorID), gladiatorLevel(glad.gladiatorLevel){};

	const int getLevel() const {
		return gladiatorLevel;
	}

	void setLevel(int new_level) {
		gladiatorLevel = new_level;
	}
	void setID(int new_ID) {
		gladiatorID = new_ID;
	}
	int getID() const;


	bool operator<(const Glad& gladiator) const;
	bool operator>(const Glad& gladiator) const;

	bool operator==(const Glad& glad) const;

	friend std::ostream& operator<<(std::ostream& output,
			const Glad& gladiator);

};

std::ostream& operator<<(std::ostream& output, const Glad& gladiator);

class GladLessById {
public:
	bool operator()(const Glad& g1, const Glad& g2) {
		return g1.getID() < g2.getID();
	}
};

#endif /* Gladiator_hpp */
