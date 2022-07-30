export module employee;

namespace HR {
    export enum class Title { Manager, SeniorEngineer, Engineer };
    export struct Employee {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary;
        Title title;
    };
}