#include <QuEST.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  QuESTEnv env = createQuESTEnv();
  Qureg qubits = createQureg(3, env);
  initZeroState(qubits);
  hadamard(qubits, 0);
  controlledNot(qubits, 0, 1);
  pauliX(qubits, 2);
  qreal prob = calcProbOfOutcome(qubits, 1, 1);
  printf("Probability of qubit 1 being in state 1: %f\n", prob);

  return 0;
}