#include <iostream>

class Lock {
public:
    constexpr static int LOCK_MIN_POSITION = 0;
    constexpr static int LOCK_MAX_POSITION = 99;
    constexpr static int LOCK_DEFAULT_STARTING_POSITION = 50;

    Lock(unsigned int startPosition) : mPosition(startPosition) {}
    Lock() : Lock(LOCK_DEFAULT_STARTING_POSITION) {}

    int getPosition() const {
        return mPosition;
    }

    int getNumberOfTimesPositionIsZero() const {
        return mNumberOfTimesPositionIsZero;
    } 

    void rotateLeft(int position) {
        if (position == 0) {
            if (mPosition == 0) mNumberOfTimesPositionIsZero++;
            return;
        }

        mPosition--;
        
        if (mPosition < LOCK_MIN_POSITION) mPosition = LOCK_MAX_POSITION;

        rotateLeft(position - 1);
    }

    void rotateRight(int position) {
        if (position == 0) {
            if (mPosition == 0) mNumberOfTimesPositionIsZero++;
            return;
        }

        mPosition++;

        if (mPosition > LOCK_MAX_POSITION) mPosition = LOCK_MIN_POSITION;

        rotateRight(position - 1);
    }
private:
    int mPosition{};
    int mNumberOfTimesPositionIsZero{0};
};

int main() {
    Lock l;

    char direction;
    int amount;
    while (std::cin >> direction >> amount) {
        switch (direction) {
        case 'L':
            l.rotateLeft(amount);
            break;
        case 'R':
            l.rotateRight(amount);
            break;
        default:
            break;
        }

        direction = '\0';
    }
    
    std::cout << "Password is: " << l.getNumberOfTimesPositionIsZero() << std::endl; // it makes sense to use endl cause the program is ending next line

    return 0;
}