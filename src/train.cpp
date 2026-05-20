// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        newCar->next = newCar;
        newCar->prev = newCar;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    countOp = 0;
    if (!first) return 0;

    bool initialState = first->light;
    first->light = !initialState;
    countOp++;

    int steps = 1;
    Car* current = first;

    while (true) {
        current = current->next;
        countOp++;
        steps++;

        if (current->light == !initialState) {
            current->light = initialState;
            countOp++;

            for (int i = 0; i < steps; i++) {
                current = current->prev;
                countOp++;
            }

            if (current->light == initialState) {
                current->light = !initialState;
                countOp++;
                steps = 1;
            } else {
                current->light = !initialState;
                countOp++;
                break;
            }
        }
    }

    return steps;
}

int Train::getOpCount() {
    return countOp;
}
