export module exercise_employee;

namespace HR {

    export enum class TitleType { Manager, SeniorEngineer, Engineer };
    export struct Employee {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary;
        TitleType title;
    };
    

}