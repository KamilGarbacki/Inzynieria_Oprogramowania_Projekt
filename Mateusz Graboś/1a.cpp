#include <iostream>
#include <string>
// Product class
class Computer {
public:
    void setCPU(const std::string& cpu) {
        cpu_ = cpu;
    }
    void setMemory(const std::string& memory) {
        memory_ = memory;
    }
    void setStorage(const std::string& storage) {
        storage_ = storage;
    }
    void display() {
        std::cout << "CPU: " << cpu_ << std::endl;
        std::cout << "Memory: " << memory_ << std::endl;
        std::cout << "Storage: " << storage_ << std::endl;
    }
private:
    std::string cpu_;
    std::string memory_;
    std::string storage_;
};
// Builder interface
class ComputerBuilder {
public:
    virtual void buildCPU(const std::string& cpu) = 0;
    virtual void buildMemory(const std::string& memory) = 0;
    virtual void buildStorage(const std::string& storage) = 0;
    virtual Computer getResult() = 0;
};
// Concrete Builder
class DesktopComputerBuilder : public ComputerBuilder {
public:
    DesktopComputerBuilder() {
        computer_ = Computer();
    }
    void buildCPU(const std::string& cpu) override {
        computer_.setCPU(cpu);
    }
    void buildMemory(const std::string& memory) override {
        computer_.setMemory(memory);
    }
    void buildStorage(const std::string& storage) override {
        computer_.setStorage(storage);
    }
    Computer getResult() override {
        return computer_;
    }
private:
    Computer computer_;
};
// Director
class ComputerAssembler {
public:
    Computer assembleComputer(ComputerBuilder& builder) {
        builder.buildCPU("Intel core i9");
        builder.buildMemory("32GB");
        builder.buildStorage("4096GB HDD");
        return builder.getResult();
    }
};
int main() {
    DesktopComputerBuilder desktopBuilder;
    ComputerAssembler assembler;
    Computer desktop = assembler.assembleComputer(desktopBuilder);
    std::cout << "Desktop Computer Configuration:" << std::endl;
    desktop.display();

    DesktopComputerBuilder mateusz;
    mateusz.buildCPU("AMD ryzen 7 5700X");
    mateusz.buildMemory("32GB");
    mateusz.buildStorage("1024GB SSD");
    Computer grabos = mateusz.getResult();
    std::cout << std::endl << "MY Computer Configuration:" << std::endl;
    grabos.display();

    return 0;
}