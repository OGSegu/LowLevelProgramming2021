long factorial(int number) {
    return (number == 0 || number == 1) ? 1 : number * factorial(number - 1);
}

int getMaxNumberOfEdges(int amount) {
    return factorial(amount) / (factorial(amount - 2) * factorial(2));
}