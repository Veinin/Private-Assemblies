#ifndef _SUBJECT_H_
#define _SUBJECT_H_

class Subject{
public:
	virtual ~Subject();

	virtual void Attach(Observer*);
	virtual void Detach(Observer*);
	virtual void Notify();
protected:
	Subject();
private:
	List<Observer> *_observers;
};

#endif