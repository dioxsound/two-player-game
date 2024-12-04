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

// Класс Pyromancer (Пиромант) с уникальной способностью "Огненная волна"
class Pyromancer : public Player {
private:
    int burnDamage;      // Урон от огня
    int burnDuration;    // Количество ходов, в течение которых действует огонь

public:
    Pyromancer(const std::string& playerName, int initialHealth = 100)
        : Player(playerName, initialHealth), burnDamage(0), burnDuration(0) {}

    void attack(Player& opponent) override {
        // Обычная атака Пироманта
        int damage = rand() % 11 + 10;
        std::cout << name << " выпускает огненную стрелу и наносит " << damage << " урона " << opponent.getName() << "!\n";
        opponent.takeDamage(damage);
    }

    // Способность "Огненная волна" - наносит урон в течение нескольких ходов
    void fireWave(Player& opponent) {
        burnDamage = rand() % 6 + 5; // Урон от 5 до 10 за ход
        burnDuration = 3;            // Длится 3 хода
        std::cout << name << " использует способность ОГНЕННАЯ ВОЛНА! " << opponent.getName()
                  << " будет получать " << burnDamage << " урона в течение " << burnDuration << " ходов.\n";
    }

    void applyBurn(Player& opponent) {
        if (burnDuration > 0) {
            std::cout << opponent.getName() << " получает " << burnDamage << " урона от ОГНЕННОЙ ВОЛНЫ.\n";
            opponent.takeDamage(burnDamage);
            burnDuration--;
        }
    }

    void displayActions() const override {
        std::cout << "Действия:\n";
        std::cout << "1. Атаковать\n";
        std::cout << "2. Использовать Огненную волну (наносит урон в течение нескольких ходов)\n";
    }

    void performAction(int choice, Player& opponent) override {
        if (choice == 1) {
            attack(opponent);
        }
        else if (choice == 2) {
            fireWave(opponent);
        }
        else {
            std::cout << "Некорректный выбор действия. Пропуск хода.\n";
        }
    }

    // Метод для проверки и применения огненного урона
    void checkBurn(Player& opponent) {
        if (burnDuration > 0) {
            applyBurn(opponent);
        }
    }
};

// Класс Game управляет процессом игры
class Game {
private:
    std::unique_ptr<Player> player1; // Первый игрок
    std::unique_ptr<Player> player2; // Второй игрок

public:
    // Конструктор принимает имена и типы персонажей игроков
    Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2)
        : player1(std::move(p1)), player2(std::move(p2)) {}

    // Метод для запуска игры
    void start() {
        std::cout << "=== Добро пожаловать в консольную файтинг-игру! ===\n";
        std::cout << player1->getName() << " против " << player2->getName() << "!\n\n";

        // Определяем, кто будет начинать первым случайно
        Player* currentPlayer = nullptr;
        Player* otherPlayer = nullptr;

        if (rand() % 2 == 0) {
            currentPlayer = player1.get();
            otherPlayer = player2.get();
        }
        else {
            currentPlayer = player2.get();
            otherPlayer = player1.get();
        }

        std::cout << currentPlayer->getName() << " начинает первым!\n\n";

        // Основной цикл игры
        while (player1->isAlive() && player2->isAlive()) {
            std::cout << "Ход игрока: " << currentPlayer->getName() << "\n";
            currentPlayer->displayActions();
            std::cout << "Выберите действие (1 или 2): ";

            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Очистка буфера ввода

            currentPlayer->performAction(choice, *otherPlayer);

            // Проверка и применение огненного урона для Pyromancer
            // Если currentPlayer или otherPlayer является Pyromancer
            Pyromancer* pyroCurrent = dynamic_cast<Pyromancer*>(currentPlayer);
            Pyromancer* pyroOther = dynamic_cast<Pyromancer*>(otherPlayer);

            if (pyroCurrent) {
                pyroCurrent->checkBurn(*otherPlayer);
            }
            if (pyroOther) {
                pyroOther->checkBurn(*currentPlayer);
            }

            // Вывод текущего здоровья обоих игроков
            std::cout << "\nТекущее здоровье:\n";
            std::cout << player1->getName() << ": " << player1->getHealth() << " HP\n";
            std::cout << player2->getName() << ": " << player2->getHealth() << " HP\n\n";

            // Проверка, жив ли противник
            if (!otherPlayer->isAlive()) {
                std::cout << otherPlayer->getName() << " побежден!\n";
                std::cout << currentPlayer->getName() << " выигрывает игру!\n";
                break;
            }

            // Меняем текущего игрока
            std::swap(currentPlayer, otherPlayer);
        }

        std::cout << "=== Игра окончена! ===\n";
    }
};
