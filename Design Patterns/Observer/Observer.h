#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;

class Observer {
public:
	virtual ~Observer();
	virtual void Update(Subject* theChangedSubject) = 0;
protected:
	Observer();
};

#endif