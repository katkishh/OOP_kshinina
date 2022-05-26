#include "Container.h"
#include<string>
#include<iostream>

class Object {
protected:
	static uint32_t m_counter;
public:
	virtual std::string toString() const = 0;
	Object() {
		++m_counter;
	}
	Object(const Object& obj) {
		++m_counter;
	}
	~Object() {
		--m_counter;
	}
};

class Task : virtual public Object {
protected:
	bool m_performed;
public:
	virtual bool hasResult() const = 0;
	virtual void execute() = 0;
	Task() {
		m_performed = false;
	}
	~Task() {};
};

class Named : virtual public Object {
protected:
	std::string m_name;
};

class BiArithmeticOperation : public Named, public Task {
private:
	double m_a;
	double m_b;
	char m_oper;
	double m_result;
public:
	BiArithmeticOperation(double a, double b, char oper, std::string name) {
		m_a = a;
		m_b = b;
		m_oper = oper;
		m_name = name;
		m_result = 0;
	}

	bool hasResult() const {
		return true;
	}

	void execute() {
		if ( m_oper == '+' ) {
			m_result = m_a + m_b;
			m_performed = true;
		}
		else if ( m_oper == '-' ) {
			m_result = m_a - m_b;
			m_performed = true;
		}
		else if ( m_oper == '*' ) {
			m_result = m_a * m_b;
			m_performed = true;
		}
		else if ( m_oper == '/' ) {
			if ( m_b == 0 ) throw std::exception("Division by 0");
			m_result = m_a / m_b;
			m_performed = true;
		}
		else throw std::exception("Wrong arithmetic operation");
	}

	std::string toString() const{
		if ( m_performed )
			return "Task " + m_name + " " + std::to_string(m_a) + m_oper + std::to_string(m_b) + " was performed. Result: " + std::to_string(m_result);
		else
			return "Task " + m_name + " " + std::to_string(m_a) + m_oper + std::to_string(m_b) + " wasn't performed. No result so far";
	}

	double getResult() {
		return m_result;
	}
};

class AddTask :public Task {
private:
	Container<Task*>& m_cont;
	Task* m_task;
public:
	AddTask(Container<Task*>& cont, Task* task) :m_task(task), m_cont(cont) {}

	bool hasResult() const {
		return false;
	}
	
	void execute() {
		m_cont.insert_back(m_task);
		m_performed = true;
	}

	std::string toString() const {
		if ( m_performed )
			return "Task was added and will be performed";
		else
			return "Task wasn't added but will be";
	}
};

class ObjectCounter :public Task {
private:
	uint32_t m_count;
public:
	ObjectCounter() {
		m_count = 0;
	}

	bool hasResult() const {
		return true;
	}

	void execute() {
		m_count = m_counter;
		m_performed = true;
	}

	std::string toString() const {
		if ( m_performed )
			return "The amount of Objects is known and equals to " + std::to_string(m_count);
		else
			return "The amount of Objects is unknown yet";
	}

	uint32_t getResult() {
		return m_count;
	}
};

class TaskCounter :public Task {
private:
	Container<Task*>const& m_cont;
	uint32_t m_count;
public:
	TaskCounter(Container<Task*>const& cont) : m_count(0), m_cont(cont) {}

	bool hasResult() const {
		return true;
	}

	void execute() {
		m_count = m_cont.size();
		m_performed = true;
	}

	std::string toString() const {
		if( m_performed )
			return "The amount of Objects in Container equals to " + std::to_string(m_count);
		else
			return "The amount of Objects in Container is unknown yet";
	}

	uint32_t getResult() {
		return m_count;
	}
};

class ResultTaskCounter :public Task {
private:
	Container<Task*>& m_cont;
	uint32_t m_count;
public:
	ResultTaskCounter(Container<Task*>& cont) : m_count(0), m_cont(cont) {}

	bool hasResult() const {
		return true;
	}

	void execute() {
		Container<Task*>::Iterator i = m_cont.begin();
		do {
			if ( i.get_element()->data->hasResult() ) ++m_count;
			i++;
		} while (i != m_cont.end());
		m_performed = true;
	}

	std::string toString() const {
		if ( m_performed )
			return "The amount of Tasks with Result equals to " + std::to_string(m_count);
		else 
			return "The amount of Tasks with Result is unknown yet";
	}

	uint32_t getResult() {
		return m_count;
	}
};

class ClearContainer :public Task {
private:
	Container<Task*>& m_cont;
public:
	ClearContainer(Container<Task*>& cont) : m_cont(cont) {}

	bool hasResult() const {
		return false;
	}

	void execute() {
		m_cont.clear();
		m_performed = true;
	}

	std::string toString() const {
		if ( m_performed )
			return "Container has been cleared";
		else
			return "Container isn't clear yet";
	}
};