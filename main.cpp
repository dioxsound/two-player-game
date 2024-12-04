// main.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

// Базовый класс Player представляет игрока в игре
class Player {
protected:
    std::string name; // Имя игрока
    int health;       // Здоровье игрока

public:
    // Конструктор с параметрами
    Player(const std::string& playerName, int initialHealth = 100)
        : name(playerName), health(initialHealth) {}

    virtual ~Player() = default;

    // Метод для получения имени игрока
    std::string getName() const {
        return name;
    }

    // Метод для получения текущего здоровья
    int getHealth() const {
        return health;
    }

    // Метод для атаки другого игрока
    virtual void attack(Player& opponent) {
        // Базовая атака: наносит случайный урон от 10 до 20
        int damage = rand() % 11 + 10;
        std::cout << name << " наносит удар и наносит " << damage << " урона " << opponent.getName() << "!\n";
        opponent.takeDamage(damage);
    }

    // Метод для получения урона
    virtual void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    // Метод для получения исцеления
    virtual void receiveHealing(int amount) {
        health += amount;
        std::cout << name << " получает " << amount << " здоровья. Текущее здоровье: " << health << " HP.\n";
    }

    // Проверка, жив ли игрок
    bool isAlive() const {
        return health > 0;
    }

    // Виртуальный метод для отображения доступных действий
    virtual void displayActions() const = 0;

    // Виртуальный метод для выполнения действия
    virtual void performAction(int choice, Player& opponent) = 0;
};

// Класс Hunter (Охотник) с уникальной способностью "Охота"
class Hunter : public Player {
public:
    Hunter(const std::string& playerName, int initialHealth = 100)
        : Player(playerName, initialHealth) {}

    void attack(Player& opponent) override {
        // Обычная атака Охотника
        int damage = rand() % 11 + 10;
        std::cout << name << " стреляет и наносит " << damage << " урона " << opponent.getName() << "!\n";
        opponent.takeDamage(damage);
    }

    // Способность "Охота" - дополнительный урон
    void hunt(Player& opponent) {
        int damage = rand() % 21 + 20; // Урон от 20 до 40
        std::cout << name << " использует способность ОХОТА и наносит " << damage << " урона " << opponent.getName() << "!\n";
        opponent.takeDamage(damage);
    }

    void displayActions() const override {
        std::cout << "Действия:\n";
        std::cout << "1. Атаковать\n";
        std::cout << "2. Использовать Охоту (наносит дополнительный урон)\n";
    }

    void performAction(int choice, Player& opponent) override {
        if (choice == 1) {
            attack(opponent);
        }
        else if (choice == 2) {
            hunt(opponent);
        }
        else {
            std::cout << "Некорректный выбор действия. Пропуск хода.\n";
        }
    }
};

// Класс Healer (Целитель-пацифист) с уникальной способностью "Исцеление"
class Healer : public Player {
public:
    Healer(const std::string& playerName, int initialHealth = 100)
        : Player(playerName, initialHealth) {}

    void attack(Player& opponent) override {
        // Атака Целителя
        int damage = rand() % 6 + 5; // Слабый урон от 5 до 10
        std::cout << name << " наносит слабый удар и наносит " << damage << " урона " << opponent.getName() << "!\n";
        opponent.takeDamage(damage);
    }

    // Способность "Исцеление" - восстанавливает здоровье самого себя
    void heal() {
        int healAmount = rand() % 21 + 10; // Восстановление от 10 до 30
        std::cout << name << " использует способность ИСЦЕЛЕНИЕ и восстанавливает " << healAmount << " здоровья!\n";
        receiveHealing(healAmount);
    }

    void displayActions() const override {
        std::cout << "Действия:\n";
        std::cout << "1. Атаковать\n";
        std::cout << "2. Использовать Исцеление (восстанавливает собственное здоровье)\n";
    }

    void performAction(int choice, Player& opponent) override {
        if (choice == 1) {
            attack(opponent);
        }
        else if (choice == 2) {
            heal();
        }
        else {
            std::cout << "Некорректный выбор действия. Пропуск хода.\n";
        }
    }

    // Метод для получения исцеления уже реализован в базовом классе
};

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
