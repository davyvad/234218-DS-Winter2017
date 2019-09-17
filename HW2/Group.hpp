/*
 * Group.hpp
 *
 *  Created on: 2 ????? 2018
 *      Author: Or
 */

#ifndef GROUP_HPP
#define GROUP_HPP

class Group{
	int _GroupId;
	int _index;

public:
    Group(int Id, int i){ _GroupId=Id;_index=i;};
	void SetIndex(int i){_index=i;}
	int GetIndex(){return _index;}
	int GetId(){return _GroupId;}
	bool operator>(const Group& gr) const{
		 if(_GroupId > gr._GroupId) return true;
		 return false;
	}
};


#endif /* GROUP_HPP_ */
