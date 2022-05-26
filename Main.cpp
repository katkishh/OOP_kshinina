#include"Container.h"
#include"Object1.h"

uint32_t Object::m_counter = 0;

int main()
{
    Container<Task*> tasks;
    Container<std::string> info;

    double a = 0, b = 0;
    char oper;
    
    a = 120; b = 7; oper = '*';
    Task* task1 = new BiArithmeticOperation(a, b, oper, "multiplication");
    AddTask* add1 = new AddTask(tasks, task1);
    add1->execute();
    a = 4; b = 8; oper = '/';
    Task* task2 = new  BiArithmeticOperation(a, b, oper, "division");
    AddTask* add2 = new AddTask(tasks, task2);
    add2->execute();
    a = 92; b = 105; oper = '-';
    Task* task3 = new BiArithmeticOperation(a, b, oper, "subtraction");
    AddTask* add3 = new AddTask(tasks, task3);
    add3->execute();
    a = 7513; b = 785; oper = '+';
    Task* task4 = new BiArithmeticOperation(a, b, oper, "adding");
    AddTask* add4 = new AddTask(tasks, task4);
    add4->execute();
    a = 95; b = 37; oper = '-';
    Task* task5 = new BiArithmeticOperation(a, b, oper, "subtraction");
    AddTask* add5 = new AddTask(tasks, task5);
    add5->execute();
    Task* task6 = new ResultTaskCounter(tasks);
    AddTask* add6 = new AddTask(tasks, task6);
    add6->execute();
    a = 856; b = 72; oper = '/';
    Task* task7 = new  BiArithmeticOperation(a, b, oper, "division");
    AddTask* add7 = new AddTask(tasks, task7);
    add7->execute();
    a = 764; b = 851; oper = '+';
    Task* task8 = new  BiArithmeticOperation(a, b, oper, "adding");
    AddTask* add8 = new AddTask(tasks, task8);
    add8->execute();
    Task* task9 = new TaskCounter(tasks);
    AddTask* add9 = new AddTask(tasks, task9);
    add9->execute();
    a = 71; b = 22; oper = '*';
    Task* task10 = new BiArithmeticOperation(a, b, oper, "multiplication");
    AddTask* add10 = new AddTask(tasks, task10);
    add10->execute();
    Task* task11 = new TaskCounter(tasks);
    AddTask* add11 = new AddTask(tasks, task11);
    add11->execute();
 
    ObjectCounter* obj_counter = new ObjectCounter;
    obj_counter->execute();
    std::cout << "Total amount of objects: " << std::to_string(obj_counter->getResult()) << std::endl;
    
    for ( int i = 0; i <= 10; ++i ) {
        tasks.get_first()->execute();
        info.insert_back(tasks.get_first()->toString());
        tasks.delete_first();
    }

    for ( Container<std::string>::Iterator i = info.begin(); i != info.end(); i++ ) {
        std::cout << i.get_element()->data << std::endl;
    }
    std::cout << info.get_last() << std::endl;        //учет последнего элемента
    
    tasks.clear();
    info.clear();

    delete obj_counter;
    
    delete add1;
    delete add2;
    delete add3;
    delete add4;
    delete add5;
    delete add6;
    delete add7;
    delete add8;
    delete add9;
    delete add10;
    delete add11;

    delete task1;
    delete task2;
    delete task3;
    delete task4;
    delete task5;
    delete task6;
    delete task7;
    delete task8;
    delete task9;
    delete task10;
    delete task11;

    ObjectCounter* obj_coonter2 = new ObjectCounter;
    obj_coonter2->execute();

    std::cout << std::endl;
    std::cout << obj_coonter2->toString() << std::endl;

    delete obj_coonter2;
    
    return 0;
}


