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

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
